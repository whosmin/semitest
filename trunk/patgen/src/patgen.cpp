#include <iostream>
#include <fstream>
#include <cctype>
#include <cmath>
#include <sstream>
#include <numeric>
#include <string>

#include "common.h"
#include "trace/evcd/evcdReader.h"
#include "eventData.h"
#include "cycleData.h"
#include "waveformTable.h"
#include "algorithm/cyclize.h"
#include "algorithm/transform.h"
#include "pattern/patternWriter.h"
#include "pattern/stil/stilWriter.h"
//#include "appLogger.h"
#include "trace/traceWriter.h"
#include "trace/evcd/evcdWriter.h"
#include "trace/verilog/verilogWriter.h"

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <boost/filesystem.hpp>
//#include <boost/logger/log.hpp>
#include <boost/shared_ptr.hpp>
#include "boost/lexical_cast.hpp"

namespace po = boost::program_options;

using namespace boost;
//using namespace boost::logger;

using namespace std;

#ifdef _PROGRAM_VERSION_
const string versionString = _PROGRAM_VERSION_;
#else
const string versionString = "";
#endif

int debug = 0;

#define WILL
#include "./signals_and_wft.inc"

void loadInstructions( string instructionFileName,
	map<string, map<unsigned long long, string> >& instMap ) {

    if(instructionFileName.size() == 0)
        return;

    //AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());

    fstream finst;
    finst.open( instructionFileName.c_str(), fstream::in);

    vector< pair<boost::regex, string > > rexpr;
//    rexpr[0] = boost::regex("\\s*(Wft|WaveformTable)\\s+([0-9]+)\\s+([A-Za-z][A-Za-z0-9_]*)\\s*", boost::regex_constants::icase);
//    rexpr[1] = boost::regex("\\s*(Wft|WaveformTable)\\s+([A-Za-z][A-Za-z0-9_]*)\\s+([0-9]+)\\s*", boost::regex_constants::icase);
//    rexpr[2] = boost::regex("\\s*([0-9]+)\\s+(Wft|WaveformTable)\\s+([A-Za-z][A-Za-z0-9_]*)\\s*", boost::regex_constants::icase);
    rexpr.push_back( make_pair( boost::regex("\\s*([0-9]+)\\s+(Wft|WaveformTable)\\s+([A-Za-z][A-Za-z0-9_]*)\\s*", boost::regex_constants::icase), "waveformtable") );
    rexpr.push_back( make_pair( boost::regex("\\s*([0-9]+)\\s+(Label)\\s+([A-Za-z0-9_]+)\\s*",                     boost::regex_constants::icase), "label") );
    rexpr.push_back( make_pair( boost::regex("\\s*([0-9]+)\\s+(Comment)\\s+(.*)",                                  boost::regex_constants::icase), "comment") );

    while( finst.good() ) {
        string str;
        getline( finst, str);
        trim(str);

        boost::cmatch matches;
        for(unsigned int i=0; i < rexpr.size(); i++) {
            if(regex_match( str.c_str(), matches, rexpr[i].first)) {
//                applog.debug << "string\t\"" << str << "\"" << endl;
//                applog.debug << "re: matches[1].first\t" << matches[1].first << endl;
                //applog.debug << "INSTRUCTIONS REGEX MATCH : " << "1 -> " << matches[1] << "\t" << "2 -> " <<  matches[2] << "\t" << "3 -> " <<  matches[3] << endl;
                string             keyword   = rexpr[i].second;
                unsigned long long timestamp = 0;
                try {
                    timestamp = boost::lexical_cast< unsigned long long, string>(matches[1]);
                    instMap[keyword][timestamp] = matches[3].first;
                }
                catch( boost::bad_lexical_cast& lex) {
                    cout << lex.what() << endl;
                }
                break;
            }
            //else 
                //applog.debug << "INSTRUCTIONS REGEX MATCH : " << "NO MATCH" << endl;
        }

    }

    finst.close();
}

