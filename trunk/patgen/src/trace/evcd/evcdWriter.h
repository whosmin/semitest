#ifndef __EVCD_WRITER_H__
#define __EVCD_WRITER_H__

#include "../../common/common.h"
#include "../traceWriter.h"
#include <string>

using namespace std;

class EvcdWriter : public TraceWriter {
    public:
        EvcdWriter();
        virtual string  getFileExt  () { return fileExt; }
        virtual void    setTopScope ( string scope);
        virtual void    write       ( ostream& os, EventData& evData, unsigned long long startTime=0, unsigned long long stopTime=0);
//        virtual void    setTimescale (double value);

    private:
        void printSignalHeader( ostream& os, SignalHeader& signalHeader);

    protected:
        static const string fileExt;
        string topScope;

};

#endif

