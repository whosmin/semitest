
#ifndef __CYCLE_DATA_H__
#define __CYCLE_DATA_H__

#include <map>
#include <vector>
#include <string>
#include <iostream>

#include "common.h"
#include "waveformTable.h"

using namespace std;

class CycleData : public CommonData {
	public:
		struct PeriodData {
			vector<char>               wfcVec;
			string                     wftRef;
			unsigned int               loopCount;
			vector< pair< string, string> > ucode;

			PeriodData() { loopCount = 0; }
            PeriodData& operator=(const PeriodData& rhs);
			void clear();
            void addComment( string comment);
            void addLabel( string label);
            string getLabel(); 
            vector<string> getLabels();
            vector<string> getComments();
//            void addUcodeInst(string keyword, string data) {
//                ucode.push_back( make_pair(keyword, data));
//            }
			string getString();
			void   print(ostream& os, string delim="\t");
            bool   operator==(PeriodData& rhs);
		};

		CycleData();
		virtual ~CycleData();
		virtual void clear();

        virtual bool setSignalHeader(const SignalHeader& header);

		void addPeriodData ( CycleData::PeriodData& periodData);
        bool setPeriodData ( CycleData::PeriodData& periodData, unsigned long vecNum);
		bool getPeriodData ( CycleData::PeriodData& periodData, unsigned long vecNum);

		unsigned long getNumVectors() { return data.size(); }

		bool removeSignal ( string         signalName);
		bool removeSignal ( vector<string> signalVec);
		bool keepSignal   ( vector<string> signalVec);

		virtual void print           (ostream& os);
		virtual void printSignalHeader (ostream& os);
		virtual void printSignalData (ostream& os);

		unsigned long addLoops(unsigned long startVec=0, unsigned long stopVec=0);

	protected:
		vector<PeriodData>          data;
		map< string, WaveformTable> wftMap;
};


#endif


