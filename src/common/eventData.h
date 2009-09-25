#ifndef __EVENT_DATA_H__
#define __EVENT_DATA_H__

#include <map>
#include <vector>

#include "driver.h"
#include "common.h"

using namespace std;

class EventData : public CommonData
{
public:
    EventData();
    EventData(double timeScale);
    virtual ~EventData();

    virtual void    clear();
                                  
	void            setTimescale          (double timeScale);
	double          getTimescale          (void)         { return timescale; }
                                          
    bool            setRegData            ( vector< pair< string, string> >& value, unsigned long long timestamp);
    bool            getRegData            ( vector< pair< string, string> >& value, unsigned long long timestamp);
                                          
	bool            removeSignal          ( string         signalName);
	bool            removeSignal          ( vector<string> signalVec);
	bool            keepSignal            ( vector<string> signalVec);
	void            removeEmptyTimestamps ();

	/// Get the simulation/trace stop time
	virtual unsigned long long  getStopTime   (void);
	virtual unsigned int        getNumSignals ();

	// Key: timestamp
    typedef vector< pair< string, string> >     RegType;
    typedef map<unsigned long long, RegType >   RegContainerType; 
    typedef vector< pair< string, State> >      DataType;
    typedef map<unsigned long long, DataType >  DataContainerType;

    bool           setData           ( DataType value, unsigned long long timestamp, bool overwrite=false);

    bool           getRegData        ( RegContainerType& data, vector<string> regNames);
    bool           getRegData        ( RegContainerType& data, string         regName);
                                     
    bool           printRegData      (ostream& os, string regName="");
    bool           printRegData      (ostream& os, vector<string> signals);
                   
    void           getLastEventState ( vector< pair< string, State> >& states);
                   
	virtual void   print             ( ostream& os);
	virtual void   printSignalHeader ( ostream& os);
	virtual void   printSignalData   ( ostream& os);
    static  void   printData         ( ostream& os, DataContainerType& data);

    vector<string> getSignals        ();
    bool           isValidSignal     ( const vector<string>& names, vector<bool>& resultVec);
    bool           isValidSignal     ( const string          name);
    bool           isValidTimestamp  (unsigned long long timestamp);

    void           add               ( EventData& eventData, unsigned long long offset);

	//
	// Key: timestamp
	//
    DataContainerType  data;


protected:
    RegContainerType   regData;
	double             timescale;

private:
	unsigned long long startTime, stopTime;

//    string             name;

	bool nameToIndex(string signalName, unsigned int &index);

	bool isNet(string signalName);
	bool isReg(string signalName);

};

bool isEqual( EventData::DataContainerType& lhs, EventData::DataContainerType& rhs);

#endif


