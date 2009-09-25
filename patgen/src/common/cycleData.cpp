
#include "cycleData.h"
//#include "appLogger.h"
#include <boost/progress.hpp>
#include <cassert>

extern bool debug;

//CycleData::PeriodData::PeriodData() { loopCount = 0; }

CycleData::PeriodData& CycleData::PeriodData::operator=(const PeriodData& rhs) {
    wfcVec    = rhs.wfcVec;
    wftRef    = rhs.wftRef;
    loopCount = rhs.loopCount;
    ucode     = rhs.ucode;

    return *this;
}
void CycleData::PeriodData::clear() {
    wftRef    = "";
    loopCount = 0;
    wfcVec.clear();
    ucode.clear();
}
void CycleData::PeriodData::addComment( string comment) {
    ucode.push_back( make_pair("comment", comment));
}
void CycleData::PeriodData::addLabel( string label) {
    ucode.push_back( make_pair("label", label));
}
string CycleData::PeriodData::getLabel() {
    string label;
    for(unsigned int i=0; i < ucode.size(); i++) {
        if(ucode[i].first == "label") {
            label = ucode[i].second;
            break;
        }
    }

    return label;
}
vector<string> CycleData::PeriodData::getLabels() {
    vector<string> labels;
    for(unsigned int i=0; i < ucode.size(); i++) {
        if(ucode[i].first == "label") {
            labels.push_back(ucode[i].second);
        }
    }

    return labels;
}
vector<string> CycleData::PeriodData::getComments() {
    vector<string> comments;
    for(unsigned int i=0; i < ucode.size(); i++) {
        if(ucode[i].first == "comment") {
            comments.push_back( ucode[i].second);
        }
    }

    return comments;
}
string CycleData::PeriodData::getString() {
	string str;
	for(register unsigned int i=0; i<wfcVec.size(); i++) {
		str += wfcVec[i];
	}
	return str;
}
void CycleData::PeriodData::print(ostream& os, string delim) {

	unsigned long cycleCount = 0;
//    for(unsigned int i=0; i<wfcVec.size(); i++) {
//        os << wfcVec[i];
//    }
	os << getString();
    os << delim << wftRef;
}

bool CycleData::PeriodData::operator==(PeriodData& rhs) {
//    return (this->getString() == rhs.getString());
    for(register unsigned int i=0; i < rhs.wfcVec.size(); i++) {
        if(wfcVec[i] != rhs.wfcVec[i])
            return false;
        if(wftRef != rhs.wftRef)
            return false;
    }

    return true;
}

CycleData::CycleData() {
}

CycleData::~CycleData() {
}

void CycleData::clear(void) {
	data.clear();
    signalHeader.clear();
}

bool CycleData::removeSignal ( string signalName) {
	return true;
}

bool CycleData::removeSignal ( vector<string> signalVec) {
	return true;
}

bool CycleData::keepSignal   ( vector<string> signalVec) {

	return true;
}

bool CycleData::setSignalHeader(const SignalHeader& header) {
    bool success = true;

    // TODO: Do some checks

    signalHeader = header;

    return success;
}

void CycleData::addPeriodData( CycleData::PeriodData& periodData) {
	// Do some checks

	// Do some calculations

	// Push data
	data.push_back( periodData);
}

bool CycleData::getPeriodData( CycleData::PeriodData& periodData, unsigned long vecNum) {
	if(vecNum >= data.size())
		return false;

	periodData = data[vecNum];

	return true;
}

bool CycleData::setPeriodData( CycleData::PeriodData& periodData, unsigned long vecNum) {
	if(vecNum >= data.size())
		return false;

    data[vecNum] = periodData;

	return true;
}

void CycleData::print(ostream& os) {
	printSignalHeader(os);
	printSignalData(os);
}


void CycleData::printSignalHeader(ostream& os) {
//    std::for_each( signalHeader.begin(), signalHeader.end(), print_element());
//    print_elements( signalHeader.begin(), signalHeader.end(), "\n");
    SignalHeader::iterator iter;
    for(iter = signalHeader.begin(); iter != signalHeader.end(); iter++) {
        os << *iter << endl;
    }
}

void CycleData::printSignalData(ostream& os) {

	unsigned long cycleCount = 0;
	for(unsigned int vecCount=0; vecCount < data.size(); vecCount++) {
		os << (data[vecCount].loopCount ) << "\t";
		data[vecCount].print(os);
		os << " // " << vecCount << " " << cycleCount << endl;
		if(data[vecCount].loopCount > 0)
			cycleCount += data[vecCount].loopCount;
		cycleCount++;
	}
}

unsigned long CycleData::addLoops(unsigned long startVec, unsigned long stopVec) {
    //AppLogger&   applog = boost::logger::logger::get_logger(log_type<AppLogger>());
    boost::timer t0;

    //applog.info << __FUNCTION__ << " START" << endl;

	register unsigned long numVecRemoved = 0;

	if((stopVec <= startVec) || (stopVec == data.size()))
		stopVec = data.size() - 1;

    assert( stopVec  > startVec);
    assert( startVec < data.size());
    assert( stopVec  < data.size());

    //applog.debug << "startVec = " << startVec << " stopVec = " << stopVec << endl;

    vector<PeriodData> newData;

	for(register unsigned long vecCount=startVec; vecCount < stopVec; ) {
        //if(debug > 1)
            //applog.debug << "vecCount = " << vecCount << " stopVec = " << stopVec << endl;

//        string currVec, nextVec;
//        currVec = data[vecCount].getString();
//        if(vecCount < (stopVec - 1))
//            nextVec = data[vecCount+1].getString();
//
//        if(currVec == nextVec) {
//            data[vecCount].loopCount++;
//            data.erase(data.begin() + vecCount + 1);
//            numVecRemoved++;
//            stopVec--;
//        }
        PeriodData currVec, nextVec;
        currVec = data[vecCount];
        unsigned int offset       = 1;
        unsigned int offsetCycles = 1;
        nextVec = data[vecCount + 1];
        while((currVec == nextVec) && (nextVec.getLabel().size() == 0)) {
            offset++;
            offsetCycles += (nextVec.loopCount + 1);
            if((vecCount + offset) > stopVec)
                break;
            nextVec = data[vecCount + offset];
        }
        currVec.loopCount = offsetCycles - 1;
        newData.push_back( currVec);
        vecCount = vecCount + offset;

//        if(vecCount < (stopVec )) {
//            nextVec = data[vecCount+1];
//
//            if(currVec == nextVec) {
//                data[vecCount].loopCount += (1 + nextVec.loopCount);
//                data.erase(data.begin() + vecCount + 1);
//                numVecRemoved++;
//                stopVec--;
//            }
//            else
//                vecCount++;
//        }
//        else
//            vecCount++;
	}
    data = newData;

    //applog.info.precision(3);
    //applog.info << __FUNCTION__ << " finished in " << t0.elapsed() << " seconds" << endl;

	return numVecRemoved;
}


