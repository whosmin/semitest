
#ifndef __PATTERN_READER_H__
#define __PATTERN_READER_H__

#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

#include "common.h"
#include "cycleData.h"
#include "waveformTable.h"

using namespace std;

class PatternReader {
	public:
                PatternReader();
		virtual ~PatternReader();
		virtual void clear();
                virtual void read(ostream& os);

    protected:
        string allPinsGroup;
        vector<string> pinOrder;

};

#endif

