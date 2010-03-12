
#include "Stil.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

template<class Type>
string toString(const Type& val) {
    string str;
    stringstream sstr;
    sstr << val;
    str = sstr.str();
    return str;
}

namespace Stil {

    SymbolTable::SymbolTable() {
    }

    bool SymbolTable::add(Object& obj) {
        bool result = true;

        if(exists(obj.getName()))
            return false;

        return result;
    }
#if 0
    bool SymbolTable::add(string name, string scope) {
        bool result = true;

        return result;
    }
#endif

    bool SymbolTable::exists(string name) {
        bool result = false;

        return result;
    }

    Signal::Signal(string instName) : Object(STIL_SIGNAL) {
        name = instName;
        _subType = PSEUDO;
    }

	Signal::Signal(string instName, SignalType type) : Object(STIL_SIGNAL), _subType(type) {
        name = instName;
	}


	Signal::Signal(string instName, string type) : Object(STIL_SIGNAL) {
        name = instName;

        if(type == "InOut") _subType = INOUT;
        else if(type == "Out") _subType = OUTPUT;
        else if(type == "In") _subType = INPUT;
        else if(type == "Supply") _subType = SUPPLY;
        else if(type == "Pseudo") _subType = PSEUDO;
        else _subType = PSEUDO;
	}

    void Signal::setSignalType( string type) {
        if(type == "InOut") _subType = INOUT;
        else if(type == "Out") _subType = OUTPUT;
        else if(type == "In") _subType = INPUT;
        else if(type == "Supply") _subType = SUPPLY;
        else if(type == "Pseudo") _subType = PSEUDO;
        else ;
    }

	Signals::Signals() : Object(STIL_SIGNALS) {
	}

	bool Signals::addSignal(Signal signal) {
		bool result = true;

		if(signalMap.find(signal.getName()) == signalMap.end()) {
			signalMap[signal.getName()] = signal;
		}
		else
			result = false;

        SymbolTable symTab = SymbolTable::getReference();
        symTab.add(signal);

		return result;
	}

    bool Signals::addSignal(string name, SignalType type) {
        Signal signal( name, type);

        return addSignal(signal);
    }

    string GroupsItem::toStil() {
        string str;

        str += name + " = " + expr + "\n";

        return str;
    }

    SignalGroups::SignalGroups() : Object(STIL_SIGNALGROUPS) {
    }

    string SignalGroups::toStil() {
        string str;

        str += "SignalGroups " + getName() + " {\n";
        map<string, GroupsItem>::iterator iter;
        for(iter = groups.begin(); iter != groups.end(); iter++) {
            str += indent + (*iter).second.toStil();
        }
        str += "}\n";
        
        return str;
    }

    bool SignalGroups::add( string name, string expr) {
        bool result = true;

        SymbolTable& symTab = SymbolTable::getReference();
        if(symTab.exists(name))
            return false;

        GroupsItem gi;
        gi.setName(name);
        gi.expr = expr;

        groups[name] = gi;

        symTab.add(gi);

        return result;
    }

    long unsigned int SpecItem::count = 0;

    double SpecItem::setExprString(string exprStr) {
        double result = 0.0;

        expr = exprStr;
        result = expr.eval();

        Expr assignExpr;
        assignExpr.str = name + " = " + toString(result);
        cout << assignExpr.str << endl;
        assignExpr.eval();

        return result;
    }

    string SpecItem::toStil() {
        string str;

        Expr tempExpr = expr;

        str += indent + indent + name + " = '" + expr.str + "'; // " + toString(tempExpr.eval()) + " \n";

        return str;
    }

    string Category::toStil() {
        string str;

        str += indent + "Category " + name + " {\n";

        Collection<SpecItem>::iterator iter;
        for(iter = specs.begin(); iter != specs.end(); iter++) {
            str += iter->second.toStil();
        }

        str += indent + "}\n";

        return str;
    }

    Spec::Spec() : Object(STIL_SPEC) {
    }

    string Spec::toStil() {
        string str;

        str += "Spec " + name + " {\n";

        Collection<Category>::iterator iter;
        for(iter = categories.begin(); iter != categories.end(); iter++) {
            str += iter->second.toStil();
        }

        str += "}\n";

        return str;
    }

    WaveformTable::WaveformTable() : Object(STIL_WAVEFORMTABLE) {
    }
    WaveformTable::WaveformTable(string wftName) : Object(STIL_WAVEFORMTABLE) {
        setName(wftName);
    }

    void WaveformTable::clear(void) {
        waveforms.clear();
        name = "";
        period = 0.0;
    }

    string WaveformTable::toStil() {
        string str;

        str += "// \n";
        //str += "// Resolution : " + toString(getEventResolution()) + " \n";
        str += "// \n";

        str += "WaveformTable " + name + " {\n";

        str += indent + "Period '" + period.str + "'; // " + toString(period.eval()) + "\n";

        str += indent + "Waveforms {\n";
        map<string, WfcList>::iterator iter;
        for(iter = waveforms.begin(); iter != waveforms.end(); iter++) {
            str += indent + indent + iter->first + "\n";
        }
        str += indent + "}\n";

        str += "}\n";

        return str;
    }
    void WaveformTable::print( ostream& os) {

        os << toStil() << endl;
    }
    void WaveformTable::getEvents( string pinName, char wfc, EventList& events) {

        if(waveforms.find(pinName) != waveforms.end()) {
            if(waveforms[pinName].find(wfc) != waveforms[pinName].end())
                events = waveforms[pinName][wfc];
        }
    }

    double WaveformTable::getEventResolution() {
        double minRes = period.eval();

        vector<double> timeCollection;

        map<string, WfcList>::iterator iterWave;
        for(iterWave = waveforms.begin(); iterWave != waveforms.end(); iterWave++) {
            WfcList::iterator iterWfc;
            for(iterWfc = iterWave->second.begin(); iterWfc != iterWave->second.end(); iterWfc++) {
                //EventList::iterator iterWfcChar;
                //for(iterWfcChar = iterWfc->second.begin(); iterWfcChar != iterWfc->second.end(); iterWfcChar++) {
                //    timeCollection.push_back(iterWfcChar->first.eval());
                //}
                EventList evList = (iterWfc->second);
                EventList::iterator iter;
                for(iter = evList.begin(); iter != evList.end(); iter++) {
                    Expr expr = iter->first;
                    timeCollection.push_back(expr.eval());
                }
            }
        }

        sort( timeCollection.begin(), timeCollection.end());
        vector<double> uniqueTimeCollection;
        unique_copy( timeCollection.begin(), timeCollection.end(), back_inserter(uniqueTimeCollection));

        for(unsigned int i=0; i < (uniqueTimeCollection.size() - 1); i++) {
            double res = fabs(uniqueTimeCollection[i+1] - uniqueTimeCollection[i]);
            minRes     = min( res, minRes);
        }

        return minRes;
    }

}

