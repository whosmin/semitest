
#include "Stil.h"
#include <iostream>

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

    Spec::Spec() : Object(STIL_SPEC) {
    }

}

