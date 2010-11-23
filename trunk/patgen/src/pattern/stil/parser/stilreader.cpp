
#include <cstdio>
#include <iostream>

#include "Stil.h"
#include "Parser.h"
#include "Scanner.h"

using namespace std;
using namespace Stil;

int main(int argc, char** argv) {

    if(argc > 1) {
        cout << "Reading file " << argv[1] << endl;
        FILE* fp = fopen( argv[1], "r");

        SymbolTable& sTable = SymbolTable::getReference();

        Scanner* scanner = new Scanner(fp);
        //wchar_t *filename = coco_string_create(argv[1]);
        //Scanner* scanner = new Scanner(filename);
        Parser* parser   = new Parser(scanner);
        //parser->pSignalGroups = new SignalGroups();
        parser->Parse();

        cout << "Errors detected : " << parser->errors->count << endl;

        {

            cout << parser->signals.toStil() << endl;

            if(parser->pSignalGroups != NULL)
                cout << parser->pSignalGroups->toStil() << endl;

            Collection<Spec>::iterator iter;
            for(iter = parser->pSpecCollection->begin(); iter != parser->pSpecCollection->end(); iter++) {
                cout << iter->second.toStil() << endl;
            }
        }

        //if(parser->pWftCollection != NULL) {
        //}
        Collection<WaveformTable> wftColl = parser->getWftCollection();
        {
            Collection<WaveformTable>::iterator iter;
            for(iter = wftColl.begin(); iter != wftColl.end(); iter++) {
                cout << iter->second.toStil() << endl;
            }
        }


        //cout << parser->pSpecCollection->toStil() << endl;

        delete scanner;
        delete parser->pSignalGroups;
        delete parser;
    }
    else
        cout << "No source file specified" << endl;

    return 0;
}

