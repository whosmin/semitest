#ifndef __WAVEFORM_TABLE_H__
#define __WAVEFORM_TABLE_H__

#include "common.h"

#include <string>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

struct Expression {
	public:
		Expression() {}
		Expression( string exprStr) {
			str = exprStr;
		}
		Expression( double exprValue) {
			value = exprValue;
		}
		void clear(void) {
			str = "";
			value = 0.0;
		}
		void operator=(double rhs) {
			value = rhs;
			stringstream ss;
			ss << rhs;
			str = ss.str();
		}
		string str;
		double value;
};

class WaveformTable {
	public:
		WaveformTable();
        WaveformTable(const string& wftName);

		void   clear (void);
		void   print (ostream& os);

        void   getEvents           ( string pinName, char wfc, map<double, State>& events);
        double getEventResolution  ();

//        typedef map<string, vector< pair<Expression, State> > > WfcList ;
//        typedef map<string, vector< pair<double, State> > > WfcList ;
//        typedef map<string, map< double, State> > WfcList ;
		typedef map<char, map< double, State> > WfcList ;

		string     name;
		Expression period;
		/// pinGroup to WfcList map
		map<string, WfcList> waveforms;
};

#endif

