#ifndef __VERILOG_WRITER_H__
#define __VERILOG_WRITER_H__

#include "../traceWriter.h"
#include "cycleData.h"
#include <string>

using namespace std;

class VerilogWriter : public TraceWriter {
    public:
//        VerilogWriter() { indent = "\t"; sep = "  "; }
        VerilogWriter();

        virtual string  getFileExt  () { return fileExt; }
        virtual void    setTopScope ( string scope);

        virtual void    write       ( ostream& os, EventData& evData, unsigned long long startTime=0, unsigned long long stopTime=0);
        virtual void    write2      ( ostream& os, EventData& evData, unsigned long long startTime=0, unsigned long long stopTime=0);

        virtual void    writePattern ( ostream& os, CycleData& cyData, unsigned long long startVec=0,  unsigned long long stopVec=0);
        virtual void    writeWaveformTable ( ostream& os, WaveformTable& wft, string wftName="");
        virtual void    writeTiming        ( ostream& os,  map<string,    WaveformTable>& wftMap, string       timingName="");

    protected:
        static const string fileExt;
        string topScope;
        bool   module;
        string moduleName;
        string netNamePrefix;
        string wireNamePrefix;
};

#endif

