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

//
// Constructor Tests
//
TEST(Register, Constructor) {
    //
    //  Size upon construction
    //
    {
        Register reg(8, "test_0x00", 0x01);
        EXPECT_EQ(reg.getSize(), 8) << "Check for size upon construction";
        cout << reg << endl;
    }
    //
    //  State upon construction
    //
    {
        Register reg(8, "reg0", 0x00);
        EXPECT_EQ(reg.getState(), "xxxxxxxx") << "Check for state upon construction";
        cout << reg << endl;

        Register reg1(8, "reg1", 0x01, "0xAA");
        EXPECT_EQ(reg1.getState(), "10101010") << "Check for state upon construction";
        cout << reg1 << endl;

        Register reg2(8, "reg2", 0x02, 0x55);
        EXPECT_EQ(reg2.getState(), "01010101") << "Check for state upon construction";
        cout << reg2 << endl;
    }
    //
    //  Default State upon construction
    //
    {
        Register reg(8, "test_0x00", 0x01);
        EXPECT_EQ(reg.getDefaultState(), "xxxxxxxx") << "Check for default state upon construction";
        cout << reg << endl;
        Register reg1(8, "test_0x00", 0x01, "0xAA");
        EXPECT_EQ(reg1.getDefaultState(), "10101010") << "Check for default state upon construction";
        cout << reg1 << endl;
    }

}

TEST(Register,Print) {

    Register testReg_0(8, "test_0x00", 0x00);
    testReg_0.setBitName( 0, "bit 0");
    testReg_0.setBitName( 1, "bit 1");
    testReg_0.setBitName( 2, "bit 2");
    testReg_0.setBitName( 3, "bit 3");
    testReg_0.setBitName( 4, "bit 4");
    testReg_0.setBitName( 5, "bit 5");
    testReg_0.setBitName( 6, "bit 6");
    testReg_0.setBitName( 7, "bit 7");

    //
    //	Printing and stdout tests
    //
    stringstream sstr;

    testReg_0.print(cout);
    testReg_0.printDetailed(cout);
    cout.flags ( ios::right | ios::hex | ios::showbase );
    testReg_0.print(cout);
    cout.flags ( ios::right | ios::dec );
}

TEST(Register,LValue_Assignment) {
    Register testReg_0(8, "test_0x00", 0x00, "0xF0");

    //
    // Tests for LValue assignment
    //
    testReg_0[0] = true;
    cout << testReg_0[0] << endl;
	EXPECT_EQ( (bool) testReg_0[0], true) << "should be true";
    testReg_0.print(cout);
    testReg_0[0] = false;
	EXPECT_EQ( (bool) testReg_0[0], false) << "should be false";
    testReg_0.print(cout);
    //testReg_0[0] = indeterminate;
    //testReg_0.print(cout);
}

TEST(Register,RValue_Assignment) {
    Register testReg_0(8, "test_0x00", 0x00, "0xFF");
    //
    // Tests for RValue operations
    //
    bool bit = false;
    bit = testReg_0[0];
    EXPECT_EQ( bit, true) << "should be true";
    //bit = testReg_0[0] & false;
    //bit = testReg_0[0] | false;

    //
    // Tests for bitwise operators
    //
    testReg_0[0] = true;
    bit = true;
    bit = testReg_0[0] & false;
    cout << bit << endl;
    bit = testReg_0[0] | true;
    cout << bit << endl;

}

TEST(Register, StringIndexing) {
    Register testReg_0(8, "test_0x00", 0x00);
    testReg_0.setBitName( 0, "bit 0");
    testReg_0.setBitName( 1, "bit 1");
    testReg_0.setBitName( 2, "bit 2");
    testReg_0.setBitName( 3, "bit 3");
    testReg_0.setBitName( 4, "bit 4");
    testReg_0.setBitName( 5, "bit 5");
    testReg_0.setBitName( 6, "bit 6");
    testReg_0.setBitName( 7, "bit 7");

    cout << "Testing string index" << endl;
    cout << "--------------------" << endl;
	testReg_0[0] = true;
	cout << "Initial value : " << testReg_0["bit 0"] << endl;
    testReg_0["bit 0"] = false;
	cout << "After setting : " << testReg_0["bit 0"] << endl;
    ASSERT_EQ( testReg_0["bit 0"], false) << "subscript operator with string argument";

	EXPECT_DEATH( testReg_0["invalid_name"], "bitNameToIndex");
}

TEST(Register, SetDefault) {
	Register testReg_0(8, "test_0x00", 0x00);
    testReg_0.setBitName( 0, "bit 0");
    testReg_0.setBitName( 1, "bit 1");
    testReg_0.setBitName( 2, "bit 2");
    testReg_0.setBitName( 3, "bit 3");
    testReg_0.setBitName( 4, "bit 4");
    testReg_0.setBitName( 5, "bit 5");
    testReg_0.setBitName( 6, "bit 6");
    testReg_0.setBitName( 7, "bit 7");
    //
    // Test setDefault
    //
    testReg_0.setDefault("01010101");
    cout << testReg_0 << endl;

    testReg_0.setState("10101010");
    cout << testReg_0 << endl;

}

TEST( Register, Get) {
	Register reg0(8, "reg0", 0x00, 0x55);
	EXPECT_EQ( reg0.get(), 0x55);
	cout << reg0.get() << endl;
}

