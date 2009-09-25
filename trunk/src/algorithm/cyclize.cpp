
#include "cyclize.h"
#include <iostream>
#include <algorithm>
#include <queue>
//#include "appLogger.h"

using namespace std;

extern int debug;

Cyclize::Cyclize() {
	
}

//
// Get wftRef
//
string getInst(map<unsigned long long, string>& instMap, unsigned long long timestamp) {
	string value;

	if(instMap.find(timestamp) == instMap.end()) {
		map< unsigned long long, string >::iterator iter;
		iter= instMap.upper_bound(  timestamp);
		iter--;
		value = iter->second;
	}
	else
		value = instMap[timestamp];

	return value;
}

vector<string> getAllInst(map<unsigned long long, string>& instMap,
        unsigned long long startTimestamp, unsigned long long stopTimestamp) {

    vector<string> values;

    if(instMap.size() == 0)
        return values;

    map<unsigned long long, string>::iterator iterStart, iterStop, iterEnd;

//    iterStart = instMap.find(startTimestamp);
//    if(iterStart == instMap.end()) {
//        iterStart = instMap.upper_bound( startTimestamp);
//        if(iterStart == instMap.end())
//            return values;
//    }
    iterStart = instMap.lower_bound(startTimestamp);
    if(iterStart == instMap.end())
        return values;

    iterEnd = instMap.lower_bound( stopTimestamp);
    iterStop = iterEnd;
    iterStop--;

//    cout << __FUNCTION__ << " "
//         << startTimestamp << " " << stopTimestamp << endl;

    if((iterStart->first >= stopTimestamp) || (iterStart->first > iterStop->first))
        return values; 

//    cout << __FUNCTION__ << "\t\t"
//         << iterStart->first << "\t" << iterStop->first << endl;

    map<unsigned long long, string>::iterator iter;
    for(iter = iterStart; iter != iterEnd; iter++) {
        values.push_back( iter->second);
    }

	return values;
}

double getMetric( map<unsigned long long, State > pinData, map<unsigned long long, State> wfcData, WaveformTable& wftRef, const double timescale ) {
    //AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());

	double metric = 0;

	map<unsigned long long, int> weights;
	vector< pair<unsigned long long, double> > weightVec;

	unsigned long long periodTimestamp = (unsigned long long) my_round( wftRef.period.value / timescale);
    if(debug > 2) {
        //applog.debug << "WaveformTable : " << wftRef.name << " Period : " << wftRef.period.value << " Timescale : " << timescale << " periodTimestamp : " << periodTimestamp << endl;
    }
//    weights[0]               = 0;
//    weights[periodTimestamp] = 0;

	map<unsigned long long, State>::iterator iter;
	for(iter = pinData.begin(); iter != pinData.end(); iter++) {
		weights[iter->first] = 0;
	}
	for(iter = wfcData.begin(); iter != wfcData.end(); iter++) {
		weights[iter->first] = 0;
	}
	map<unsigned long long, int>::iterator iterWeights;
	unsigned long long prevTimestamp = 0;
	for(iterWeights = weights.begin(); iterWeights != weights.end(); iterWeights++) {
		unsigned long long timestamp = iterWeights->first;
		State pinState, wfcState;

		if(pinData.find(timestamp) == pinData.end()) {
			map<unsigned long long, State>::iterator iter;
			iter = pinData.upper_bound( timestamp);
			iter--;
			pinState = iter->second;
		}
		else
			pinState = pinData[timestamp];

		if(wfcData.find(timestamp) == wfcData.end()) {
			map<unsigned long long, State>::iterator iter;
			iter = wfcData.upper_bound( timestamp);
			iter--;
			wfcState = iter->second;
		}
//            wfcState = (wfcData.upper_bound( timestamp)--)->second;
		else
			wfcState = wfcData[timestamp];

		if(wfcState == pinState) {
			weights[timestamp] = 1;
//            metric = metric + 1.0;
		}
		weightVec.push_back( make_pair(timestamp, weights[timestamp]));

		prevTimestamp = timestamp;
	}

#if 0
    if(debug > 2) {

        applog.debug << "\tMetric " << endl;
        for(iter = pinData.begin(); iter != pinData.end(); iter++) {
            applog.debug << "\t\tPin : " << iter->first << "\t" << (char) iter->second << endl;
        }
        for(iter = wfcData.begin(); iter != wfcData.end(); iter++) {
            applog.debug << "\t\tWfc : " << iter->first << "\t" << (char) iter->second << endl;
        }
        applog.debug << "\t\t";
        for( iterWeights = weights.begin(); iterWeights != weights.end(); iterWeights++) {
            applog.debug << "\t" << iterWeights->first << "[" << iterWeights->second << "]";
        }
    }
#endif

	metric = 0.0;
	for(unsigned int i=0; i < weightVec.size(); i++) {
		double value = 0.0;


		if(i < (weightVec.size()-1))
			value  = (weightVec[i].second * (((double)(weightVec[i+1].first - weightVec[i].first))/periodTimestamp));
		else if(i == (weightVec.size() - 1)) {
			if(weightVec[i].first == periodTimestamp)
				value  = weightVec[i].second * 0.1;
			else
				value  = weightVec[i].second * (((double) (periodTimestamp - weightVec[i].first))/periodTimestamp);
		}

		metric += value;

//        cout.precision(3);
#if 0
        if(debug > 2) {
            applog.debug << "\t ( " << weightVec[i].first << ", " << weightVec[i].second << ") [ " << value << ", " << metric << "]";
            if(i == (weightVec.size() - 1)) {
                applog.debug << " periodTimestamp : " << periodTimestamp; 
            }
        }
#endif
	}

//    metric = metric / periodTimestamp;

//    if(weights.size() > 0)
//        metric = metric / weights.size();

#if 0
    if(debug > 2) {
        applog.debug << endl << "\t" << metric << endl << endl;
    }
#endif

	return metric;
}
double getMetric( map<unsigned long long, State > pinData, map<double, State> wfcData, WaveformTable& wftRef, const double timescale ) {
	double metric = 0;

	map<unsigned long long, State> wfcCharData;
	map<double, State>::iterator iter;
	for(iter = wfcData.begin(); iter != wfcData.end(); iter++) {
		unsigned long long timestamp = (unsigned long long) my_round(iter->first / timescale);
		wfcCharData[timestamp] = iter->second;
	}

	metric = getMetric( pinData, wfcCharData, wftRef, timescale);

	return metric;
}

