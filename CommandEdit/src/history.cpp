#include "history.h"

#include <iostream>

History::History() {
    maxSize                 = 100;
    currIndex               = -1;
    allowAdjacentDuplicates = true;
    byteCount = 0;
}

void History::clear(void) {
    buffer.clear();
    currIndex = -1;
    byteCount = 0;
}

void History::setMaxSize(unsigned int max) {
    maxSize = max;
}

unsigned int History::getSize(void) {
    return buffer.size();
}

bool History::addEntry(string line) {
    bool popped = false;

    buffer.push_back(line);
    byteCount += line.size();

    if(buffer.size() >= maxSize) {
        byteCount -= buffer.begin()->size();
        buffer.erase(buffer.begin());
        popped = true;
    }

    currIndex = buffer.size() - 1;

    cout << __PRETTY_FUNCTION__ << " " << line << endl;

    return !popped;
}

bool History::getCurrEntry(string& value) {
    bool valid = false;

    if(buffer.size() > 0) {
        value = buffer[currIndex];
        valid = true;
    }

    return valid;
}

bool History::getPrevEntry(string& value) {
    bool end   = true;
    bool empty = true;

    if(buffer.size() > 0) {
        empty = false;
        if(currIndex == 0)
            end = true;
        else {
            end = false;
            currIndex--;
        }
        value = buffer[currIndex];
    }
    else
        empty = true;

    cout << __PRETTY_FUNCTION__ << " " << value << endl;

    return !(end | empty);
}

bool History::getNextEntry(string& value) {
    bool end   = true;
    bool empty = true;

    if(buffer.size() > 0) {
        empty = false;
        if(currIndex >= (buffer.size() - 1)) {
            end = true;
            value = ""; // Remove this if you do not want to clear the command
        }
        else {
            end = false;
            currIndex++;
            value = buffer[currIndex];
        }
    }
    else
        empty = true;

    cout << __PRETTY_FUNCTION__ << " " << value << endl;

    return !(end | empty);
}


IterHistory::IterHistory() {
    maxSize                 = 100;
    allowAdjacentDuplicates = true;
    iterBuffer = buffer.end();
}

void IterHistory::clear(void) {
    buffer.clear();
    iterBuffer = buffer.end();
}

void IterHistory::setMaxSize(unsigned int max) {
    maxSize = max;
    while(buffer.size() > maxSize)
        buffer.erase(buffer.begin(), buffer.begin());
}

unsigned int IterHistory::getSize(void) {
    return buffer.size();
}

bool IterHistory::addEntry(string line) {
    bool popped = false;

    if(buffer.size() > maxSize) {
        buffer.pop_front();
        popped = true;
    }

    buffer.push_back(line);
    iterBuffer = buffer.end();

    cout << __PRETTY_FUNCTION__ << " " << buffer.size() << " " << line << endl;

    return !popped;
}

bool IterHistory::getCurrEntry(string& value) {
    bool valid = true;

    if(iterBuffer != buffer.end())
        value = *iterBuffer;
    else
        value = "";

    return valid;
}

bool IterHistory::getPrevEntry(string& value) {
    bool end   = false;
    bool empty = false;

    int size = buffer.size();

    if(buffer.size() > 0) {
        if(iterBuffer == buffer.begin())
            value = *iterBuffer;
        else
            value = *(--iterBuffer);
    }
    else
        empty = true;

    cout << __PRETTY_FUNCTION__ << " " << value << endl;

    return !(end | empty);
}

bool IterHistory::getNextEntry(string& value) {
    bool end   = false;
    bool empty = false;

    if(iterBuffer == buffer.end()) {
        value = "";
        end = true;
    }
    else if(++iterBuffer != buffer.end()) {
        value = *(iterBuffer);
    }
    else {
        value = "";
        end = true;
    }

    cout << __PRETTY_FUNCTION__ << " " << value << endl;

    return !(end | empty);
}


