
#include <cstdio>
#include <iostream>

#include "Stil.h"
#include "Parser.h"
#include "Scanner.h"

using namespace std;

int main(int argc, char** argv) {

    if(argc > 1) {
        cout << "Reading file " << argv[1] << endl;
        FILE* fp = fopen( argv[1], "r");

        Stil::SymbolTable& sTable = Stil::SymbolTable::getReference();

        Scanner* scanner = new Scanner(fp);
        //wchar_t *filename = coco_string_create(argv[1]);
        //Scanner* scanner = new Scanner(filename);
        Parser* parser   = new Parser(scanner);
        //parser->pSignalGroups = new Stil::SignalGroups();
        parser->Parse();

        cout << "Errors detected : " << parser->errors->count << endl;

        if(parser->pSignalGroups != NULL)
            cout << parser->pSignalGroups->toStil() << endl;
        Stil::Collection<Stil::Spec>::iterator iter;
        for(iter = parser->pSpecCollection->begin(); iter != parser->pSpecCollection->end(); iter++) {
            cout << iter->second.toStil() << endl;
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

