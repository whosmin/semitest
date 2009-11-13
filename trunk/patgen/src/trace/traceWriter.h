#ifndef __TRACE_WRITER_H__
#define __TRACE_WRITER_H__

#include "eventData.h"
#include "common.h"

#include <string>
#include <vector>

using namespace std;

class TraceWriter {
    public:
        TraceWriter();
    public:
        virtual  ~TraceWriter() {}
        virtual string  getFileExt  () = 0;
        virtual void    setTopScope ( string name) = 0;
        virtual void    write       ( ostream& os, EventData& evData, unsigned long long startTime=0, unsigned long long stopTime=0) = 0;

        virtual void    setTimescale (double value);
        virtual double  getTimescale () { return timescale; }
        virtual void    doubleToTimescale ( const double value, unsigned int& digit, string& unit);

        vector<string> comments;
        string         version;
    protected:
        double timescale;
        string indent;
        string sep;
};

#endif

