
#ifndef __CYCLIZE_H__
#define __CYCLIZE_H__

#include "common.h"
#include "eventData.h"
#include "cycleData.h"
#include "waveformTable.h"

#include <string>
#include <vector>
#include <map>

class Cyclize {
	public:
		Cyclize(); 
        /// \brief Cyclization Method A
        ///
        /// \param[in]  evDataRef    Event Data structure reference
        /// \param[out] cyDataRef    Cycle Data structure reference
        /// \param[in]  wftMap       Waveform Table data map reference
        /// \param[in]  instructions
        /// \param[in]  pinOrder 
		void methodA(EventData& evDataRef, CycleData& cyDataRef,
				map< string, WaveformTable>& wftMap,
                map< string , map< unsigned long long, string> >& instMap,
                vector<string> pinOrder
                );

	private:
};

#endif

