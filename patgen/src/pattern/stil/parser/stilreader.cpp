
#include <cstdio>
#include <iostream>

#include "Parser.h"
#include "Scanner.h"

using namespace std;

int main(int argc, char** argv) {

    if(argc > 1) {
        cout << "Reading file " << argv[1] << endl;
        FILE* fp = fopen( argv[1], "r");
        Scanner* scanner = new Scanner(fp);
        //wchar_t *filename = coco_string_create(argv[1]);
        //Scanner* scanner = new Scanner(filename);
        Parser* parser   = new Parser(scanner);
        parser->Parse();

        cout << "Errors detected : " << parser->errors->count << endl;

        delete scanner;
        delete parser;
    }
    else
        cout << "No source file specified" << endl;

    return 0;
}

