#ifndef __STIL_STIL_H__
#define __STIL_STIL_H__

#include <map>
#include <string>

using namespace std;

namespace Stil {

	class Signal {
		public:
			enum Type { INOUT, INPUT, OUTPUT, SUPPLY, PSEUDO };

            Signal();
			Signal(string name, Type type);
			Signal(string name, string type);
            string getName(void) { return _name; }
            Type   getType(void) { return _type; }

        private:
			string _name;
			Type   _type;
	};

	class Signals {
		public:
			Signals();

			bool addSignal(Signal signal);
			bool addSignal(string name, Signal::Type type);

		protected:
			map<string, Signal> signalMap;
	};
}

#endif

