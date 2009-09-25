
#include "eventData.h"
#include <iostream>
#include <cassert>
using namespace std;

bool isNetType( string type);
bool isRegType( string type);

EventData::EventData() {
    setTimescale(1.0);
}

EventData::EventData(double timeScale) {
    setTimescale(timeScale);
}

EventData::~EventData() {
}

void EventData::setTimescale(double timeScale) {
    assert(timeScale > 0.0);
    assert(timeScale <= 1.0);

    timescale = timeScale;
}

void EventData::clear() {
    data.clear();
    regData.clear();
    signalHeader.clear();
}

bool EventData::setRegData( vector< pair< string, string> >& value, unsigned long long timestamp) {
    regData[timestamp] = value;

    return true;
}
bool EventData::getRegData( vector< pair< string, string> >& value, unsigned long long timestamp) {
    if(regData.find(timestamp) == regData.end()) {
        value = regData[timestamp];
        return true;
    }
    else
        return false;
}

void EventData::print(ostream& os) {
	printSignalHeader(os);
	printSignalData(os);
}

void EventData::printSignalHeader(ostream& os) {
	const string sep = "\t";

	os << ".--------------------------------------------------------." << endl;
	os << "|                    SignalHeader                        |" << endl;
	os << "'--------------------------------------------------------'" << endl;
    SignalInfo::print( signalHeader, os);
    os << "Timescale : " << scientific << timescale << endl;
}
void EventData::printSignalData(ostream& os) {
	const string sep = "\t";
	os << ".--------------------------------------------------------." << endl;
	os << "|                    SignalData                          |" << endl;
	os << "'--------------------------------------------------------'" << endl;

    printData( os, data);
}

bool EventData::nameToIndex( string signalName, unsigned int &index) {
	bool found = false;
	for(unsigned int i=0; i < signalHeader.size(); i++) {
		if(signalHeader[i].name == signalName) {
			found = true;
			index = i;
			break;
		}
	}

	return found;
}

inline bool isNetType(string type) {
	if(type == "inout" || type == "input" || type == "output" || type == "port")
		return true;

	return false;
}
inline bool isRegType(string type) {
	if(type == "reg")
		return true;
	return false;
}

bool EventData::isNet(string signalName) {
	bool found = false;
	unsigned int index = 0;
	found = nameToIndex( signalName, index);

	if(found == true) 
		return isNetType( signalHeader[index].type);

	return false;
}

bool EventData::isReg(string signalName) {
	bool found = false;
	unsigned int index = 0;
	found = nameToIndex( signalName, index);

	if(found == true) 
		return isRegType( signalHeader[index].type);

	return false;
}

void EventData::removeEmptyTimestamps(void) {
	map<unsigned long long, vector< pair< string, State> > >::iterator iterMap;
	for(iterMap = data.begin(); iterMap != data.end(); iterMap++) {
		if(iterMap->second.size() == 0) data.erase(iterMap);
	}
	map<unsigned long long, vector< pair< string, string> > >::iterator iterReg;
	for(iterReg = regData.begin(); iterReg != regData.end(); iterReg++) {
		if(iterReg->second.size() == 0)
			regData.erase(iterReg);
	}
}

bool EventData::removeSignal(string signalName) {

	bool found = false;
	unsigned int index = 0;
	found = nameToIndex( signalName, index);

	if(found == true) {
		//
		// Delete the signal from the Event data
		//
		if(isNetType(signalHeader[index].type)) {
			map<unsigned long long, vector< pair< string, State> > >::iterator iterMap;
			for(iterMap = data.begin(); iterMap != data.end(); iterMap++) {
				vector< pair< string, State> >::iterator iterVec;
				bool signalFound = false;
				for(iterVec = iterMap->second.begin(); (iterVec != iterMap->second.end()) && (signalFound == false); iterVec++) {
					if(iterVec->first == signalName) {
						iterMap->second.erase(iterVec);
						signalFound = true;
					}
				}
			}
		}
		else if(isRegType(signalHeader[index].type)) {
			map<unsigned long long, vector< pair< string, string> > >::iterator iterMap;
			for(iterMap = regData.begin(); iterMap != regData.end(); iterMap++) {
				vector< pair< string, string> >::iterator iterVec;
				bool signalFound = false;
				for(iterVec = iterMap->second.begin();
						(iterVec != iterMap->second.end()) && (signalFound == false); iterVec++) {
					if(iterVec->first == signalName) {
						iterMap->second.erase(iterVec);
						signalFound = true;
					}
				}
			}
		}
		else {
			cerr << "ERROR : " << __PRETTY_FUNCTION__ << endl;
		}

		//
		// Delete the signal from the Signal Map
		//
		SignalHeader::iterator iter;
		for(iter = signalHeader.begin(); iter != signalHeader.end(); iter++) {
			if(iter->name == signalName) {
				signalHeader.erase(iter);
				break;
			}
		}
	}

	return found;
}

