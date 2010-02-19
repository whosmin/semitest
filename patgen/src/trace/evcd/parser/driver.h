#ifndef __EVCD_DRIVER_H__
#define __EVCD_DRIVER_H__

#include <string>
#include <vector>
#include <map>

#include "common.h"

using namespace std;

namespace evcd
{

    class Scanner;
    class Parser;

    class Driver
    {
    public:
        /// construct a new parser driver context
        Driver();
        virtual ~Driver() {}

        friend class Scanner;
        friend class Parser;

        /// enable debug output in the flex scanner
        bool trace_scanning;

        /// enable debug output in the bison parser
        bool trace_parsing;

        /** Invoke the scanner and parser for a stream.
         * @param in	input stream
         * @param sname	stream name for error messages
         * @return		true if successfully parsed
         */
        bool parse_stream(istream& in, const string& sname = "stream input");

        /** Invoke the scanner and parser on an input string.
         * @param input	input string
         * @param sname	stream name for error messages
         * @return		true if successfully parsed
         */
        bool parse_string(const string& input, const string& sname = "string stream");

        /** Invoke the scanner and parser on a file. Use parse_stream with a
         * std::ifstream if detection of file reading errors is required.
         * @param filename	input file name
         * @return		true if successfully parsed
         */
        bool parse_file(const string& filename);

        virtual void error(const class location& loc, const string& m);
        virtual void error(const string& m);


        virtual void   onScope          ( string name, string type);
        virtual void   onUpScope        (void);
        virtual void   onVar            ( string name, string type, unsigned int size, string alias);
        virtual void   onVar            ( string name, string type, unsigned int size, string alias, unsigned int msbIndex, unsigned int lsbIndex);
        virtual void   onEndDefinitions (void);
        virtual void   onDate           (string str);
        virtual void   onTimescale      (unsigned long long number, string unit);
        virtual void   onVersion        (string str);
        virtual void   onTimestamp      (unsigned long long time);
        virtual void   onDumpportsBegin (void);
        virtual void   onDumpportsEnd   (void);
        virtual void   onScalarChange   (string alias, string value, unsigned int strength0, unsigned int strength1);
        virtual void   onVectorChange   (string alias, string value);
        virtual void   onVectorChange   (string alias, string value, string strength0, string strength1);
        virtual void   onEOF            (void);

        virtual void   signalEndDefinitions (void) {}
        virtual void   signalChanges       (void) {}
        virtual void   signalEOF           (void) {}
        virtual void   signalDumpportsBegin ( void) {}
        virtual void   signalDumpportsEnd   ( void) {}

        virtual string getCurrentScope  (void);

    protected:
        /// stream name (file or input stream) used for error messages.
        string streamname;
        /** Pointer to the current lexer instance, this is used to connect the
         * parser to the scanner. It is used in the yylex macro. */
        Scanner* lexer;
        Parser*  pParser;

        string scopeSeparator;
        vector< pair<string, string> > scopeVec;

        string        dateStr;
        string        versionStr;
        unsigned long long timescaleNumber;
        string        timescaleUnit;

//        multimap< string , SignalInfo> signalMap;
        map< string , SignalInfo> signalMap;
		unsigned int varCount;

    protected:
        bool         signalExists ( string alias);
        unsigned int signalCount  ( string alias);

        vector< pair< string, string> > currStates;
        unsigned long long                   currTime;

    };

}

#endif

