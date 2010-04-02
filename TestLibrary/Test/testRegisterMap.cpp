/*
 * testRegisterMap.cpp
 *
 *      Author: tusharjog
 */

#include <iostream>
#include <string>
#include <sstream>
#include <gtest/gtest.h>

using namespace std;

#include "../Core/testLib.h"

using namespace TestLib;


//
// Constructor Tests
//
TEST(RegisterMap, Constructor) {
    //
    //  Size upon construction
    //
    {
        //
        // RegisterMap Tests
        //
        RegisterMap dutRegMap("F761586");
        cout << "dutRegMap.getSize()\t" << dutRegMap.getSize() << endl;

        Register reg0( 8, "reg0", 0x00, "0xAA");
        dutRegMap.addRegister(reg0);
        cout << "dutRegMap.getSize()\t" << dutRegMap.getSize() << endl;
        Register temp( 8);
        temp = dutRegMap[0];

        dutRegMap[0].print(cout);
        dutRegMap.printDetailed(cout);
    }
    //
    //  State upon construction
    //
    {
    }
    //
    //  Default State upon construction
    //
    {
    }

}

TEST( RegisterMap, AddRegister) {
    //
    //	
    //
    RegisterMap regMap("DUT");
    EXPECT_EQ( regMap.getSize(), 0);

    Register    reg0( 8, "reg0", 0x00, "0xAA");
    EXPECT_EQ( regMap.addRegister(reg0), true);
    cout << __func__ << regMap.getSize() << endl;

    EXPECT_EQ( regMap.getSize(), 1);

    cout << regMap[0] << endl;

    regMap[0]      = 0x00; cout << regMap[0] << endl;
    regMap["reg0"] = 0xFF; cout << regMap["reg0"] << endl;

    EXPECT_EQ( regMap.addRegister(reg0), false);
}
TEST( RegisterMap, KeywordAccess) {
    //
    //	
    //
    RegisterMap regMap("DUT");
    Register    reg0( 8, "reg0", 0x00, "0x00");
    Register    reg1( 8, "reg1", 0x00, "0xFF");
}

TEST(RegisterMap, LValue_Assignment) {
    //
    // Tests for LValue assignment
    //
}

TEST(RegisterMap,RValue_Assignment) {

}

TEST(RegisterMap, StringIndexing) {
}

TEST(RegisterMap, IntegerAssignmentOperator) {
}


TEST(RegisterMap, StringAssignmentOperator) {
}

int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

	std::string input;
	std::cin >> input;
}