void dumpInstructions(EventData& eventData, ostream& os, const vector<string> regNames) {
    EventData::RegContainerType regData;

    eventData.getRegData( regData, regNames);

    EventData::RegContainerType::iterator iter;

    for(iter = regData.begin(); iter != regData.end(); iter++) {
        unsigned long long timestamp = iter->first;
        for(unsigned int i=0; i < iter->second.size(); i++) {
            string instrBin = iter->second[i].second;
            string instrAsc;
            
            // Left (MSB) extend with zero
            while(instrBin.size() % 8)
                instrBin = '0' + instrBin;

            const unsigned int bitWidth = instrBin.size() - 1;
            for(unsigned int i=0; i <= bitWidth; i+=8) {
                string str;
                for(unsigned int j=0; j <= 7; j++) {
                    str += instrBin[i + j];
                }
                int ch = 0;
                for(unsigned int j=0; j<str.size(); j++) {
                    if(str[7-j] == '1')
                        ch += 1 << j;
                }
                if(isprint(ch))
                    instrAsc += char(ch);

            }

            os << timestamp << "\t" << instrAsc << endl;
        }
    }
}

string getTestName( string fileName) {
    string testName;
    vector<string> stringVec;

    boost::split( stringVec, fileName, is_any_of("/\\"));
    testName = stringVec.back();
    stringVec.clear();

    boost::split( stringVec, testName, is_any_of("."));
    testName = stringVec.front();

    return testName;
}

vector<string> commandLine;
string         commandLineString;

int main(int argc, char *argv[])
{

    for(int i=0; i < argc; i++) {
        commandLine.push_back(string(argv[i]));
        commandLineString += string(argv[i]) + " ";
    }
//    accumulate( commandLine.begin(), commandLine.end(), commandLineString);

    //AppLogger& applog = boost::logger::logger::get_logger(log_type<AppLogger>());
    //applog.info.off();
    //applog.debug.off();
    //applog.fatal.on();
    //applog.warn.on();

    ///////////////////////////////////////////////////////////////////////////
    //                                                                       //
    //  Process command line options                                         //
    //                                                                       //
    ///////////////////////////////////////////////////////////////////////////
    boost::program_options::options_description desc("Options");
    desc.add_options()
        ("help,h",                                         "display help message and exit")
        ("version,v",                                      "display version information and exit")
        ("config,c",                                       "Set config file path/name")
        ("instructions,i",  po::value< string >(),         "Set instructions file path/name")
        ("debug-parser,p",                                 "Enable parser trace")
        ("debug-scanner,s",                                "Enable scanner trace")
        ("trace-file",      po::value< vector<string> >(), "input file")
        ("test-name",       po::value< vector<string> >(), "Override test/pattern name")
        ("debug",           po::value< int >(),            "Set debug level. 0 => None, 1 => Brief, 2 => Detailed. Enable debug log")
        ("log-info",                                       "Enable info log")
        ("log-debug",                                      "Enable debug log")
        ("gen-evcd",                                       "Create cyclized evcd file")
        ("gen-verilog",                                    "Create verilog testbench")
    ;

    po::positional_options_description p;
    p.add("trace-file", -1);

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).
          options(desc).positional(p).run(), vm);
    //boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);

    po::notify(vm);

    if(vm.count("help")) {
        cout << argv[0] << "\t" << versionString << endl;
        cout << desc << endl;
        exit(1);
    }
    if(vm.count("version")) {
        cout << argv[0] << "\t" << versionString << endl;
        exit(1);
    }

    if(vm.count("debug")) {
        debug = vm["debug"].as< int >();
        //applog.debug.on();
    }

#if 0
    if(vm.count("log-info"))
        applog.info.on();
    if(vm.count("log-debug"))
        applog.debug.on();
