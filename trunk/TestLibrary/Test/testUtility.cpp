//
// This file is part of SemiTest
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
// Copyright 2010 Tushar Jog
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

TEST(Utility, stringToBool) {
    const string testStr = "0101";
    vector<logic::tribool> boolResults;

    stringToBool(testStr, boolResults);

    for (unsigned int i=boolResults.size()-1; i >= 0; i--) {
        cout << boolResults[i];
    }
    cout << endl;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
