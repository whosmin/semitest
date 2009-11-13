#ifndef __STIL_WRITER_H__
#define __STIL_WRITER_H__

#include <iostream>
#include <fstream>
#include <cctype>

#include "../patternWriter.h"

class StilWriter : public PatternWriter {
    public:
        StilWriter();

        virtual bool writeHeader        ( ostream& os);
        virtual bool writeFooter        ( ostream& os);
        virtual void writePattern       ( ostream& os,  CycleData&     cyData,         string  patName,     unsigned     long startVec=0, unsigned long stopVec=0);
        virtual void writeWaveformTable ( ostream& os,  WaveformTable& wft,            string  wftName="");
        virtual void writeTiming        ( ostream& os,  map<string,    WaveformTable>& wftMap, string       timingName);
        
        virtual void setAllPinsGroup(string group);

        bool quotedLabel;

    protected:
        virtual string mapVec(const string& vec);
        double version;

        string vectorPrefix, vectorSuffix;
};

#endif

