

#if !defined(COCO_PARSER_H__)
#define COCO_PARSER_H__

#include "Stil.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

using namespace Stil;
using namespace std;


#include "Scanner.h"



class Errors {
public:
	int count;			// number of errors detected

	Errors();
	void SynErr(int line, int col, int n);
	void Error(int line, int col, const char *s);
	void Warning(int line, int col, const char *s);
	void Warning(const char *s);
	void Exception(const char *s);

}; // Errors

class Parser {
private:
	enum {
		_EOF=0,
		_integer=1,
		_decimal=2,
		_semi=3,
		_range=4,
		_IDENTIFIER=5,
		_TODO=6,
		_string=7,
		_expr_string=8,
		_ForceDown=9,
		_ForceUp=10,
		_Unknown=11,
		_lbracket=12,
		_rbracket=13
	};
	int maxT;

	Token *dummyToken;
	int errDist;
	int minErrDist;

	void SynErr(int n);
	void Get();
	void Expect(int n);
	bool StartOf(int s);
	void ExpectWeak(int n, int follow);
	bool WeakSeparator(int n, int syFol, int repFol);

public:
	Scanner *scanner;
	Errors  *errors;

	Token *t;			// last recognized token
	Token *la;			// lookahead token

Stil::SymbolTable            table;
    Stil::Signals                signals;
    //Stil::Signals*                pSignals;
    Stil::Collection<Stil::Spec>* pSpecCollection;
    Stil::Collection<Stil::WaveformTable> wftCollection;
    Stil::SignalGroups*          pSignalGroups; // TODO : Replace this with a Collection object

    std::map<std::string,std::string> symTab;
    int level;
    string tempString;

    Collection<Stil::WaveformTable>& getWftCollection() { return wftCollection; }



	Parser(Scanner *scanner);
	~Parser();
	void SemErr(const char* msg);

	void Stil();
	void stil_version();
	void stil_block();
	void signals_block();
	void signalgroups_block();
	void timing_block();
	void spec_block();
	void selector_block();
	void signals_list();
	void signals_item();
	void signal_name();
	void signal_type();
	void identifier();
	void groups_list();
	void groups_item();
	void sigref_expr();
	void signal_name_array_opt();
	void timing_items();
	void timing_item();
	void waveform_table();
	void waveform_table_item(Stil::WaveformTable& wft);
	void period_item(Stil::WaveformTable& wft);
	void waveforms_block(Stil::WaveformTable& wft);
	void inherit_item(Stil::WaveformTable& wft);
	void waveforms_item();
	void waveform_item();
	void wfcs();
	void wfcs_def();
	void events();
	void event();
	void wfc();
	void category_block(Spec& spec);
	void category_item(Category& cat);
	void min_spec(SpecItem& specItem);
	void typ_spec(SpecItem& specItem);
	void max_spec(SpecItem& specItem);
	void selector_item();

	void Parse();

}; // end Parser



#endif // !defined(COCO_PARSER_H__)

