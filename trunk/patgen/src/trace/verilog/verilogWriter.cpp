#include "verilogWriter.h"
//#include "appLogger.h"
#include <ctime>

enum StateType {
    TYPE_DRIVE   = 1,
    TYPE_COMPARE = 2,
    TYPE_EXPECT  = 4,
    TYPE_UNKNOWN = 0
};

void stateToVerilogState( State state, char& ch, StateType& type) {
    switch(state) {
        case FORCE_LOW       : ch = '0'; type = TYPE_DRIVE;   break;
        case FORCE_HIGH      : ch = '1'; type = TYPE_DRIVE;   break;
        case FORCE_Z         : ch = 'z'; type = TYPE_DRIVE;   break;
        case FORCE_UNKNOWN   : ch = 'x'; type = TYPE_DRIVE;   break;
        case FORCE_OFF       : ch = 'z'; type = TYPE_DRIVE;   break;
        case COMPARE_LOW     : ch = 'c'; type = TYPE_COMPARE; break; // special compare char 'c'
        case COMPARE_HIGH    : ch = 'c'; type = TYPE_COMPARE; break; // special compare char 'c'
        case COMPARE_Z       : ch = 'c'; type = TYPE_COMPARE; break; // special compare char 'c'
        case COMPARE_UNKNOWN : ch = 'x'; type = TYPE_COMPARE; break;
        case UNKNOWN_LOW     : ch = 'x'; type = TYPE_UNKNOWN; break;
        case UNKNOWN_HIGH    : ch = 'x'; type = TYPE_UNKNOWN; break;
        case UNKNOWN         : ch = 'x'; type = TYPE_UNKNOWN; break;
        default              : ch = 'x'; type = TYPE_UNKNOWN; 
    };
}

VerilogWriter::VerilogWriter() {
    indent         = "\t";
    sep            = "     ";
    module         = true;
    moduleName     = "dtt_tb";
    netNamePrefix  = "n_";
    wireNamePrefix = "w_";
}

void VerilogWriter::setTopScope ( string scope) {
}

const string VerilogWriter::fileExt = "v";

void VerilogWriter::write( ostream& os, EventData& evData,
        unsigned long long startTime, unsigned long long stopTime) {
    //AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());
    //applog.info << __PRETTY_FUNCTION__ << endl;

    double       evTimescale      = evData.getTimescale();
    unsigned int evTimescaleDigit = 1;
    string       evTimescaleUnit;
    doubleToTimescale( evTimescale, evTimescaleDigit, evTimescaleUnit);

    vector<string> pinNames = evData.getSignals();
    map<string, unsigned int> name2index;
    vector<string> netNames, wireNames, portNames;
    for(unsigned int i=0; i < pinNames.size(); i++) {
        string pinName = pinNames[i];
        name2index[pinName] = i;
        netNames.push_back(  netNamePrefix  + pinName);
        wireNames.push_back( wireNamePrefix + pinName);
        portNames.push_back( "p_" + pinName);
    }

//    os << "`timescale" << sep << evTimescaleDigit << sep << evTimescaleUnit << ";" << endl;
//    os << "`ifndef TB_TIME_SCALE" << endl;
//    os << "`define TB_TIME_SCALE 1" << endl;
//    os << "`endif" << endl;
    os << endl;

    string semi = ";";

    if(module) {
        os << "module" << sep << moduleName << sep << "(" << endl;
        for(unsigned int i=0; i < portNames.size(); i++) {
            os << indent << "inout" << sep << portNames[i];
            if(i != (portNames.size() - 1)) os << ",";
            os << endl;
        }
        os << ");" << endl;
        os << endl;
        os << "parameter TB_TIME_SCALE = 1;" << endl;
        os << endl;

        // Print reg
        for(unsigned int i=0; i < netNames.size(); i++) {
            os << indent << "reg" << sep << netNames[i] << semi << endl;
        }
        os << endl;
        // Print wire 
        for(unsigned int i=0; i < wireNames.size(); i++) {
            os << indent << "wire" << sep << wireNames[i] << semi << endl;
        }
        os << endl;
        for(unsigned int i=0; i < portNames.size(); i++) {
            os << indent << "assign" << sep << portNames[i] << indent << " = " << netNames[i] << semi << endl;
        }
        os << endl;
    }


    os << indent << "initial begin" << endl << endl;
    unsigned long long currTimestamp = 0, prevTimestamp = 0;
    unsigned long long deltaTimestamp = 0;
    EventData::DataContainerType::iterator iter;
    for(iter = evData.data.begin(); iter != evData.data.end(); iter++, prevTimestamp = currTimestamp) {
        currTimestamp = iter->first;
        deltaTimestamp = currTimestamp - prevTimestamp;

        if(module)
            os << indent;
//        os << indent << "#(64'd" << deltaTimestamp << " * `TB_TIME_SCALE);" << endl;
        os << indent << "#(64'd" << deltaTimestamp << " * TB_TIME_SCALE);" << endl;

        for(unsigned int i=0; i < iter->second.size(); i++) {
            string pinName = iter->second[i].first;
            State  state   = iter->second[i].second;

            char ch; StateType type;
            stateToVerilogState( state, ch, type);
            if(type != TYPE_COMPARE) {
                os << indent << indent << indent
                   << netNames[name2index[pinName]] << indent << " = " << "1'b" << ch << ";" << endl;
            }
        }
        os << endl;
        os << indent << indent << "$finish;" << endl;
    }

    os << indent << "end" << " // initial begin" << endl;

    if(module) {
        os << "endmodule //" << moduleName << endl;
        os << endl;
    }
}

