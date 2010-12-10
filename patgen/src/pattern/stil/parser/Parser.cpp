

#include <wchar.h>
#include "Parser.h"
#include "Scanner.h"




void Parser::SynErr(int n) {
	if (errDist >= minErrDist) errors->SynErr(la->line, la->col, n);
	errDist = 0;
}

void Parser::SemErr(const char* msg) {
	if (errDist >= minErrDist) errors->Error(t->line, t->col, msg);
	errDist = 0;
}

void Parser::Get() {
	for (;;) {
		t = la;
		la = scanner->Scan();
		if (la->kind <= maxT) { ++errDist; break; }

		if (dummyToken != t) {
			dummyToken->kind = t->kind;
			dummyToken->pos = t->pos;
			dummyToken->col = t->col;
			dummyToken->line = t->line;
			dummyToken->next = NULL;
			coco_string_delete(dummyToken->val);
			dummyToken->val = coco_string_create(t->val);
			t = dummyToken;
		}
		la = t;
	}
}

void Parser::Expect(int n) {
	if (la->kind==n) Get(); else { SynErr(n); }
}

void Parser::ExpectWeak(int n, int follow) {
	if (la->kind == n) Get();
	else {
		SynErr(n);
		while (!StartOf(follow)) Get();
	}
}

bool Parser::WeakSeparator(int n, int syFol, int repFol) {
	if (la->kind == n) {Get(); return true;}
	else if (StartOf(repFol)) {return false;}
	else {
		SynErr(n);
		while (!(StartOf(syFol) || StartOf(repFol) || StartOf(0))) {
			Get();
		}
		return StartOf(syFol);
	}
}

void Parser::Stil() {
		stil_version();
		while (StartOf(1)) {
			stil_block();
		}
}

void Parser::stil_version() {
		Expect(14);
		Expect(2);
		Expect(3);
}

void Parser::stil_block() {
		switch (la->kind) {
		case 15: {
			signals_block();
			break;
		}
		case 25: {
			signalgroups_block();
			break;
		}
		case 27: {
			timing_block();
			break;
		}
		case 36: {
			spec_block();
			break;
		}
		case 41: {
			selector_block();
			break;
		}
		case 6: {
			Get();
			break;
		}
		default: SynErr(43); break;
		}
}

void Parser::signals_block() {
		Expect(15);
		Expect(16);
		signals_list();
		Expect(17);
}

void Parser::signalgroups_block() {
		Expect(25);
		if(pSignalGroups == NULL)
		   pSignalGroups = new Stil::SignalGroups();
		pSignalGroups->clear();
		
		Expect(16);
		groups_list();
		Expect(17);
}

void Parser::timing_block() {
		Expect(27);
		identifier();
		Expect(16);
		timing_items();
		Expect(17);
}

void Parser::spec_block() {
		Expect(36);
		identifier();
		Spec spec;
		spec.setName(t->val);
		
		Expect(16);
		category_block(spec);
		while (la->kind == 37) {
			category_block(spec);
		}
		Expect(17);
		if(pSpecCollection == NULL)
		   pSpecCollection = new Stil::Collection<Stil::Spec>;
		(*pSpecCollection)[spec.getName()] = spec;
		
}

void Parser::selector_block() {
		Expect(41);
		identifier();
		Expect(16);
		selector_item();
		while (la->kind == 5 || la->kind == 7) {
			selector_item();
		}
		Expect(17);
}

void Parser::signals_list() {
		signals_item();
		while (la->kind == 5 || la->kind == 7) {
			signals_item();
		}
}

void Parser::signals_item() {
		signal_name();
		Stil::Signal signal(t->val); 
		signal_type();
		signal.setSignalType(t->val); 
		if (la->kind == 3) {
			Get();
		} else if (la->kind == 16) {
			Get();
			if (la->kind == 18) {
				Get();
			} else if (la->kind == 19) {
				Get();
			} else SynErr(44);
			Expect(3);
			Expect(17);
		} else SynErr(45);
		signals.addSignal(signal);
		signals.addSignal(signal);
		//if(pSignals == NULL) pSignals = new Signals();
		//pSignals->addSignal(signal);
		symTab[signal.getName()] = "Signal"; 
		
}

void Parser::signal_name() {
		identifier();
		if (la->kind == 12) {
			Get();
			Expect(1);
			Expect(13);
		}
}