map< string, char> getCycleDataChar( map<string, State>& periodBeginPinState,
		WaveformTable& wftRef, 
		map<unsigned long long, vector< pair< string, State> > >& periodEventData,
        const vector<string> pinList, const double timeScale
		) {
	map< string, char> cycleData;

	// Key : pinname Value: Map of timestamp to State
	map<string, map< unsigned long long, State> > pinEvents;

	map<string, State>::iterator iterPBPS;
	for(iterPBPS = periodBeginPinState.begin(); iterPBPS != periodBeginPinState.end(); iterPBPS++) {
		pinEvents[iterPBPS->first][0] = iterPBPS->second;
	}
	
	map<unsigned long long, vector< pair< string, State> > >::iterator iter;
	for(iter = periodEventData.begin(); iter != periodEventData.end(); iter++) {
		for(unsigned int i=0; i < iter->second.size(); i++) {
			pinEvents[iter->second[i].first][iter->first] = iter->second[i].second;
		}
	}

#if 0
    if(debug > 2) {
        AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());
        applog.debug << "PinEvents : " << endl;
        map<string, map< unsigned long long, State> >::iterator iter;
        for(iter = pinEvents.begin(); iter != pinEvents.end(); iter++) {
            applog.debug << "\t" << iter->first << "\t";
            map<unsigned long long, State>::iterator iterState;
            for(iterState = iter->second.begin(); iterState != iter->second.end(); iterState++) {
                applog.debug << "\t" << iterState->first << "\t" << (char) iterState->second;
            }
            applog.debug << endl;
        }
    }
#endif

	// Key: wfc Char , Value : map of time to state
//    map< string, map<string, map<unsigned long long, State> > > wfEvents;
//    map< string, map<string, vector<unsigned long long, State> > >::iterator wfIter;
//    for(wfIter = wftRef.waveforms.begin(); wfIter != wftRef.waveforms.end(); wfIter++) {
//
//    }

    // Dont need this anymore since pinList is being passed