TEST(Register, IntegerAssignmentOperator) {
    Register testReg_0(8, "test_0x00", 0x00);
    testReg_0.setBitName( 0, "bit 0");
    testReg_0.setBitName( 1, "bit 1");
    testReg_0.setBitName( 2, "bit 2");
    testReg_0.setBitName( 3, "bit 3");
    testReg_0.setBitName( 4, "bit 4");
    testReg_0.setBitName( 5, "bit 5");
    testReg_0.setBitName( 6, "bit 6");
    testReg_0.setBitName( 7, "bit 7");

    cout << testReg_0 << endl;

    testReg_0 = 0xAA; cout << testReg_0 << endl;
    testReg_0 = 0x55; cout << testReg_0 << endl;
    testReg_0.setState( 0xF0); cout << testReg_0 << endl;
    testReg_0.setState( 0x0F); cout << testReg_0 << endl;

    testReg_0 = 0x18ULL; cout << testReg_0 << endl;
    testReg_0 = 0x81ULL; cout << testReg_0 << endl;
}


TEST(Register, StringAssignmentOperator) {
    Register testReg_0(8, "test_0x00", 0x00);
    testReg_0.setBitName( 0, "bit 0");
    testReg_0.setBitName( 1, "bit 1");
    testReg_0.setBitName( 2, "bit 2");
    testReg_0.setBitName( 3, "bit 3");
    testReg_0.setBitName( 4, "bit 4");
    testReg_0.setBitName( 5, "bit 5");
    testReg_0.setBitName( 6, "bit 6");
    testReg_0.setBitName( 7, "bit 7");

    cout << testReg_0 << endl;

    testReg_0 = "0xAA"; cout << testReg_0 << endl;
    testReg_0 = "0x55"; cout << testReg_0 << endl;
}

TEST(Register, Flip) {
    Register reg(8, "test_0x00", 0x00, "0xAA");
    reg.flip();
    cout << reg << endl;
}


TEST(Register, CopyConstructor) {
    Register reg( testReg);

    cout << reg << endl;
    ASSERT_EQ( reg.getBitName(0), "bit 0");
    ASSERT_EQ( reg.getBitName(1), "bit 1");
    ASSERT_EQ( reg.getBitName(2), "bit 2");
    ASSERT_EQ( reg.getBitName(3), "bit 3");
    ASSERT_EQ( reg.getBitName(4), "bit 4");
    ASSERT_EQ( reg.getBitName(5), "bit 5");
    ASSERT_EQ( reg.getBitName(6), "bit 6");
    ASSERT_EQ( reg.getBitName(7), "bit 7");
}

TEST( Register, AssignmentOperator) {
    Register reg;

    reg = testReg;
    cout << reg << endl;

    ASSERT_EQ( reg.getBitName(0), "bit 0");
    ASSERT_EQ( reg.getBitName(1), "bit 1");
    ASSERT_EQ( reg.getBitName(2), "bit 2");
    ASSERT_EQ( reg.getBitName(3), "bit 3");
    ASSERT_EQ( reg.getBitName(4), "bit 4");
    ASSERT_EQ( reg.getBitName(5), "bit 5");
    ASSERT_EQ( reg.getBitName(6), "bit 6");
    ASSERT_EQ( reg.getBitName(7), "bit 7");
}

TEST( Register, getStateValue) {
    Register reg(testReg);

    cout << reg.getStateInteger() << endl;
    ASSERT_EQ( reg.getStateInteger(), 0xAA);
}

TEST( Register, get) {
    Register reg(testReg);

    cout << reg.get() << endl;
    ASSERT_EQ( reg.get(), 0xAA);
}

TEST( Register, setName_and_get) {
    Register reg(testReg);

    vector<unsigned int> indices;

    indices.clear();
    indices.push_back(0);
    indices.push_back(1);
    reg.setName( "first_two", indices); 

    indices.clear();
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(4);
    indices.push_back(6);
    reg.setName( "even", indices); 

    indices.clear();
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(5);
    indices.push_back(7);
    reg.setName( "odd", indices); 

    cout << reg << endl;

    ASSERT_EQ( reg.get("first_two"), 2);
    ASSERT_EQ( reg.get("even"), 0);
    ASSERT_EQ( reg.get("odd"), 15);

    Register agcReg( 8, "AFE Gain Control", 0x01, 0x0F);
    agcReg.setBitName( 0, "AGC");
    indices.clear();
    indices.push_back(4);
    indices.push_back(5);
    agcReg.setName( "Res", indices);
    agcReg.setBitName( 4, "some name");

    cout << agcReg << endl;
}

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

    array1d<Register::integer_type, 2> temp = reg.get();
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

#if 0

	//
	// RegisterMap Tests
	//
	RegisterMap dutRegMap("F761586");
	cout << "dutRegMap.getSize()\t" << dutRegMap.getSize() << endl;
	dutRegMap.addRegister(testReg_0);
	cout << "dutRegMap.getSize()\t" << dutRegMap.getSize() << endl;
	Register temp( 8);
	temp = dutRegMap[0];

	dutRegMap[0].print(cout);
	dutRegMap.printDetailed(cout);
#endif
	

	std::string input;
	std::cin >> input;
}
