
#include "common.h"

#include <string>
#include <map>
#include <cmath>

using namespace std;

void SignalInfo::print(ostream& os, std::string delim) {
    os << name  << delim;
    os << scope << delim;
    os << type  << delim;
}

void SignalInfo::print(vector<SignalInfo>& header, ostream& os, std::string delim) {
    for(unsigned int i=0; i < header.size(); i++) {
		os << header[i].name  << delim;
		os << header[i].scope << delim;
		os << header[i].type  << delim;
		os << endl;
    }
}

std::ostream& operator<<(std::ostream& os, SignalInfo& info) {
    info.print(os);

    return os;
}


void reorderSignalHeader( SignalHeader& signalHeader, const vector<string>& pinOrder) {
    map<string, unsigned int> found;
    vector< pair<string, unsigned int> > notFound;

    for(unsigned int i=0; i < signalHeader.size(); i++) {
        string name = signalHeader[i].name;
        vector<string>::const_iterator iter = std::find( pinOrder.begin(), pinOrder.end(), name);
        if(iter != pinOrder.end())
            found[name] = i;
        else
            notFound.push_back( make_pair(name, i) );
    }

    SignalHeader newSignalHeader;
    for(unsigned int i=0; i < pinOrder.size(); i++) {
        string name = pinOrder[i];
        if(found.find(name)!= found.end()) {
            newSignalHeader.push_back( signalHeader[found[name]]);
        }
    }

    for(unsigned int i=0; i < notFound.size(); i++) {
        newSignalHeader.push_back( signalHeader[ notFound[i].second]);
    }

    for(unsigned int i=0; i < newSignalHeader.size(); i++) {
        newSignalHeader[i].index = i;
    }

    signalHeader = newSignalHeader;
}
		
CommonData::CommonData() {
}

CommonData::~CommonData() {
}


void CommonData::setName(std::string str) {
    name = str; 
}

string  CommonData::getName(void) {
    return name; 
}

bool CommonData::setSignalHeader(const SignalHeader& header) {
    signalHeader = header;
    return true;
}

SignalHeader CommonData::getSignalHeader() {
    return signalHeader; 
}

double my_round(double value) {
    double fracPart, intPart;

    fracPart = std::modf( value, &intPart);

    double round = intPart;

    if(fracPart > 0.5)
        round = intPart + 1.0;

    return round;
}

vector<string> getNames(const SignalHeader& header) {
    vector<string> names;
    SignalHeader::const_iterator iter;
    for(iter = header.begin(); iter != header.end(); iter++) {
        names.push_back(iter->name);
    }
    return names;
}

void horizToVert( const vector<string>& input, vector<string>& output, unsigned int align) {
    unsigned int maxLength = 0;
    for(unsigned int i=0; i < input.size(); i++) {
        if(input[i].size() > maxLength)
            maxLength = input[i].size();
    }

    vector<string> tempInput( input.size(), string( maxLength, ' '));
    vector<string> tempOutput( maxLength, string( input.size(), ' '));

    for(unsigned int i=0; i < input.size(); i++) {
        for(unsigned int j=0; j < input[i].size(); j++) {
            switch(align) {
                case 0: // Left, Top
                    tempInput[i][j] = input[i][j]; break;
                case 1: // Center
                    tempInput[i][j] = input[i][j]; break;
                case 2: // Right, Bottom
                    tempInput[i][j + (maxLength-input[i].size())] = input[i][j]; break;
                default: // Left, Top
                    tempInput[i][j] = input[i][j];
            }
        }
    }

    for(unsigned int i=0; i < tempInput.size(); i++) {
        string str = tempInput[i];
        for(unsigned int j=0; j < str.size(); j++) {
            tempOutput[j][i] = str[j];
        }
    }

    output = tempOutput;
}

//void getSignalHeaderNames( const SignalHeader& signalHeader, vector<string>& names, bool vertical) {
//    vector<string> signalNames;
//
//    signalNames = getNames(signalHeader);
//
//    horizToVert( signalNames, names);
//}