//    vector<string> pinList;
//    map<string, State>::iterator iterPinState;
//    for(iterPinState = periodBeginPinState.begin(); iterPinState != periodBeginPinState.end(); iterPinState++) {
//        string pinName = iterPinState->first;
//        pinList.push_back(pinName);
//    }
	
	for(unsigned int i=0; i < pinList.size(); i++) {
		string pinName = pinList[i];
		map<char, double> metric;
		map<char, map<double, State> >::iterator iter;
        if(debug > 2)
            cout << pinName << endl;
		double maxMetric = 0.0;
		char   maxWfcChar = ' ';
		for(iter = wftRef.waveforms[pinName].begin(); iter != wftRef.waveforms[pinName].end(); iter++) {
			char wfcChar = iter->first;
			map<unsigned long long, State> wfcCharData;
            if(debug > 2)
                cout << "\t\'" << wfcChar << "\'" << endl;

			metric[wfcChar] = getMetric( pinEvents[pinName], wftRef.waveforms[pinName][wfcChar], wftRef, timeScale);
			if(metric[wfcChar] >= maxMetric && metric[wfcChar] > 0.0) {
				maxMetric = metric[wfcChar];
				maxWfcChar = wfcChar;
			}
		}
        if(debug > 2)
            cout << pinName << "\t" << "\'" << maxWfcChar << "\'\t" << maxMetric << endl;
		cycleData[pinName] = maxWfcChar;
	}

	
	/*
	map<string, map< unsigned long long, State> >::iterator peIter;
	for(peIter = pinEvents.begin(); peIter != pinEvents.end(); peIter++) {
		string pinName = peIter->first;
		cout << "\t" << pinName;
		map<unsigned long long, State>::iterator iter;
		for(iter = peIter->second.begin(); iter != peIter->second.end(); iter++) {
			cout << " " << iter->first << " " << (char) iter->second;
		}
		cout << endl;
	}
	*/

	return cycleData;
}

vector<char> reorderCycleState( map<string, char>& cycleState, vector<string>& pinOrder) {
    vector<char> reorderedVec;
    for(unsigned int i=0; i < pinOrder.size(); i++) {
        map<string, char>::iterator iter;
        iter = cycleState.find(pinOrder[i]);
        if(iter != cycleState.end())
            reorderedVec.push_back( iter->second);

//        if((iter = cycleState.find(pinOrder[i]) != cycleState.end())) {
//            reorderedVec.push_back( iter->second);
//        }
    }

    return reorderedVec;
}


/// Cyclization Method A
//
//  From instructions data structure, form range of timestamps where a particular
//  wftRef is valid
//  Break range into period boundaries. Some boundaries might be less than a period width
//  Iterate through eventData timestamps with step size currWftRef.period
//  	For each signal pick appropriate wfcChar from wftRef and push onto cycleData
//  
void Cyclize::methodA ( 
        EventData&                                        evData,
        CycleData&                                        cyData,
		map< string, WaveformTable>&                      wftMap,
        map< string , map< unsigned long long, string> >& instMap,
        vector<string> pinOrder
        ) {

	unsigned long long simStopTimestamp = evData.getStopTime();
	double        timeScale        = evData.getTimescale();

    if(pinOrder.size() == 0)
        pinOrder = evData.getSignals();

#if 0
    AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());
    if(debug) {
        applog.debug << "Timescale : " << timeScale << endl;
        applog.debug << "PinOrder : " << endl;
        for(unsigned int i=0; i < pinOrder.size(); i++) {
            applog.debug << "\t" << pinOrder[i] << endl;
        }
    }
#endif

//    evData.removeEmptyTimestamps();
	cyData.clear(); // Clear prior to filling
    // TODO: FIXME 
    SignalHeader signalHeader = evData.getSignalHeader();
    reorderSignalHeader( signalHeader, pinOrder);
    cyData.setSignalHeader( signalHeader);

	//
	// Create wftRefMap from instructions data structure
	//
	map< unsigned long long, string > wftRefMap;
    if(instMap.find("waveformtable") != instMap.end())
        wftRefMap = instMap["waveformtable"];

	map< unsigned long long, string > commentMap, labelMap;
    if(instMap.find("comment") != instMap.end())
        commentMap = instMap["comment"];
    if(instMap.find("label") != instMap.end())
        labelMap = instMap["label"];

	map<string, State>           pinState;       // cursor
	map<string, State>           periodPinState; // period cursor
    EventData::DataContainerType periodEventData;

    queue< pair<EventData::DataContainerType, vector<char> > > eventDataQueue;

    EventData::DataContainerType::iterator iter;
