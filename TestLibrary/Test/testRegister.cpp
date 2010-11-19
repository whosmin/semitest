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


//
// Register class test fixture
//
class RegisterTest : public ::testing::Test {
    public:
        RegisterTest() {
            reg0 = Register( 8, "reg_0x00", 0x00);
            reg1 = Register( 8, "reg_0x01", 0x01);
            reg2 = Register( 8, "reg_0x02", 0x02);
        }

        virtual void SetUp() {
            reg0.setBitName( 0, "bit 0");
            reg0.setBitName( 1, "bit 1");
            reg0.setBitName( 2, "bit 2");
            reg0.setBitName( 3, "bit 3");
            reg0.setBitName( 4, "bit 4");
            reg0.setBitName( 5, "bit 5");
            reg0.setBitName( 6, "bit 6");
            reg0.setBitName( 7, "bit 7");

            reg0 = 0xAA;

        }

        Register reg0, reg1, reg2;
};

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
    testReg_0.setBitName( 0, "bit 0");
    testReg_0.setBitName( 1, "bit 1");
    testReg_0.setBitName( 2, "bit 2");
    testReg_0.setBitName( 3, "bit 3");
    testReg_0.setBitName( 4, "bit 4");
    testReg_0.setBitName( 5, "bit 5");
    testReg_0.setBitName( 6, "bit 6");
    testReg_0.setBitName( 7, "bit 7");

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

	testReg_0["bit 0"] = true;
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
    tribool temp = testReg_0["bit 0"].get(0);
    cout << (bool) testReg_0["bit 0"].get(0) << endl;
    //cout << "Initial value : " << testReg_0["bit 0"] << endl;
    testReg_0["bit 0"] = false;
    //cout << "After setting : " << testReg_0["bit 0"] << endl;

    ASSERT_EQ( testReg_0.get(0), false) << "subscript operator with string argument";

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

TEST_F( RegisterTest, setName_and_get) {
    vector<unsigned int> indices;

    indices.clear();
    indices.push_back(0);
    indices.push_back(1);
    reg0.setName( "first_two", indices); 

    indices.clear();
    indices.push_back(0);
    indices.push_back(2);
    indices.push_back(4);
    indices.push_back(6);
    reg0.setName( "even", indices); 

    indices.clear();
    indices.push_back(1);
    indices.push_back(3);
    indices.push_back(5);
    indices.push_back(7);
    reg0.setName( "odd", indices); 

    cout << reg0 << endl;

    ASSERT_EQ( reg0.get("first_two"), 2);
    ASSERT_EQ( reg0.get("even"), 0);
    ASSERT_EQ( reg0.get("odd"), 15);

	reg0.set("first_two", 0);
	ASSERT_EQ( reg0.get("first_two"), 0);
	reg0.set("first_two", 1);
	ASSERT_EQ( reg0.get("first_two"), 1);

	reg0.set( "odd", 7);

	reg0.set("bit 0", 1);

    Register agcReg( 8, "AFE Gain Control", 0x01, 0x0F);
    agcReg.setBitName( 0, "AGC");
    indices.clear();
    indices.push_back(4);
    indices.push_back(5);
    agcReg.setName( "Res", indices);
    agcReg.setBitName( 4, "some name");

    cout << agcReg << endl;
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