bool EventData::removeSignal(vector<string> signalVec) {
	const unsigned int numSignals = signalVec.size();
	unsigned int numSignalsRemoved = 0;

	for(unsigned int i=0; i < numSignals; i++) {
		if(removeSignal(signalVec[i]) == true)
			numSignalsRemoved++;
	}

	if(numSignalsRemoved == numSignals)
		return true;
	else
		return false;
}

bool EventData::keepSignal(vector<string> signalVec) {
	unsigned int numSignalsRemoved = 0;

	vector<string> removeSignals;

	for(unsigned int i = 0; i < signalHeader.size(); i++) {
		bool match = false;
		for(unsigned int j = 0; j < signalVec.size(); j++) {
			if(signalHeader[i].name == signalVec[j]) {
				match = true;
				break;
			}
		}
		if(match == false)
			removeSignals.push_back( signalHeader[i].name);

	}

	for(unsigned int i=0; i < removeSignals.size(); i++) {
		bool result = removeSignal( removeSignals[i]);
		if(result)
			numSignalsRemoved++;
	}

	return true;
}

unsigned long long EventData::getStopTime(void) {
    DataContainerType::reverse_iterator iter;
	iter = data.rbegin();

	stopTime = iter->first;

    RegContainerType::reverse_iterator riter;
	riter = regData.rbegin();

    if(riter->first > stopTime)
        stopTime = riter->first;

	return stopTime;
}

unsigned int EventData::getNumSignals() {
	return data.size();
}

bool EventData::getRegData( RegContainerType& data, vector<string> regNames) {
    bool result = true;
    unsigned int              numFound = 0;
    map<string, unsigned int> name2index;

    for(unsigned int i=0; i < regNames.size(); i++) {
        if(isReg(regNames[i])) {
            numFound++;
            unsigned int index = 0;
            nameToIndex( regNames[i], index);
            name2index[regNames[i]] = index;
        }
    }

    if(numFound == 0)
        return false;

    RegContainerType::iterator iter;
    for(iter = regData.begin(); iter != regData.end(); iter++) {
        vector< pair< string, string> > currData;
        vector< pair< string, string> >::iterator iterData;
        for(iterData = iter->second.begin(); iterData != iter->second.end(); iterData++) {
            if(name2index.find(iterData->first) != name2index.end()) {
                currData.push_back( *iterData);
            }
        }
        if(currData.size() > 0)
            data[iter->first] = currData;
    }

    return result;
}

bool EventData::getRegData( RegContainerType& data, string regName) {
    vector<string> regNames;
    regNames.push_back(regName);
    return getRegData( data, regNames);
}

bool EventData::printRegData(ostream& os, vector<string> signals) {
    bool                      result   = true;
    unsigned int              numFound = 0;
    map<string, unsigned int> name2index;

    for(unsigned int i=0; i < signals.size(); i++) {
        if(isReg(signals[i])) {
            numFound++;
            unsigned int index = 0;
            nameToIndex( signals[i], index);
            name2index[signals[i]] = index;
        }
    }
    if(numFound < signals.size())
        result = false;

    if(numFound > 0) {
        RegContainerType::iterator iter;
        for(iter = regData.begin(); iter != regData.end(); iter++) {
            for(unsigned int i=0; i < iter->second.size(); i++) {
                string name  = iter->second[i].first;
                string value = iter->second[i].second;
                if(name2index.find(name) != name2index.end()) {
                    os << name << "\t" << value << endl;
                }
            }
        }
    }

    return result;
}

bool EventData::printRegData(ostream& os, string regName) {
    vector<string> regNames;
    regNames.push_back(regName);
    return printRegData( os, regNames);
}

void EventData::getLastEventState ( vector< pair< string, State> >& states) {
    DataContainerType::reverse_iterator iter;

    for(iter = data.rbegin(); iter != data.rend(); iter++) {
        if(iter->second.size() > 0)
            break;
    }

    states = data[iter->first];
}