//    iter = evData.data.begin();
//    unsigned long long startTimestamp = iter->first;
    unsigned long long vecNum = 0;
	for(iter = evData.data.begin(); iter != evData.data.end(); ) {
		unsigned long long startTimestamp = iter->first;
		//
		// Get wftRef
		//
		string wftRef = getInst( wftRefMap, startTimestamp);

		double period = wftMap[wftRef].period.value;
		unsigned long long periodTimestamp = (unsigned long long) my_round( period / timeScale);

		EventData::DataContainerType::iterator iterPeriod;
		iterPeriod = iter;
		periodEventData.clear();

		unsigned long long periodEndTimestamp = startTimestamp + periodTimestamp;
		
		//
		// Get all events in the period
		//
		while(iterPeriod->first < (periodEndTimestamp)
				&& (iterPeriod != evData.data.end())
				&& (getInst( wftRefMap, iterPeriod->first) == wftRef)
			) {
			periodEventData[ iterPeriod->first - startTimestamp] = evData.data[iterPeriod->first];

			for(unsigned int i=0; i < iterPeriod->second.size(); i++) {
				string pinName = iterPeriod->second[i].first;
				State  event   = iterPeriod->second[i].second;
				periodPinState[pinName] = event;
			}

			vector< pair< string, State> > empty;
			if((startTimestamp + periodTimestamp) < simStopTimestamp)
				if(evData.data.find( startTimestamp + periodTimestamp) == evData.data.end())
					evData.data[startTimestamp + periodTimestamp] = empty;


			iterPeriod++;
		}

        vector<char> cycleStateReordered;
        // Compare to previous
        bool matched = false;
        if(eventDataQueue.size() > 0) {
            //applog.debug << endl;
            //applog.debug << "StartTimestamp : " << startTimestamp << endl;
            //applog.debug << "Current Period : ";
            //EventData::printData( applog.debug, periodEventData);
            //applog.debug << "Queue : ";
            //EventData::printData( applog.debug, eventDataQueue.back().first);

            if(isEqual( periodEventData, eventDataQueue.back().first) == true) {
                //applog.debug << "MATCH FOUND " << endl;
                cycleStateReordered = eventDataQueue.back().second;
                matched = true;
            }
        }

        if(matched == false) {
            map< string, char> cycleState = getCycleDataChar( pinState, wftMap[wftRef], periodEventData, pinOrder, timeScale);

            cycleStateReordered = reorderCycleState( cycleState, pinOrder);

        }
        eventDataQueue.push( make_pair(periodEventData, cycleStateReordered) );

        if(eventDataQueue.size() > 2)
            eventDataQueue.pop();

        map<string, char>::iterator iterWfcChar;

#if 0
        if(debug > 1) {
            // print the event data
            applog.debug << "EventData : ";
            map<string, State>::iterator iterPeriodState; 
            for(iterPeriodState = periodPinState.begin(); iterPeriodState != periodPinState.end(); iterPeriodState++) {
                applog.debug << (char) iterPeriodState->second;
            }
            applog.debug << endl;

            // print the cycle data
            applog.debug << "CycleData : ";
//            for(iterWfcChar = cycleState.begin(); iterWfcChar != cycleState.end(); iterWfcChar++) {
//                applog.debug << iterWfcChar->second;
//            }
            for(unsigned int i=0; i < cycleStateReordered.size(); i++) {
                applog.debug << cycleStateReordered[i];
            }
            applog.debug << endl;
        }
#endif

		
		CycleData::PeriodData periodData;

        periodData.wfcVec = cycleStateReordered;
		periodData.wftRef = wftRef;

        vector<string> comments = getAllInst( commentMap, startTimestamp, periodEndTimestamp);
        for(unsigned int i=0; i < comments.size(); i++) {
            //applog.debug << __FUNCTION__ << " " << __LINE__ << "COMMENT " << startTimestamp << " " << periodEndTimestamp << " : " << comments[i] << endl;
            periodData.addComment( comments[i]);
        }

        vector<string> labels = getAllInst( labelMap, startTimestamp, periodEndTimestamp);
        for(unsigned int i=0; i < labels.size(); i++) {
            //applog.debug << __FUNCTION__ << " " << __LINE__ << " LABEL " << startTimestamp << " " << periodEndTimestamp << " : " << labels[i] << endl;
            periodData.addLabel( labels[i]);
        }

        //
        // Add to Cyclized Data
        //
		cyData.addPeriodData( periodData);

		pinState = periodPinState;
		iter = iterPeriod;
        vecNum++;
        //applog.debug << "VectorNum : " << vecNum << endl;
	}


    //applog.debug << "End of : " << __FUNCTION__  << endl;
}

