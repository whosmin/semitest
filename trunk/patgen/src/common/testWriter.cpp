
#include "testWriter.h"

TestWriter::TestWriter() {
	padLastVector     = false;
	indent = "\t";
    expandLoopCountBoundary = 0;
}

TestWriter::~TestWriter() {
}

void TestWriter::clear() {
}

bool TestWriter::setIndent(string str) {
	for(unsigned int i=0; i < str.size(); i++) {
		if( (str[i] != ' ') || (str[i] != '\t') || (str[i] != '\n') )
			return false;
	}
	indent = str;

	return true;
}

bool TestWriter::setPatNameSuffix( string str) {
	for(unsigned int i=0; i < str.size(); i++) {
		if( (str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n') || (str[i] == '\r'))
			return false;
	}

	patNameSuffix = str;

	return true;
}

string TestWriter::reorder(string wfcStr) {
	string reorderedStr = wfcStr;

	return reorderedStr;
}

bool TestWriter::setPatPinOrder(vector<string> order) {
    bool result = true;

    return result;
}

void TestWriter::getSignalHeaderComment( CycleData& cyData, vector<string>& comment) {
    SignalHeader signalHeader = cyData.getSignalHeader();
    vector<string> names = getNames(signalHeader);
    vector<string> temp;
    horizToVert( names, temp, 2);
//    for(unsigned int i=0; i < temp.size(); i++) {
//        temp[i] = slCommentPrefix + " " + temp[i];
//    }

    comment = temp;
}