#endif

    vector<string> traceFiles;
    vector<string> testNames;
    string         instructionFileName = "instructions.txt";
    bool           createInstructions  = true;
    bool           debugParser         = false;
    bool           debugScanner        = false;

    if(vm.count("debug-parser")) {
        debugParser = true;
    }
    if(vm.count("debug-scanner")) {
        debugScanner = true;
    }
    if (vm.count("trace-file")) {
        traceFiles = vm["trace-file"].as< vector<string> >();
        if(debug) {
            //applog.debug << "Trace files are : ";
            //for(unsigned int i=0; i < traceFiles.size(); i++) {
                //applog.debug << " " << traceFiles[i];
            //}
            //applog.debug << endl;
        }
        if(traceFiles.size() == 0) {
            //applog.error << "No input files given" << endl;
            exit(1);
        }
    }

    testNames.clear();
    for(unsigned int i=0; i<traceFiles.size(); i++) {
        testNames.push_back( getTestName( traceFiles[i]));
    }

    if (vm.count("test-name")) {
        vector<string> names = vm["test-name"].as< vector<string> >();
        for(unsigned int i=0; i < std::min(names.size(), traceFiles.size()); i++) {
            testNames[i] = names[i];
        }
    }

    if(vm.count("instructions")) {
        instructionFileName = vm["instructions"].as< string >();
        // TODO Check if file already exists
        if(!boost::filesystem::exists( instructionFileName)) {
            //applog.error << "File " << instructionFileName << " does not exist!" << endl;
            exit(1);
        }
        createInstructions = false;
    }

    ///////////////////////////////////////////////////////////////////////////
    //                                                                       //
    ///////////////////////////////////////////////////////////////////////////

    EventData  eventData;
    EvcdReader driver(eventData);

    driver.trace_parsing  = debugParser;
    driver.trace_scanning = debugScanner;


    if(traceFiles.size() > 0) {
        std::fstream infile(traceFiles[0].c_str());
        if (!infile.good()) {
            //applog.error << "Could not open file: " << traceFiles[0] << std::endl;
            exit(1);
        }
        //applog.info << "Started Loading trace file " << traceFiles[0] << endl;
        driver.parse_stream(infile, traceFiles[0].c_str());
        //applog.info << "Finished Loading trace file " << traceFiles[0] << endl;
    }
    else
        exit(1);


    eventData.setName( testNames[0]);

    //if(debug > 1)
        //eventData.print(applog.debug);

    //
    // Create instructions.txt from Event Data
    //
    if(createInstructions) {
        //applog.info << "Creating instructions file " << instructionFileName << endl;

        vector<string> instRegNames;
        instRegNames.push_back("test_instr");
        instRegNames.push_back("test_comment");
        instRegNames.push_back("strobe_instr");

        fstream finst;
        finst.open( instructionFileName.c_str(), fstream::out);
        dumpInstructions( eventData, finst, instRegNames);
        finst.close();
    }



    vector<bool> validVec;
    if(!eventData.isValidSignal( pioSignalGroup, validVec)) {
        vector<string> validSignals;
        for(unsigned int i=0; i < validVec.size(); i++) {
            if(validVec[i] == false) {
                //applog.error << "WARNING : Signal " << pioSignalGroup[i] << "\t not found in Event Data." << endl;
            }
            else
                validSignals.push_back( pioSignalGroup[i]);
        }
        if(validSignals.size() == 0) {
            //applog.error << "ERROR : Invalid signal group" << endl;
            exit(1);
        }
        pioSignalGroup = validSignals;
    }
    if(debug) {
        //applog.debug << "VALID SIGNALS (pioSignalGroup) : " << endl;
        for(unsigned int i=0; i < pioSignalGroup.size(); i++) {
            //applog.debug << "\t" << i << "\t" << pioSignalGroup[i] << endl;
        }
    }
	eventData.keepSignal( pioSignalGroup);

    //if(debug > 1)
        //eventData.print(applog.debug);
    
    //applog.info << "Sizeof EventData : " << sizeof(eventData) << endl;


	map< string, WaveformTable> wftMap;

    loadWft(wftMap);

    //////////////////////////////////////////////////////////
    //
    // Build instructions
    //
	vector< pair<unsigned long long, string> >    instructions;
	map<string, map<unsigned long long, string> > instMap;

