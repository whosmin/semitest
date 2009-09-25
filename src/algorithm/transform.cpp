
#include "transform.h"
//#include "appLogger.h"
#include <cassert>
#include <cmath>

extern bool debug;

//AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());

/// \param[in]  periodData
/// \param[in]  wft
/// \param[out] eventData
/// \param[in]  timescale
void getEventData ( 
        CycleData::PeriodData& periodData,
        WaveformTable&         wft,
        EventData&             eventData,
        vector<string>&        pinList,
        double                 timescale)  {

        for(unsigned int i=0; i < periodData.wfcVec.size(); i++) {
            char   wfc     = periodData.wfcVec[i];
            string pinName = pinList[i];

            map<double, State> events;
            wft.getEvents( pinName, wfc, events);

            map<double, State>::iterator iter;
            for(iter = events.begin(); iter != events.end(); iter++) {
                unsigned long long timestamp = 0;
                // Need my_round due to fractional error
                timestamp = (unsigned long long) my_round(iter->first / timescale);
                eventData.data[timestamp].push_back( make_pair(pinName, iter->second)); 
            }
        }

}

void Transform::expand(    CycleData& cyData, EventData& evData,
        map< string, WaveformTable>& wftMap,
        vector<string> pinList, double timescale) {

    assert( timescale >= 0.0);
    assert( timescale <= 1.0);

    if(timescale == 0.0) {
        //
        // Calculate timescale
        //
        vector<double> res;
        map<string, WaveformTable>::iterator iter;
        for(iter = wftMap.begin(); iter != wftMap.end(); iter++) {
            res.push_back( iter->second.getEventResolution());
        }
        double minRes = *(min_element( res.begin(), res.end()));
        double exponent = ceil( log10(1/minRes));
        timescale = pow( 10.0, -exponent);

        //applog.debug << "Calculating timescale : " << timescale << endl;
        //applog.debug << "minRes = " << minRes << " exponent = " << exponent << endl;

        assert( timescale >= 0.0);
        assert( timescale <= 1.0);
    }

    //if(debug)
        //cyData.print( applog.debug);

    SignalHeader signalHeader = cyData.getSignalHeader();

    vector<string> pinNames;
    for(unsigned int i=0; i < signalHeader.size(); i++) {
        pinNames.push_back( signalHeader[i].name);
    }

    evData.setSignalHeader( signalHeader);

    unsigned long numVectors = cyData.getNumVectors();

    unsigned long long periodBeginTimestamp = 0;
    unsigned long loopSum = 0;
    for(unsigned long vecNum=0; vecNum < numVectors; vecNum++) {
        CycleData::PeriodData periodData;
        cyData.getPeriodData( periodData, vecNum);


//        periodData.print( applog.debug);

        WaveformTable wft = wftMap[periodData.wftRef];
        double period = wft.period.value;

        // Need my_round due to fractional error
        unsigned long long periodTimestamp = (unsigned long long) my_round(period/timescale);

        EventData periodEventData;

        getEventData( periodData, wft, periodEventData, pinNames, timescale);

//        periodEventData.print( applog.debug);
        
        for(unsigned int i=0; i <= periodData.loopCount; i++) {
            // append event data
            //applog.debug << "Adding events at timestamp " << periodBeginTimestamp << endl;
            evData.add( periodEventData, periodBeginTimestamp);
//            periodBeginTimestamp = (unsigned long long) (((vecNum + 1 + loopSum + i)*period)/timescale);
            periodBeginTimestamp = (unsigned long long) ((vecNum + 1 + loopSum + i)*periodTimestamp);
        }
        loopSum += periodData.loopCount;
    }

    evData.setTimescale( timescale);
}


