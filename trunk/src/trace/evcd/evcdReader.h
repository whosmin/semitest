#ifndef __EVCD_READER_H__
#define __EVCD_READER_H__

#include <iostream>
#include <fstream>
#include <cctype>

#include "driver.h"
#include "eventData.h"
#include "common.h"

using namespace std;

class EvcdReader : public evcd::Driver
{
public:
    EvcdReader(EventData& data);
    virtual ~EvcdReader();
    virtual void   signalEndDefinitions ( void);
    virtual void   signalChanges        ( void);
    virtual void   signalEOF            ( void);
    virtual void   signalDumpportsBegin ( void);
    virtual void   signalDumpportsEnd   ( void);
    static  string binToAscii           ( string binStr);
protected:
    State charToState(char ch); 
    EventData& evDataRef;
};


#endif

