
#ifndef __TEST_WRITER_H__
#define __TEST_WRITER_H__

#include <iostream>
#include <fstream>
#include <cctype>

#include "common.h"
#include "cycleData.h"
#include "waveformTable.h"

class TestWriter {
	public:
		TestWriter();
		virtual ~TestWriter();
		virtual void clear();

		virtual bool setIndent        ( string str);
		virtual bool setPatNameSuffix ( string str);

		virtual bool writeHeader        ( ostream& os)=0;
		virtual bool writeFooter        ( ostream& os)=0;
		virtual void writePattern       ( ostream& os, CycleData&     cyData,         string  patName,    unsigned    long startVec=0, unsigned long stopVec=0) = 0;
		virtual void writeWaveformTable ( ostream& os, WaveformTable& wft,            string  wftName="") =           0;
		virtual void writeTiming        ( ostream& os, map<string,    WaveformTable>& wftMap, string      timingName) =    0;

		bool   padLastVector;

		/// \brief Rearrange order and/or take subset of pins and return wfcChar string

        virtual void setAllPinsGroup(string group) { allPinsGroup = group; }

        virtual bool setPatPinOrder(vector<string> order);

        virtual void getSignalHeaderComment( CycleData& cyData, vector<string>& comment);

	protected:

		/// \brief Set and order of signals to dump from CycleData data structure
		vector<string> patPinOrder;

		virtual string reorder(string wfcStr);

		string indent;
		string patNameSuffix;
        // Pin group name for all pattern pins in one group
        string allPinsGroup;

        /// \brief Single line comment prefix
        string slCommentPrefix;
        /// \brief Multi-line comment prefix
        string mlCommentPrefix;
        /// \brief Multi-line comment suffix
        string mlCommentSuffix;

        unsigned int expandLoopCountBoundary;
};


#endif

