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
 * testRegister.cpp
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

string toString(vector<logic::tribool>& binaryVec) {
    string binaryStr;
    for (int i=binaryVec.size()-1; i >= 0; i--) {
        string bit = "x";
        if(binaryVec[i] == false)
            bit = "0";
        else if(binaryVec[i] == true)
            bit = "1";
        else
            bit = "x";
        binaryStr = binaryStr + bit;
    }
    return binaryStr;
}

TEST(Utility, stringToBool) {
    bool result = false;
    const string testStr = "A101";
    vector<logic::tribool> boolResults;

    unsigned long long value = 0;

    result = stringToBool("0b1000", boolResults);
    EXPECT_EQ( toString(boolResults), "1000");
    EXPECT_EQ( result, true);
    //for (int i=boolResults.size()-1; i >= 0; i--) cout << boolResults[i]; cout << endl;

    result = stringToBool("0x1011", boolResults, 16);
    EXPECT_EQ( toString(boolResults), "0001000000010001");
    EXPECT_EQ( result, true);

    result = stringToBool("1011", boolResults, 10);
    EXPECT_EQ( toString(boolResults), "1111110011");
    EXPECT_EQ( result, true);

    result = stringToBool("+1011", boolResults);
    EXPECT_EQ( result, false);

}

TEST(Utility, stringToLong) {
    EXPECT_EQ(stringToLong(       "1234", 10),       1234L);
    EXPECT_EQ(stringToLong( "-987654321", 10), -987654321L);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
