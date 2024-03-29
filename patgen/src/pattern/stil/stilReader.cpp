
#include "stilReader.h"

#include <cstdio>
#include <iostream>

#include "parser/Stil.h"
#include "parser/Parser.h"
#include "parser/Scanner.h"

using namespace std;
using namespace Stil;

StilReader::StilReader() {
}

StilReader::~StilReader() {
}

void StilReader::clear() {
}

void StilReader::read( istream& is, vector<string>& pinNames, map<string, ::WaveformTable>& wftMap) {
    SymbolTable& sTable = SymbolTable::getReference();

    Scanner* scanner = new Scanner(is);
    //wchar_t *filename = coco_string_create(argv[1]);
    //Scanner* scanner = new Scanner(filename);
    Parser* parser   = new Parser(scanner);
    //parser->pSignalGroups = new SignalGroups();
    parser->Parse();

    cout << "Errors detected : " << parser->errors->count << endl;

    {

        cout << parser->signals.toStil() << endl;
        pinNames = parser->signals.getNames();

        if(parser->pSignalGroups != NULL)
            cout << parser->pSignalGroups->toStil() << endl;

        Collection<Spec>::iterator iter;
        for(iter = parser->pSpecCollection->begin(); iter != parser->pSpecCollection->end(); iter++) {
            cout << iter->second.toStil() << endl;
        }

        Collection<Stil::WaveformTable> wftColl = parser->getWftCollection();
        {
            Collection<Stil::WaveformTable>::iterator iter;
            for(iter = wftColl.begin(); iter != wftColl.end(); iter++) {
                Stil::WaveformTable stilWft = iter->second;
                cout << stilWft.toStil() << endl;
                ::WaveformTable wft(stilWft.getName());
                wft.period = ::Expression(stilWft.period.getValue());

                wftMap[wft.name] = wft;

                for(unsigned int i=0; i < pinNames.size(); i++) {
                    if(stilWft.hasPin(pinNames[i])) {
                        //stilWft.getEvents( pinNames[i],
                        cout << pinNames[i] << endl;
                    }
                }
            }
        }

    }


}