bool EventData::isValidSignal( const vector<string>& names, vector<bool>& resultVec) {
    bool result = true;
    vector<bool> validVec( names.size(), false);
    unsigned int numInvalid = 0;
    for(unsigned int i=0; i < names.size(); i++) {
        if(!isNet(names[i])) {
            numInvalid++;
            validVec[i] = false;
        }
        else
            validVec[i] = true;
    }

    if(numInvalid > 0)
        result = false;

    resultVec = validVec;

    return result;
}

bool EventData::isValidSignal( const string name) {
    bool           result = false;
    vector<bool>   resultVec;
    vector<string> names;

    names.push_back(name);
    result = isValidSignal( names, resultVec);
    
    return result;
}

vector<string> EventData::getSignals() {
    vector<string> netNames;
    vector<string> regNames;
    for(unsigned int i=0; i < signalHeader.size(); i++) {
        if(isNetType(signalHeader[i].type))
            netNames.push_back( signalHeader[i].name);
        else if(isRegType(signalHeader[i].type))
            regNames.push_back( signalHeader[i].name);
    }

    return netNames;
}

void EventData::add( EventData& eventData, unsigned long long offset) {

    // TODO Check signal headers for new signals being added
    //      And also to check if signal aliases are unique
    DataContainerType::iterator iter;
    for(iter = eventData.data.begin(); iter != eventData.data.end(); iter++) {
        unsigned long long timestamp = offset + iter->first;
        for(unsigned int i=0; i < iter->second.size(); i++) {
            data[timestamp].push_back( iter->second[i]);
        }
    }
}
//ostream& operator<<(ostream& os, EventData::State& state) {
//    switch(state) {
//        case EventData::FORCE_LOW       : os << "D"; break;
//        case EventData::FORCE_HIGH      : os << "U"; break;
//        case EventData::FORCE_Z         : os << "Z"; break;
//        case EventData::FORCE_UNKNOWN   : os << "N"; break;
//        case EventData::COMPARE_LOW     : os << "L"; break;
//        case EventData::COMPARE_HIGH    : os << "H"; break;
//        case EventData::COMPARE_Z       : os << "T"; break;
//        case EventData::COMPARE_UNKNOWN : os << "X"; break;
//        case EventData::UNKNOWN_LOW     : os << "0"; break;
//        case EventData::UNKNOWN_HIGH    : os << "1"; break;
//        default                         : os << "?";
//    };
//
//    return os;
//}

bool isEqual( EventData::DataContainerType& lhs, EventData::DataContainerType& rhs) {
    if(lhs.size() != rhs.size()) {
//        cout << "1 : " << lhs.size() << " " << rhs.size() << endl;
        return false;
    }

    EventData::DataContainerType::iterator iterLhs, iterRhs;
    for(iterLhs = lhs.begin(), iterRhs = rhs.begin(); iterLhs != lhs.end() && iterRhs != rhs.end(); iterLhs++, iterRhs++) {
        if(iterLhs->first != iterRhs->first) {
//            cout << "2 : " << iterLhs->first << " " << iterRhs->first << endl;
            return false;
        }

        if(iterLhs->second.size() != iterRhs->second.size()) {
//            cout << "3" << endl;
            return false;
        }

        unsigned int size = iterLhs->second.size();
        for(unsigned int i=0; i < size; i++) {
            if(iterLhs->second[i].first != iterRhs->second[i].first) {
//                cout << "4" << endl;
                return false;
            }
            if(iterLhs->second[i].second != iterRhs->second[i].second) {
//                cout << "5" << endl;
                return false;
            }
        }
    }

    return true;
}

void EventData::printData( ostream& os, EventData::DataContainerType& data) {
    EventData::DataContainerType::iterator iter;
	for(iter = data.begin(); iter != data.end(); iter++) {
        os << "#" << iter->first << endl;
        vector< pair< string, State > > states = iter->second;
        for (unsigned int i=0; i < states.size(); i++)
        {
            os << states[i].first << " " << (char) states[i].second << endl;
        }
	}
}

bool EventData::isValidTimestamp  (unsigned long long timestamp) {
    bool found = false;

    if(data.find(timestamp) != data.end()) {
        found = true;
    }

    return found;
}

bool EventData::setData( EventData::DataType value, unsigned long long timestamp, bool overwrite) {
    bool result = isValidTimestamp(timestamp);

    if((result == false) || (overwrite == true)) {
        // TODO Check for valid signals
        data[timestamp] = value;
    }

    return result;
}

