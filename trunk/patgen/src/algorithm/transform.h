#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "common.h"
#include "cycleData.h"
#include "eventData.h"
#include "waveformTable.h"

#include <string>
#include <vector>

class Transform {
    public:
        Transform() {}

        void expand(    CycleData& cyData, EventData& evData,
                        map< string, WaveformTable>& wftMap, vector<string> pinList, double timescale=0.0);
};

#endif

