#ifndef HISTORY_H
#define HISTORY_H

#include <string>
#include <vector>
#include <list>

using namespace std;

class History {
    public:
        History();
        void clear();

        void         setMaxSize(unsigned int);
        unsigned int getMaxSize() { return maxSize; }

        unsigned int getSize(void);

        bool addEntry     (string  line);
        bool getCurrEntry (string& value);
        bool getPrevEntry (string& value);
        bool getNextEntry (string& value);

    protected:
        unsigned int   maxSize;
        bool           allowAdjacentDuplicates;

    private:
        vector<string> buffer;
        int            currIndex;
};

class IterHistory {
    public:
        IterHistory();
        void clear();

        void         setMaxSize(unsigned int);
        unsigned int getMaxSize() { return maxSize; }

        unsigned int getSize(void);

        bool addEntry     (string  line);
        bool getCurrEntry (string& value);
        bool getPrevEntry (string& value);
        bool getNextEntry (string& value);

    protected:
        unsigned int   maxSize;
        bool           allowAdjacentDuplicates;

    private:
        list<string> buffer;
        list<string>::iterator iterBuffer;
};


#endif // HISTORY_H
