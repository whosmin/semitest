#include "evcdReader.h"
//#include "appLogger.h"

EvcdReader::EvcdReader(EventData& data) : evcd::Driver() , evDataRef(data)
{
}

EvcdReader::~EvcdReader()
{
}

bool sortFunction(SignalInfo lhs, SignalInfo rhs) {
	return lhs.index < rhs.index;
}

void EvcdReader::signalEndDefinitions(void)
{
	map< string, SignalInfo>::iterator iter;
	SignalHeader signalHeader;
	for(iter = signalMap.begin(); iter != signalMap.end(); iter++) {
		signalHeader.push_back( iter->second);
	}

	std::sort( signalHeader.begin(), signalHeader.end(), sortFunction);

	evDataRef.setSignalHeader( signalHeader);



	double timescale = timescaleNumber;
	if(timescaleUnit == "fs")      timescale = timescale * 1e-15;
	else if(timescaleUnit == "ps") timescale = timescale * 1e-12;
	else if(timescaleUnit == "ns") timescale = timescale * 1e-9;
	else if(timescaleUnit == "us") timescale = timescale * 1e-6;
	else if(timescaleUnit == "ms") timescale = timescale * 1e-3;
	else if(timescaleUnit == "s")  timescale = timescale * 1;
	else ;

	evDataRef.setTimescale( timescale);
}

//
// .------.-----------.-------.------------------------------------------------------.
// | Char | Direction | Level | Verilog_Description                                  |
// |------+-----------+-------+------------------------------------------------------|
// |  D   | Input     | Low   | low                                                  |
// |  U   | Input     | High  | high                                                 |
// |  N   | Input     | ?     | unknown                                              |
// |  Z   | Input     | Three | three-state                                          |
// |  d   | Input     | Low   | low  (two or more drivers active)                    |
// |  u   | Input     | High  | high (two or more drivers active)                    |
// |------+-----------+-------+------------------------------------------------------|
// |  L   | Output    | Low   | low                                                  |
// |  H   | Output    | High  | high                                                 |
// |  X   | Output    | ?     | unknown (don't care)                                 |
// |  T   | Output    | Three | three-state                                          |
// |  l   | Output    | Low   | low  (two or more drivers active)                    |
// |  h   | Output    | High  | high (two or more drivers active)                    |
// |------+-----------+-------+------------------------------------------------------|
// |  0   | ?         | Low   | low  (both input and output are active with 0 value) |
// |  1   | ?         | High  | high (both input and output are active with 1 value) |
// |  ?   | ?         | ?     | unknown                                              |
// |  F   | ?         | Three | three-state (input and output unconnected)           |
// |  A   | ?         | ?     | unknown (input 0 and output 1)                       |
// |  a   | ?         | ?     | unknown (input 0 and output X)                       |
// |  B   | ?         | ?     | unknown (input 1 and output 0)                       |
// |  b   | ?         | ?     | unknown (input 1 and output X)                       |
// |  C   | ?         | ?     | unknown (input X and output 0)                       |
// |  c   | ?         | ?     | unknown (input X and output 1)                       |
// |  f   | ?         | ?     | unknown (input and output three-stated)              |
// `------^-----------^-------^------------------------------------------------------'
//
State EvcdReader::charToState(char ch) {

    State state = UNKNOWN;
    switch (ch)
    {
    case 'D':
    case 'd':
        state = FORCE_LOW;
        break;
    case 'U':
    case 'u':
        state = FORCE_HIGH;
        break;
    case 'Z':
        state = FORCE_Z;
        break;
    case 'N':
        state = FORCE_UNKNOWN;
        break;
    case 'L':
    case 'l':
        state = COMPARE_LOW;
        break;
    case 'H':
    case 'h':
        state = COMPARE_HIGH;
        break;
    case 'X':
        state = COMPARE_UNKNOWN;
        break;
    case 'T':
        state = COMPARE_Z;
        break;
    default :
        state = UNKNOWN;
    };

    return state;
}

void EvcdReader::signalChanges(void)
{
    vector< pair< string, State > > states;
    vector< pair< string, string > > regStates;

    for (unsigned int i=0; i < currStates.size(); i++)
    {
        string alias = currStates[i].first;
        string name  = signalMap[alias].name;
		string type  = signalMap[alias].type;
        string value = currStates[i].second;

		if(type == "reg") {
			regStates.push_back(make_pair( name, value));
		}
		if(type == "inout" || type == "output" || type == "input" || type == "port") {
			const char ch = toupper(value[0]);

            State state = charToState(ch);

			states.push_back( make_pair( name, state));
		}
    }

//    if (states.size() > 0)
        evDataRef.data[currTime] = states;
//    if (regStates.size() > 0)
        evDataRef.setRegData( regStates, currTime);
}

void EvcdReader::signalEOF(void) {
    unsigned long long stopTime = evDataRef.getStopTime();

    vector< pair< string, State> > empty;
    evDataRef.getLastEventState( empty);

    if(evDataRef.data.find(stopTime) == evDataRef.data.end())
        evDataRef.data[stopTime] = empty;
}

string EvcdReader::binToAscii( string binStr) {
    string asciiStr;

    return asciiStr;
}
void   EvcdReader::signalDumpportsBegin ( void) {
}

void   EvcdReader::signalDumpportsEnd   ( void) {
    vector< pair< string, State > >  states;
    vector< pair< string, string > > regStates;

    map<string, string> name2type;

    //AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());

    for (unsigned int i=0; i < currStates.size(); i++)
    {
        string alias = currStates[i].first;
        string name  = signalMap[alias].name;
		string type  = signalMap[alias].type;
        string value = currStates[i].second;

        name2type[name] = type;
    }

    bool errorFound = false;
	map< string, SignalInfo>::iterator iter;
	for(iter = signalMap.begin(); iter != signalMap.end(); iter++) {
        if(name2type.find(iter->second.name) == name2type.end()) {
            //applog.error << "Signal " << iter->second.name << " does not have a valid entry in the $dumpports statement" << endl;
            errorFound = true;
        }
	}
    if(errorFound)
        exit(1);
}