void Parser::signal_type() {
		if (la->kind == 20) {
			Get();
		} else if (la->kind == 21) {
			Get();
		} else if (la->kind == 22) {
			Get();
		} else if (la->kind == 23) {
			Get();
		} else if (la->kind == 24) {
			Get();
		} else SynErr(46);
}

void Parser::identifier() {
		if (la->kind == 5) {
			Get();
		} else if (la->kind == 7) {
			Get();
		} else SynErr(47);
}

void Parser::groups_list() {
		groups_item();
		while (la->kind == 5 || la->kind == 7) {
			groups_item();
		}
}

void Parser::groups_item() {
		identifier();
		string groupName = t->val; 
		Expect(26);
		sigref_expr();
		string expr = t->val; 
		Expect(3);
		pSignalGroups->add( groupName, expr); 
}

void Parser::sigref_expr() {
		if (la->kind == 5 || la->kind == 7) {
			signal_name_array_opt();
		} else if (la->kind == 8) {
			Get();
		} else SynErr(48);
}

void Parser::signal_name_array_opt() {
		if (la->kind == 5 || la->kind == 7) {
			signal_name();
		} else if (la->kind == 5 || la->kind == 7) {
			identifier();
			Expect(12);
			Expect(1);
			Expect(4);
			Expect(1);
			Expect(13);
		} else SynErr(49);
}

void Parser::timing_items() {
		timing_item();
		while (la->kind == 28) {
			timing_item();
		}
}

void Parser::timing_item() {
		waveform_table();
}

void Parser::waveform_table() {
		Expect(28);
		identifier();
		Stil::WaveformTable wft(t->val);
		
		Expect(16);
		waveform_table_item(wft);
		while (la->kind == 29 || la->kind == 30 || la->kind == 31) {
			waveform_table_item(wft);
		}
		Expect(17);
		wftCollection[wft.getName()] = wft; 
}

void Parser::waveform_table_item(Stil::WaveformTable& wft) {
		if (la->kind == 29) {
			period_item(wft);
		} else if (la->kind == 31) {
			waveforms_block(wft);
		} else if (la->kind == 30) {
			inherit_item(wft);
		} else SynErr(50);
}

void Parser::period_item(Stil::WaveformTable& wft) {
		Expect(29);
		Expect(8);
		cout << "Period " << t->val << "\t"; wft.period = t->val; cout << wft.period.eval() << endl; 
		Expect(3);
}

void Parser::waveforms_block(Stil::WaveformTable& wft) {
		Expect(31);
		Expect(16);
		waveforms_item();
		while (la->kind == 5 || la->kind == 7 || la->kind == 8) {
			waveforms_item();
		}
		Expect(17);
}

void Parser::inherit_item(Stil::WaveformTable& wft) {
		Expect(30);
		identifier();
		Expect(3);
}

void Parser::waveforms_item() {
		sigref_expr();
		string sigName = t->val; Stil::WaveformTable::WfcList wfcList; 
		Expect(16);
		waveform_item();
		while (StartOf(2)) {
			waveform_item();
		}
		Expect(17);
}

void Parser::waveform_item() {
		wfcs();
		Stil::WaveformTable::EventList eventList; string pinGroup = t->val; 
		Expect(16);
		wfcs_def();
		while (la->kind == 8) {
			wfcs_def();
		}
		Expect(17);
}

void Parser::wfcs() {
		wfc();
		while (StartOf(2)) {
			wfc();
		}
}

void Parser::wfcs_def() {
		string exprStr; vector<State> stateVec; 
		Expect(8);
		exprStr = t->val; 
		events(stateVec);
		Expect(3);
		
}

void Parser::events(vector<State>& stateVec ) {
		event(stateVec);
		while (la->kind == 32) {
			Get();
			event(stateVec);
		}
}

