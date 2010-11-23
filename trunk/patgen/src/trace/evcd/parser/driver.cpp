#include <fstream>
#include <sstream>

#include "driver.h"
#include "evcd_yacc.hpp"
#include "scanner.h"

namespace evcd
{

    Driver::Driver()
            : trace_scanning(false),
            trace_parsing(false)
    {
        scopeSeparator = ".";
        currStates.clear();
        currTime = 0;
		varCount = 0;
        lexer = 0;
        pParser = 0;
    }

    bool Driver::parse_stream(istream& in, const string& sname)
    {
        streamname = sname;

        Scanner scanner(&in);
        scanner.set_debug(trace_scanning);
        this->lexer = &scanner;

        Parser parser(*this);
        pParser = &parser;
        parser.set_debug_level(trace_parsing);
        bool parseResult = (parser.parse() == 0);
        pParser = 0;

        return parseResult;
    }

    bool Driver::parse_file(const string &filename)
    {
        ifstream in(filename.c_str());
        return parse_stream(in, filename);
    }

    bool Driver::parse_string(const string &input, const string& sname) {
        istringstream iss(input);
        return parse_stream(iss, sname);
    }

    void Driver::error(const class location& loc, const string& m) {
        cerr << "ERROR @ [";
        //   cerr << loc << " : " << m << endl;
        position last = loc.end - 1;
        if (last.filename)
            cerr << "FILE : " << *(last.filename) << ", Line : " << last.line << ", Column : " << last.column;

        if (last.filename && (!loc.begin.filename || *loc.begin.filename != *last.filename))
            cerr << '-' << last;
        else if (loc.begin.line != last.line)
            cerr << '-' << last.line  << '.' << last.column;
        else if (loc.begin.column != last.column)
            cerr << '-' << last.column;

        cerr << "] : " << m;
        cerr << endl;
    }

    void Driver::error(const string& m) {
        cerr << m << endl;
    }

    void Driver::onScope( string name, string type) {
        scopeVec.push_back( make_pair( name, type) );
    }

    string Driver::getCurrentScope(void) {
        string scope;
        for (unsigned int i=0; i<scopeVec.size(); i++)
        {
            if (i > 0)
                scope += scopeSeparator;
            scope += scopeVec[i].first;
        }

        return scope;
    }

    void Driver::onUpScope(void) {
        if (scopeVec.size() < 1)
            cerr << "Scope stack empty" << endl;
        else
            scopeVec.pop_back();
    }

    // Net
    void   Driver::onVar( string name, string type, unsigned int size, string alias)
    {
        SignalInfo signal;

        if (type == "inout" || type == "input" || type == "output" || type == "port")
        {
            signal.name  = name;
            signal.scope = getCurrentScope();
            signal.size  = size;
            signal.alias = alias;
            signal.type  = type;
			signal.index = varCount;

//            signalMap[signal.alias] = signal;
//            signalMap.insert( pair<string, SignalInfo>( signal.alias, signal) );
            signalMap.insert( make_pair( signal.alias, signal) );

			varCount++;
        }
        else
        {
            cerr << "ERROR : Invalid signal type" << endl;
            exit(1);
        }
    }

    // Register
    void   Driver::onVar( string name, string type, unsigned int size, string alias, unsigned int msbIndex, unsigned int lsbIndex)
    {
        SignalInfo signal;

        if (!signalExists(alias))
        {
            signal.name  = name;
            signal.scope = getCurrentScope();
            signal.size  = size;
            signal.alias = alias;
            signal.type  = type;
			signal.index = varCount;

//            signalMap[signal.alias] = signal;
//            signalMap.insert( pair<string, SignalInfo>( signal.alias, signal) );
            signalMap.insert( make_pair( signal.alias, signal) );

			varCount++;
        }
        else
        {
            cerr << "ERROR : Invalid signal name. Signal [" << name << "] already exists" << endl;
            exit(1);
        }
    }

    void Driver::onEndDefinitions(void)
    {
//        map<string, SignalInfo>::iterator iter;
//        for(iter = signalMap.begin(); iter != signalMap.end(); iter++) {
//            cout << iter->second.scope << " " << iter->second.name << " " << iter->second.alias << endl;
//        }
        signalEndDefinitions();
    }

    void Driver::onDate(string str)
    {
        dateStr = str;
    }

    void Driver::onTimescale(unsigned long long number, string unit)
    {
        timescaleNumber = number;
        timescaleUnit   = unit;
    }

    void Driver::onVersion(string str)
    {
        versionStr = str;
    }

    void Driver::onTimestamp(unsigned long long time)
    {
        signalChanges();
        currStates.clear();

        unsigned long long newTime = time;

        currTime = newTime;
    }

    void Driver::onDumpportsBegin(void)
    {
        signalDumpportsBegin();
    }

    void Driver::onDumpportsEnd(void)
    {
        signalDumpportsEnd();
    }

    void Driver::onScalarChange(string alias, string value, unsigned int strength0, unsigned int strength1)
    {
        if (signalExists(alias)) 
            if(signalMap[alias].type == "reg") {
                cerr << "ERROR : Signal " << signalMap[alias].name << " defined as port, cannot use reg data." << endl;
                exit(1);
            }
            else
                currStates.push_back( make_pair( alias, value));
        else {
            cerr << "ERROR : Signal alias " << alias << " is invalid" << endl;
            exit(1);
        }
    }

    void Driver::onVectorChange(string alias, string value)
    {
        if (signalExists(alias))
            if(signalMap[alias].type == "reg")
                currStates.push_back( make_pair( alias, value));
            else {
                cerr << "ERROR : Signal " << signalMap[alias].name << " defined as reg, cannot use port data." << endl;
                exit(1);
            }
        else {
            cerr << "ERROR : Signal alias " << alias << " is invalid" << endl;
            exit(1);
        }
    }

    void Driver::onVectorChange(string alias, string value, string strength0, string strength1)
    {
        if (signalExists(alias))
            if(signalMap[alias].type == "reg")
                currStates.push_back( make_pair( alias, value));
            else {
                cerr << "ERROR : Signal " << signalMap[alias].name << " not defined as reg but as " << signalMap[alias].type << ", cannot use port data." << endl;
                //exit(1);
            }
        else {
            cerr << "ERROR : Signal alias " << alias << " is invalid" << endl;
            exit(1);
        }
    }

    void Driver::onEOF(void)
    {
//        if (currStates.size() > 0)
        {
            signalChanges();
            currStates.clear();
        }
        signalEOF();
    }

    inline bool Driver::signalExists(string alias)
    {
        map< string, SignalInfo>::iterator iter = signalMap.find(alias);
        if (iter != signalMap.end())
            return true;

        return false;
    }
    inline unsigned int Driver::signalCount(string alias)
    {
        return (unsigned int) signalMap.count( alias);
    }
}
