#include "evcdWriter.h"
//#include "appLogger.h"
#include <ctime>

void stateToEvcdState( State state, char& ch, unsigned int& str0, unsigned int& str1) {
    switch(state) {
        case FORCE_LOW       : ch = 'D'; str0 = 6; str1 = 0; break;
        case FORCE_HIGH      : ch = 'U'; str0 = 0; str1 = 6; break;
        case FORCE_Z         : ch = 'Z'; str0 = 0; str1 = 0; break;
        case FORCE_UNKNOWN   : ch = 'N'; str0 = 6; str1 = 6; break;
        case FORCE_OFF       : ch = 'Z'; str0 = 0; str1 = 0; break;
        case COMPARE_LOW     : ch = 'L'; str0 = 6; str1 = 0; break;
        case COMPARE_HIGH    : ch = 'H'; str0 = 0; str1 = 6; break;
        case COMPARE_Z       : ch = 'T'; str0 = 0; str1 = 0; break;
        case COMPARE_UNKNOWN : ch = 'X'; str0 = 6; str1 = 6; break;
        case UNKNOWN_LOW     : ch = '0'; str0 = 6; str1 = 6; break;
        case UNKNOWN_HIGH    : ch = '1'; str0 = 6; str1 = 6; break;
        case UNKNOWN         : ch = '?'; str0 = 6; str1 = 6; break;
        default              : ch = ' '; str0 = 0; str1 = 0;
    };
}

const string EvcdWriter::fileExt = "evcd";

EvcdWriter::EvcdWriter()
{
    indent = "\t";
    sep    = "  ";
}

void EvcdWriter::setTopScope( string scope) {
    topScope = scope;
}

//void EvcdWriter::setTimescale(double value) {
//    TraceWriter::setTimescale(value);
//}

void EvcdWriter::write( ostream& os, EventData& evData,
        unsigned long long startTime, unsigned long long stopTime)
{
    //AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());

    time_t rawtime;
    time(&rawtime);
    struct tm * timeinfo = localtime( &rawtime);
    string dateString = asctime(timeinfo);

    double       evTimescale      = evData.getTimescale();
    unsigned int evTimescaleDigit = 1;
    string       evTimescaleUnit;
    doubleToTimescale( evTimescale, evTimescaleDigit, evTimescaleUnit);

//    double unitVal = 1.0;
//    if(evTimescale < 1e-15) {
//    }
//    else if(evTimescale < 1e-12) {
//        unitVal       = 1e-15;
//        evTimescaleUnit = "fs";
//    }
//    else if(evTimescale < 1e-9) {
//        unitVal       = 1e-12;
//        evTimescaleUnit = "ps";
//    }
//    else if(evTimescale < 1e-6) {
//        unitVal       = 1e-9;
//        evTimescaleUnit = "ns";
//    }
//    else if(evTimescale < 1e-3) {
//        unitVal       = 1e-6;
//        evTimescaleUnit = "us";
//    }
//    else if(evTimescale < 1) {
//        unitVal       = 1e-3;
//        evTimescaleUnit = "ms";
//    }
//
//    evTimescaleDigit = (unsigned int) my_round(evTimescale / unitVal);

    if(timescale == 0.0) {
    }

    //applog.debug << "Timescale : (double) " << evTimescale << endl;

    for(unsigned int i=0; i < comments.size(); i++) {
        os << "$comment" << endl;
        os << indent     << comments[i] << endl;
        os << "$end"     << endl << endl;
    }

    os << "$date"      << endl;
    os << indent       << dateString << endl;
    os << "$end"       << endl << endl;

    os << "$timescale" << endl;
    os << indent       << evTimescaleDigit << " " << evTimescaleUnit  << endl;
    os << "$end"       << endl << endl;

    SignalHeader signalHeader = evData.getSignalHeader();

    printSignalHeader( os, signalHeader);

    os << "$enddefinitions $end" << endl << endl;

    map<string, SignalInfo> signalHeaderMap;
    for(unsigned int i=0; i < signalHeader.size(); i++) {
        signalHeaderMap[signalHeader[i].name] = signalHeader[i];
    }

    EventData::DataContainerType::iterator iter;
    for(iter = evData.data.begin(); iter != evData.data.end(); iter++) {
        unsigned long long timestamp = iter->first;

        os << endl;
        os << "#" << timestamp << endl;

        bool dumpports = false;
        if(timestamp == 0 && iter->second.size() == signalHeader.size()) {
            dumpports = true;
        }

        if(dumpports)
            os << "$dumpports" << endl;
        {
            for(unsigned int i=0; i < iter->second.size(); i++) {
                string name  = iter->second[i].first;
                State  state = iter->second[i].second;

                char ch; unsigned int strength0, strength1;
                stateToEvcdState( state, ch, strength0, strength1);
                os << "p" << ch << sep << strength0 << sep << strength1 << sep << signalHeaderMap[name].alias << endl;
            }
        }
        if(dumpports)
            os << "$end" << endl;
    }

}

bool compareSignalInfo( const SignalInfo a, const SignalInfo b) {
    return a.scope < b.scope;
}

void EvcdWriter::printSignalHeader( ostream& os, SignalHeader& signalHeader) {
    if(topScope != "") {
        os << "$scope module " << topScope << " $end" << endl;
        for(unsigned int i=0; i < signalHeader.size(); i++) {
            os << "$var"
               << sep << signalHeader[i].type
               << sep << signalHeader[i].size
               << sep << signalHeader[i].alias
               << sep << signalHeader[i].name
               << sep << "$end" << endl;
        }
        os << "$upscope $end" << endl << endl;
    }
    else {
        map<string, vector<SignalInfo> > scopeToSignalInfo;
        for(unsigned int i=0; i < signalHeader.size(); i++) {
            scopeToSignalInfo[signalHeader[i].scope].push_back(signalHeader[i]);
        }
//        sort( signalHeader.begin(), signalHeader.end(), compareSignalInfo);

        map<string, vector<SignalInfo> >::iterator iter;
        for(iter = scopeToSignalInfo.begin(); iter != scopeToSignalInfo.end(); iter++) {
            string scopeStr = iter->first;
            os << "$scope module " << scopeStr << " $end" << endl;
            for(unsigned int i=0; i < iter->second.size(); i++) {
                SignalInfo info = iter->second[i];
                os << "$var"
                   << sep << info.type
                   << sep << info.size
                   << sep << info.alias
                   << sep << info.name
                   << sep << "$end" << endl;
            }
            os << "$upscope $end" << endl << endl;
        }
    }
}


