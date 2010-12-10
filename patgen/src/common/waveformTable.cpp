
#include "waveformTable.h"
#include <iostream>
#include <cmath>

WaveformTable::WaveformTable() {
    clear();
}

WaveformTable::WaveformTable(const string& wftName) {
    clear();
    name = wftName;
}

void WaveformTable::clear(void) {
	waveforms.clear();
	name = "";
	period = 0.0;
}

void WaveformTable::getEvents( string pinName, char wfc, map<double, State>& events) {

    if(waveforms.find(pinName) != waveforms.end()) {
        if(waveforms[pinName].find(wfc) != waveforms[pinName].end())
            events = waveforms[pinName][wfc];
    }
}

void WaveformTable::print( ostream& os) {
	string indent = "\t";

    os << "//" <<  endl;
    os << "// Res : " << getEventResolution() << endl;
    os << "//" <<  endl;
	os << "WaveformTable " << "\"" << name << "\" {" << endl;
	os << indent << "Period " << "\'" << period.value << "\';" << endl;
	os << indent << "Waveforms {" << endl;

	map<string, WfcList>::iterator iterWave;
	for(iterWave = waveforms.begin(); iterWave != waveforms.end(); iterWave++) {
		os << indent << indent << "\"" << iterWave->first << "\" {" << endl;
		WfcList::iterator iterWfc;
		for(iterWfc = iterWave->second.begin(); iterWfc != iterWave->second.end(); iterWfc++) {
			os << indent << indent << indent << iterWfc->first << " {" << endl;
			map<double, State>::iterator iterWfcChar;
			for(iterWfcChar = iterWfc->second.begin(); iterWfcChar != iterWfc->second.end(); iterWfcChar++) {
				os << indent << indent << indent
					<< indent << "\'" << iterWfcChar->first << "\'"
					<< indent << (char) iterWfcChar->second << ";"
					<< endl;
			}
//            for(unsigned int i=0; i < iterWfc->second.size(); i++) {
//                os << indent << indent << indent
//                    << indent << "\'" << iterWfc->second[i].first << "\'"
//                    << indent << (char) iterWfc->second[i].second << ";"
//                    << endl;
//            }
			os << indent << indent << indent << "}" << endl;
		}
		os << indent << indent << "}" << endl;
	}

	os << indent << "}" << endl;
	os << "}" << endl;
}

double WaveformTable::getEventResolution() {
    double minRes = period.value;

    vector<double> timeCollection;

    map<string, WfcList>::iterator iterWave;
	for(iterWave = waveforms.begin(); iterWave != waveforms.end(); iterWave++) {
		WfcList::iterator iterWfc;
		for(iterWfc = iterWave->second.begin(); iterWfc != iterWave->second.end(); iterWfc++) {
			map<double, State>::iterator iterWfcChar;
			for(iterWfcChar = iterWfc->second.begin(); iterWfcChar != iterWfc->second.end(); iterWfcChar++) {
                timeCollection.push_back(iterWfcChar->first);
            }
        }
    }

    sort( timeCollection.begin(), timeCollection.end());
    vector<double> uniqueTimeCollection;
    unique_copy( timeCollection.begin(), timeCollection.end(), back_inserter(uniqueTimeCollection));

    for(unsigned int i=0; i < (uniqueTimeCollection.size() - 1); i++) {
        double res = fabs(uniqueTimeCollection[i+1] - uniqueTimeCollection[i]);
        minRes     = min( res, minRes);
    }

    return minRes;
}