void Parser::event(vector<State>& stateVec ) {
		if (la->kind == 5 || la->kind == 7) {
			identifier();
			string text = t->val;
			if(text.size() == 1) {
			  switch(text[0]) {
			    case FORCE_LOW:       stateVec.push_back(FORCE_LOW);       break;
			    case FORCE_HIGH:      stateVec.push_back(FORCE_HIGH);      break;
			    case FORCE_Z:         stateVec.push_back(FORCE_Z);         break;
			    case FORCE_UNKNOWN:   stateVec.push_back(FORCE_UNKNOWN);   break;
			    case FORCE_OFF:       stateVec.push_back(FORCE_OFF);       break;
			    case COMPARE_LOW:     stateVec.push_back(COMPARE_LOW);     break;
			    case COMPARE_HIGH:    stateVec.push_back(COMPARE_HIGH);    break;
			    case COMPARE_Z:       stateVec.push_back(COMPARE_Z);       break;
			    case COMPARE_UNKNOWN: stateVec.push_back(COMPARE_UNKNOWN); break;
			    case UNKNOWN_LOW:     stateVec.push_back(UNKNOWN_LOW);     break;
			    case UNKNOWN_HIGH:    stateVec.push_back(UNKNOWN_HIGH);    break;
			    case UNKNOWN:         stateVec.push_back(UNKNOWN);         break;
			    default: stateVec.push_back(UNKNOWN);
			  }
			}
			
		} else if (la->kind == 9) {
			Get();
			stateVec.push_back(FORCE_LOW); 
		} else if (la->kind == 10) {
			Get();
			stateVec.push_back(FORCE_HIGH); 
		} else if (la->kind == 33) {
			Get();
			stateVec.push_back(UNKNOWN); 
		} else if (la->kind == 11) {
			Get();
			stateVec.push_back(UNKNOWN); 
		} else SynErr(51);
}

void Parser::wfc() {
		if (la->kind == 1) {
			Get();
		} else if (la->kind == 5 || la->kind == 7) {
			identifier();
		} else if (la->kind == 34) {
			Get();
		} else if (la->kind == 35) {
			Get();
		} else SynErr(52);
}

void Parser::category_block(Spec& spec) {
		Expect(37);
		identifier();
		Category cat; cat.setName(t->val); cout << "Category " << t->val << endl; 
		Expect(16);
		category_item(cat);
		while (la->kind == 5 || la->kind == 7) {
			category_item(cat);
		}
		Expect(17);
		spec.categories[cat.getName()] = cat; 
}

void Parser::category_item(Category& cat) {
		identifier();
		SpecItem specItem(t->val); 
		if (la->kind == 26) {
			Get();
			if (la->kind == 8) {
				Get();
			} else if (la->kind == 7) {
				Get();
			} else SynErr(53);
			specItem.setExprString(t->val); 
			Expect(3);
		} else if (la->kind == 16) {
			Get();
			min_spec(specItem);
			typ_spec(specItem);
			specItem.setExprString(specItem.typExpr.str); 
			max_spec(specItem);
			Expect(17);
		} else SynErr(54);
		cat.specs[specItem.getName()] = specItem; 
}

void Parser::min_spec(SpecItem& specItem) {
		Expect(38);
		Expect(8);
		specItem.minExpr = t->val; 
		Expect(3);
}

void Parser::typ_spec(SpecItem& specItem) {
		Expect(39);
		Expect(8);
		specItem.typExpr = t->val; 
		Expect(3);
}

void Parser::max_spec(SpecItem& specItem) {
		Expect(40);
		Expect(8);
		specItem.maxExpr = t->val; 
		Expect(3);
}

void Parser::selector_item() {
		identifier();
		if (la->kind == 38) {
			Get();
		} else if (la->kind == 39) {
			Get();
		} else if (la->kind == 40) {
			Get();
		} else SynErr(55);
		Expect(3);
}



void Parser::Parse() {
	t = NULL;
	la = dummyToken = new Token();
	la->val = coco_string_create("Dummy Token");
	Get();
	Stil();

	Expect(0);
}

Parser::Parser(Scanner *scanner) {
	maxT = 42;

	dummyToken = NULL;
	t = la = NULL;
	minErrDist = 2;
	errDist = minErrDist;
	this->scanner = scanner;
	errors = new Errors();
}

bool Parser::StartOf(int s) {
	const bool T = true;
	const bool x = false;

	static bool set[3][44] = {
		{T,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x},
		{x,x,x,x, x,x,T,x, x,x,x,x, x,x,x,T, x,x,x,x, x,x,x,x, x,T,x,T, x,x,x,x, x,x,x,x, T,x,x,x, x,T,x,x},
		{x,T,x,x, x,T,x,T, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,x,x, x,x,T,T, x,x,x,x, x,x,x,x}
	};



	return set[s][la->kind];
}

Parser::~Parser() {
	delete errors;
	delete dummyToken;
}

Errors::Errors() {
	count = 0;
}

