
#include "Stil.h"
#include <iostream>
#include <sstream>

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

    Signal::Signal(string name) : Object(STIL_SIGNAL) {
        _name = name;
        _subType = PSEUDO;
    }

	Signal::Signal(string name, SignalType type) : Object(STIL_SIGNAL), _subType(type) {
        _name = name;
	}


	Signal::Signal(string name, string type) : Object(STIL_SIGNAL) {
        _name = name;

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

        str += _name + " = " + expr + "\n";

        return str;
    }

    SignalGroups::SignalGroups() : Object(STIL_SIGNALGROUPS) {
    }

    string SignalGroups::toStil() {
        string str;

        str += "SignalGroups " + getName() + " {\n";
        string indent = "\t";
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
        assignExpr.str = _name + " = " + toString(result);
        cout << assignExpr.str << endl;
        assignExpr.eval();

        return result;
    }

    string SpecItem::toStil() {
        string str;

        string indent = "\t";

        Expr tempExpr = expr;

        str += indent + indent + _name + " = " + expr.str + "; // " + toString(tempExpr.eval()) + " \n";

        return str;
    }

    string Category::toStil() {
        string str;

        string indent = "\t";
        str += indent + "Category " + _name + " {\n";

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

        str += "Spec " + _name + " {\n";

        Collection<Category>::iterator iter;
        for(iter = categories.begin(); iter != categories.end(); iter++) {
            str += iter->second.toStil();
        }

        str += "}\n";

        return str;
    }

}

