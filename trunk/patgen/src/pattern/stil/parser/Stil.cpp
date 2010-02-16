
#include "Stil.h"

namespace Stil {

    Signal::Signal() {
        _type = PSEUDO;
    }

	Signal::Signal(string name, Type type) : _name(name), _type(type) {
	}


	Signal::Signal(string name, string type) : _name(name) {
        if(type == "InOut")
            _type = INOUT;
        else if(type == "Out")
            _type = OUTPUT;
        else if(type == "In")
            _type = INPUT;
        else if(type == "Supply")
            _type = SUPPLY;
        else if(type == "Pseudo")
            _type = PSEUDO;
        else
            _type = PSEUDO;
	}

	Signals::Signals() {
	}

	bool Signals::addSignal(Signal signal) {
		bool result = true;

		if(signalMap.find(signal.getName()) == signalMap.end()) {
			signalMap[signal.getName()] = signal;
		}
		else
			result = false;

		return result;
	}

    bool Signals::addSignal(string name, Signal::Type type) {
        Signal signal( name, type);

        return addSignal(signal);
    }

}

