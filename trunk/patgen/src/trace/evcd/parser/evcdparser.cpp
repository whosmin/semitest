
#include <iostream>
#include <fstream>
#include <cctype>

#include "driver.h"

using namespace std;

int main(int argc, char *argv[])
{
//    EventData  eventData;
//    EvcdReader driver(eventData);
	evcd::Driver driver;
    bool readfile = false;

    for (int ai = 1; ai < argc; ++ai)
    {
        if (argv[ai] == std::string ("-p")) 
            driver.trace_parsing = true;
        else if (argv[ai] == std::string ("-s"))
            driver.trace_scanning = true;
        else {
            // read a file with expressions
            std::fstream infile(argv[ai]);
            if (!infile.good()) {
                std::cerr << "Could not open file: " << argv[ai] << std::endl;
                return 0;
            }
            bool result = driver.parse_stream(infile, argv[ai]);
        }
    }

    cout << endl; cout << endl;
}