void VerilogWriter::write2( ostream& os, EventData& evData,
        unsigned long long startTime, unsigned long long stopTime) {
    //AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());
    //applog.info << __PRETTY_FUNCTION__ << endl;

    double       evTimescale      = evData.getTimescale();
    unsigned int evTimescaleDigit = 1;
    string       evTimescaleUnit;
    doubleToTimescale( evTimescale, evTimescaleDigit, evTimescaleUnit);

    vector<string> pinNames = evData.getSignals();
    map<string, unsigned int> name2index;
    vector<string> netNames, wireNames, portNames;
    for(unsigned int i=0; i < pinNames.size(); i++) {
        string pinName = pinNames[i];
        name2index[pinName] = i;
        netNames.push_back(  netNamePrefix  + pinName);
        wireNames.push_back( wireNamePrefix + pinName);
        portNames.push_back( "p_" + pinName);
    }

//    os << "`timescale" << sep << evTimescaleDigit << sep << evTimescaleUnit << ";" << endl;
//    os << "`ifndef TB_TIME_SCALE" << endl;
//    os << "`define TB_TIME_SCALE 1" << endl;
//    os << "`endif" << endl;
    os << endl;

    string semi = ";";

    if(module) {
        os << "module" << sep << moduleName << sep << "(" << endl;
        for(unsigned int i=0; i < portNames.size(); i++) {
            os << indent << "inout" << sep << portNames[i];
            if(i != (portNames.size() - 1)) os << ",";
            os << endl;
        }
        os << ");" << endl;
        os << endl;
        os << "parameter TB_TIME_SCALE = 1;" << endl;
        os << endl;

        // Print reg
        for(unsigned int i=0; i < netNames.size(); i++) {
            os << indent << "reg" << sep << netNames[i] << semi << endl;
        }
        os << endl;
        // Print wire 
//        for(unsigned int i=0; i < wireNames.size(); i++) {
//            os << indent << "wire" << sep << wireNames[i] << semi << endl;
//        }
//        os << endl;
        for(unsigned int i=0; i < portNames.size(); i++) {
            os << indent << "assign" << sep << portNames[i] << indent << " = " << netNames[i] << semi << endl;
        }
        os << endl;
    }


    map<string, vector< pair<unsigned long long, State> > > pinEventData;

    unsigned long long currTimestamp  = 0;
    unsigned long long prevTimestamp  = 0;
    unsigned long long deltaTimestamp = 0;
    EventData::DataContainerType::iterator iter;
    for(iter = evData.data.begin(); iter != evData.data.end(); iter++, prevTimestamp = currTimestamp) {
        currTimestamp = iter->first;
        deltaTimestamp = currTimestamp - prevTimestamp;

        for(unsigned int i=0; i < iter->second.size(); i++) {
            string pinName = iter->second[i].first;
            State  state   = iter->second[i].second;

            pinEventData[pinName].push_back( make_pair(currTimestamp, state) );
        }
    }

    map<string, vector< pair<unsigned long long, State> > >::iterator iterPin;
    for(iterPin = pinEventData.begin(); iterPin != pinEventData.end(); iterPin++) {
        string pinName = iterPin->first;

        if(iterPin->second.size() > 0) {
            unsigned long long currTimestamp  = 0;
            unsigned long long prevTimestamp  = 0;
            unsigned long long deltaTimestamp = 0;
            char currVerilogState = 'x';
            char prevVerilogState = ' ';

            os << endl;
            os << indent << "initial begin" << endl;
            for(unsigned int i=0; i < iterPin->second.size(); i++) {
                unsigned long long currTimestamp = iterPin->second[i].first;
                State              state         = iterPin->second[i].second;
                deltaTimestamp = currTimestamp - prevTimestamp;


                StateType type;
                stateToVerilogState( state, currVerilogState, type);
                if(currVerilogState != prevVerilogState) {
                    os << indent << indent << "#(64'd" << deltaTimestamp << " * TB_TIME_SCALE)";
                    if(type != TYPE_COMPARE) {
                        os << indent << netNames[name2index[pinName]] << indent << " = " << "1'b" << currVerilogState << ";" << endl;
                    }
                    else {
                        os << indent << semi << " // Compare " << (char) state << endl;
                    }
                    deltaTimestamp = 0;
                    prevVerilogState = currVerilogState;
                    prevTimestamp    = currTimestamp;
                }
            }
            os << indent << "end" << " // initial begin for " << pinName << endl;
        }
    }


    if(module) {
        os << "endmodule //" << moduleName << endl;
        os << endl;
    }
}


void VerilogWriter::writePattern( ostream& os, CycleData& cyData,
        unsigned long long startVec,  unsigned long long stopVec) {
}

void VerilogWriter::writeWaveformTable ( ostream& os, WaveformTable& wft, string wftName) {
    
    os << "// " << endl;
    os << "// WaveformTable " << wft.name << endl;
    os << "// " << endl;

    os << "case(index)" << endl;
    map<string, WaveformTable::WfcList>::iterator iter;
    for(iter = wft.waveforms.begin(); iter != wft.waveforms.end(); iter++) {
        string pinName = iter->first;

        os << indent << endl;
    }
    os << "endcase" << endl;
}

void VerilogWriter::writeTiming( ostream& os, map<string, WaveformTable>& wftMap, string timingName) {
}