void Errors::SynErr(int line, int col, int n) {
	char* s;
	switch (n) {
			case 0: s = coco_string_create("EOF expected"); break;
			case 1: s = coco_string_create("integer expected"); break;
			case 2: s = coco_string_create("decimal expected"); break;
			case 3: s = coco_string_create("semi expected"); break;
			case 4: s = coco_string_create("range expected"); break;
			case 5: s = coco_string_create("IDENTIFIER expected"); break;
			case 6: s = coco_string_create("TODO expected"); break;
			case 7: s = coco_string_create("string expected"); break;
			case 8: s = coco_string_create("expr_string expected"); break;
			case 9: s = coco_string_create("ForceDown expected"); break;
			case 10: s = coco_string_create("ForceUp expected"); break;
			case 11: s = coco_string_create("Unknown expected"); break;
			case 12: s = coco_string_create("lbracket expected"); break;
			case 13: s = coco_string_create("rbracket expected"); break;
			case 14: s = coco_string_create("\"STIL\" expected"); break;
			case 15: s = coco_string_create("\"Signals\" expected"); break;
			case 16: s = coco_string_create("\"{\" expected"); break;
			case 17: s = coco_string_create("\"}\" expected"); break;
			case 18: s = coco_string_create("\"ScanIn\" expected"); break;
			case 19: s = coco_string_create("\"ScanOut\" expected"); break;
			case 20: s = coco_string_create("\"InOut\" expected"); break;
			case 21: s = coco_string_create("\"Out\" expected"); break;
			case 22: s = coco_string_create("\"In\" expected"); break;
			case 23: s = coco_string_create("\"Supply\" expected"); break;
			case 24: s = coco_string_create("\"Pseudo\" expected"); break;
			case 25: s = coco_string_create("\"SignalGroups\" expected"); break;
			case 26: s = coco_string_create("\"=\" expected"); break;
			case 27: s = coco_string_create("\"Timing\" expected"); break;
			case 28: s = coco_string_create("\"WaveformTable\" expected"); break;
			case 29: s = coco_string_create("\"Period\" expected"); break;
			case 30: s = coco_string_create("\"InheritWaveformTable\" expected"); break;
			case 31: s = coco_string_create("\"Waveforms\" expected"); break;
			case 32: s = coco_string_create("\"/\" expected"); break;
			case 33: s = coco_string_create("\"?\" expected"); break;
			case 34: s = coco_string_create("\"#\" expected"); break;
			case 35: s = coco_string_create("\"%\" expected"); break;
			case 36: s = coco_string_create("\"Spec\" expected"); break;
			case 37: s = coco_string_create("\"Category\" expected"); break;
			case 38: s = coco_string_create("\"Min\" expected"); break;
			case 39: s = coco_string_create("\"Typ\" expected"); break;
			case 40: s = coco_string_create("\"Max\" expected"); break;
			case 41: s = coco_string_create("\"Selector\" expected"); break;
			case 42: s = coco_string_create("??? expected"); break;
			case 43: s = coco_string_create("invalid stil_block"); break;
			case 44: s = coco_string_create("invalid signals_item"); break;
			case 45: s = coco_string_create("invalid signals_item"); break;
			case 46: s = coco_string_create("invalid signal_type"); break;
			case 47: s = coco_string_create("invalid identifier"); break;
			case 48: s = coco_string_create("invalid sigref_expr"); break;
			case 49: s = coco_string_create("invalid signal_name_array_opt"); break;
			case 50: s = coco_string_create("invalid waveform_table_item"); break;
			case 51: s = coco_string_create("invalid event"); break;
			case 52: s = coco_string_create("invalid wfc"); break;
			case 53: s = coco_string_create("invalid category_item"); break;
			case 54: s = coco_string_create("invalid category_item"); break;
			case 55: s = coco_string_create("invalid selector_item"); break;

		default:
		{
			char format[20];
			coco_sprintf(format, 20, "error %d", n);
			s = coco_string_create(format);
		}
		break;
	}
	printf("-- line %d col %d: %s\n", line, col, s);
	coco_string_delete(s);
	count++;
}

void Errors::Error(int line, int col, const char *s) {
	printf("-- line %d col %d: %s\n", line, col, s);
	count++;
}

void Errors::Warning(int line, int col, const char *s) {
	printf("-- line %d col %d: %s\n", line, col, s);
}

void Errors::Warning(const char *s) {
	printf("%s\n", s);
}

void Errors::Exception(const char* s) {
	printf("%s", s); 
	exit(1);
}



