#include "designWriter.h"
#include <cassert>

DesignWriter::DesignWriter()
{
}


void DesignWriter::setTimescale(double value) {
    assert(value > 0.0);
    assert(value < 1.0);

    timescale = value;
}

void DesignWriter::doubleToTimescale( const double value, unsigned int& digit, string& unit) {
    double unitVal = 1.0;
    if(value < 1e-15) {
    }
    else if(value < 1e-12) {
        unitVal = 1e-15;
        unit    = "fs";
    }
    else if(value < 1e-9) {
        unitVal = 1e-12;
        unit    = "ps";
    }
    else if(value < 1e-6) {
        unitVal = 1e-9;
        unit    = "ns";
    }
    else if(value < 1e-3) {
        unitVal = 1e-6;
        unit    = "us";
    }
    else if(value < 1) {
        unitVal = 1e-3;
        unit    = "ms";
    }

    digit = (unsigned int) my_round(value / unitVal);
}

