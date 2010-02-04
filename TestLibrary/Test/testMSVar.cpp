//
// This file is part of SemiTest
//
// Copyright (c) 2009 - 2010 Tushar Jog
//
// SemiTest is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Foobar is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
//

/*
 * testMSVar.cpp
 *
 *      Author: Tushar Jog
 */

#include <gtest/gtest.h>
#include <boost/logic/tribool.hpp>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "../Core/testLib.h"

using namespace std;
using namespace boost;

using namespace TestLib;

//
// Declare local macros, types and functions for use in this file
//
// start
#define NUM_SITES 8

typedef struct results_str {
    int    resource;
    int    site;
    double value;
    int    PassFail; // -1 => lower than lower limit, 0 => within limits, 1 => greater than upper limit
    } RESULTS_STR;

typedef std::vector<char> Bitstream;

int groupgetresults( RESULTS_STR results[], int size) {
    int result = 0;

    return result;
}

RESULTS_STR __results[32];

double qmsmv( int pin, int mode, int numsamples, double sampledelay) {
    double result = 0.0;

    for(int i=0; i < NUM_SITES; i++) {
        __results[i].site     = i;
        __results[i].resource = i;
        __results[i].value    = i * 1.0;
        __results[i].PassFail = 0;
    }

    return result;
}

// end

template<typename T>
ostream& operator<<(ostream& os, std::vector<T> vt)
{
    for (unsigned int i = 0; i < vt.size(); i++)
        os << vt[i];
    return os;
}
template<typename T>
ostream& operator<<(ostream& os, MSArray<T> vt)
{
    for (unsigned int i = 0; i < vt.size(); i++)
        os << vt[i].value;
    return os;
}

// This should be done first
template<typename T>
    std::size_t MSVarVec<T>::numSites(8);
template<typename T>
    int MSVarVec<T>::indexOffset(0);

#ifdef _MSC_VER
#define __FUNCNAME__ __FUNCSIG__
#else
#define __FUNCNAME__ __PRETTY_FUNCTION__
#endif

//
// Test defaults that are application even before constructing any objects, since MSVar is a templated class
// and lines 109..113 have some defaults set
//
TEST( MSVar, Defaults) {
    MSVar<double> msDouble;
    EXPECT_EQ( msDouble.size(), 8) << "Check default size of 8";
    EXPECT_EQ( msDouble.getIndexOffset(), 0) << "Check default value of indexOffset";
}

TEST( MSVar, DllFunction) {
    MSArray<RESULTS_STR> results;
    qmsmv( 1, 1, 1024, 13.0);
    groupgetresults( results.c_array(), NUM_SITES);
    cout << results << endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

