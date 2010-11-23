
#ifndef __STIL_READER_H__
#define __STIL_READER_H__

#include <iostream>
#include <fstream>
#include <cctype>

#include "common.h"
#include "cycleData.h"
#include "waveformTable.h"

#include "../patternReader.h"

class StilReader : public PatternReader {
    public:
        StilReader();
        virtual ~StilReader();
        virtual void clear();
        virtual void read(istream &is);

};


#endif
