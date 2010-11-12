/*
 * testRegister.cpp
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */

/*
 * testRegister.cpp
 *
 *      Author: Tushar Jog
 */

#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

using namespace std;

#include "../Core/testLib.h"
#include "../Core/msRegister.h"

using namespace TestLib;

ostream& operator<<(ostream& os, array1d<unsigned long long> rhs) {
    for(unsigned int i=0; i < rhs.size(); i++)
        os << rhs[i];
    return os;
}



Register testReg(8, "test_0x00", 0x00);


TEST ( MSRegister, Constructor) {
    MSRegister<2> reg;
    reg[0].printDetailed(cout);
    reg[1].printDetailed(cout);
}
TEST ( MSRegister, CopyConstructor) {
    MSRegister<2> reg(testReg);
    reg[0].printDetailed(cout);
    reg[1].printDetailed(cout);
}
TEST ( MSRegister, Set) {
    MSRegister<2> reg(testReg);
    //reg.set( 255, 8);

    reg.setState( 0xF0);
    ASSERT_EQ( reg[0].getStateInteger(), 0xF0);
    ASSERT_EQ( reg[1].getStateInteger(), 0xF0);
    reg.printDetailed(cout);

    reg.setState( "0xAA");
    ASSERT_EQ( reg[0].getStateInteger(), 0xAA);
    ASSERT_EQ( reg[1].getStateInteger(), 0xAA);
    reg.printDetailed(cout);
}

TEST ( MSRegister, Get) {
    MSRegister<2> reg(testReg);

    array1d<Register::integer_type, 2> temp; // = reg.get();
    for(unsigned int i=0; i < temp.size(); i++) {
        cout << temp[i] << endl;
    }
}

int main(int argc, char** argv) {

testReg.setBitName( 0, "bit 0");
testReg.setBitName( 1, "bit 1");
testReg.setBitName( 2, "bit 2");
testReg.setBitName( 3, "bit 3");
testReg.setBitName( 4, "bit 4");
testReg.setBitName( 5, "bit 5");
testReg.setBitName( 6, "bit 6");
testReg.setBitName( 7, "bit 7");

testReg = 0xAA;

    ::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();
    RUN_ALL_TESTS();


	std::string input;
	std::cin >> input;
}
