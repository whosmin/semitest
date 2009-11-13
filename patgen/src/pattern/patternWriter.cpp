
#include "patternWriter.h"

PatternWriter::PatternWriter() {
	padLastVector     = false;
	indent = "\t";
    expandLoopCountBoundary = 0;
}

PatternWriter::~PatternWriter() {
}

void PatternWriter::clear() {
}

bool PatternWriter::setIndent(string str) {
	for(unsigned int i=0; i < str.size(); i++) {
		if( (str[i] != ' ') || (str[i] != '\t') || (str[i] != '\n') )
			return false;
	}
	indent = str;

	return true;
}

bool PatternWriter::setPatNameSuffix( string str) {
	for(unsigned int i=0; i < str.size(); i++) {
		if( (str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') || (str[i] == '\r'))
			return false;
	}

	patNameSuffix = str;

	return true;
}

string PatternWriter::reorder(string wfcStr) {
	string reorderedStr = wfcStr;

	return reorderedStr;
}

bool PatternWriter::setPatPinOrder(vector<string> order) {
    bool result = true;

    return result;
}

void PatternWriter::getSignalHeaderComment( CycleData& cyData, vector<string>& comment) {
    SignalHeader signalHeader = cyData.getSignalHeader();
    vector<string> names = getNames(signalHeader);
    vector<string> temp;
    horizToVert( names, temp, 2);
//    for(unsigned int i=0; i < temp.size(); i++) {
//        temp[i] = slCommentPrefix + " " + temp[i];
//    }

    comment = temp;
}