//    instMap["comment"][0] = "";

    //applog.info << "Loading instructions from file " << instructionFileName << endl;
    loadInstructions( instructionFileName, instMap);

    //
    // Create Dummy event data based on instruction timestamps
    //
    {
        EventData::DataType dummy;
        map<string, map<unsigned long long, string> >::iterator iter;
        for(iter = instMap.begin(); iter != instMap.end(); iter++) {
            string keyword = iter->first;
            map<unsigned long long, string>::iterator iterInst;
            for(iterInst = iter->second.begin(); iterInst != iter->second.end(); iterInst++) {
                unsigned long long timestamp = iterInst->first;
                if(!eventData.isValidTimestamp( timestamp))
                    eventData.setData( dummy, timestamp);
            }
        }
    }

    if(debug) {
        //applog.debug << "INSTRUCTIONS" << endl;
        map<string, map<unsigned long long, string> >::iterator iter;
        for(iter = instMap.begin(); iter != instMap.end(); iter++) {
            string keyword = iter->first;
            map<unsigned long long, string>::iterator iterInst;
            for(iterInst = iter->second.begin(); iterInst != iter->second.end(); iterInst++) {
                //applog.debug << keyword << "\t" << iterInst->first << "\t" << iterInst->second << endl;
            }
        }
        
    }

    if(instMap.find("waveformtable") == instMap.end()) {
        //applog.error << "Did not find WaveformTable instructions" << endl;
        exit(1);
    }

    for(map<unsigned long long, string>::iterator iter = instMap["waveformtable"].begin();
            iter != instMap["waveformtable"].end();
            iter++ )
    {
        string wftRef = iter->second;
        if(wftMap.find(wftRef) == wftMap.end()) {
            //applog.error << "Did not find WaveformTable " << wftRef << endl;
            exit(1);
        }
    }

	CycleData cycleData;

    //applog.info << "Cyclizing EventData"<< endl;
	Cyclize cyclize;
	cyclize.methodA( eventData, cycleData, wftMap, instMap, pioSignalGroup);

    //
    // Clear event data to free up memory
    //
    eventData.clear();

    if(debug > 1) {
        //applog.debug << "----------------------------------------" << endl;
        //applog.debug << "          Cyclized Data                 " << endl;
        //applog.debug << "----------------------------------------" << endl;
        //cycleData.print(applog.debug);
    }

    //applog.info << "Compressing CycleData"<< endl;
    cycleData.addLoops();


    if(debug > 1) {
        //applog.debug << "----------------------------------------" << endl;
        //cycleData.print(applog.debug);
    }

    //
    // Write STIL output
    //
    //applog.info << "Writing CycleData to STIL"<< endl;
    string stilFileName = testNames[0] + ".stil";
	fstream filestr( stilFileName.c_str(), fstream::out);

	PatternWriter *pPatternWriter = new StilWriter();
    pPatternWriter->setAllPinsGroup(pioGroupName);
    pPatternWriter->writeHeader( filestr);
//    pPatternWriter->writeTiming  ( filestr, wftMap,    "default");
	pPatternWriter->writePattern ( filestr, cycleData, testNames[0]);
    pPatternWriter->writeFooter( filestr);
	delete pPatternWriter;

	filestr.close();


    if(vm.count("gen-evcd") || vm.count("gen-verilog")) {
        EventData cyEventData;
    //    cyEventData.setTimescale( eventData.getTimescale());
    //    cyEventData.setTimescale( 1e-12);


        //applog.info << "Expanding CycleData"<< endl;
        Transform transform;
        transform.expand( cycleData, cyEventData, wftMap, pioSignalGroup);
        //if(debug > 1)
            //cyEventData.print(applog.debug);

        //
        // Write cyclized trace file
        //
        if(vm.count("gen-evcd")) {
            TraceWriter *pTraceWriter = new EvcdWriter();
            pTraceWriter->version = "0.1";
            pTraceWriter->comments.push_back( versionString);
            pTraceWriter->comments.push_back( "Command: \n\t" + commandLineString);


            string designFileName = testNames[0] + "_cyclized." + pTraceWriter->getFileExt();
            fstream fout( designFileName.c_str(), fstream::out);
            if(fout.good()) {
                pTraceWriter->write( fout, cyEventData);
            }
            fout.close();
            delete pTraceWriter;
        }

        //
        // Write Verilog Testbench
        //
        if(vm.count("gen-verilog")) {
            VerilogWriter* pVerilogWriter = new VerilogWriter();
            string verilogFileName = testNames[0] + "." + pVerilogWriter->getFileExt();
            fstream fout( verilogFileName.c_str(), fstream::out);
            if(fout.good()) {
                pVerilogWriter->write2( fout, cyEventData);
            }
            fout.close();
            delete pVerilogWriter;
        }
    }

    //
    // Clear cycle data to free up memory
    //
    cycleData.clear();


    return 0;
}

