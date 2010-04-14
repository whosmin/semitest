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

int toInt(string str) {
    int value = 0;

    stringstream sstr;
    sstr << str;
    sstr >> value;

    return value;
}

Register createRegisterHelper( string str) {
    Register reg;

    unsigned int size = 0;
    string   name;
    string   address;
    string   defValue;
    string   slice;
    string   names;
    vector< vector<Register::size_type> > sliceIndices;
    vector<string>                 sliceNames;

    stringstream sstr;

    vector<string> fields = split( str, ";");
    if(fields.size() > 0) {
        size = toInt(fields[0]);
    }
    if(fields.size() > 1)
        name = fields[1];
    if(fields.size() > 2)
        address = fields[2];
    if(fields.size() > 3)
        defValue = fields[3];

    if(fields.size() > 1)
        reg = Register( size, name, address, defValue);

    if( fields.size() > 5) {
        slice = fields[4];
        names = fields[5];
        sliceNames = split( names, ",");
        vector<string> sliceVec = split( slice, ",");
        if(sliceNames.size() == sliceVec.size()) {
            for(unsigned int i=0; i < sliceVec.size(); i++) {
                vector<unsigned int> indices;
                vector<string>       digitVec = split( sliceVec[i], ":");
                unsigned int first = 0, second = 0;
                first = toInt(digitVec[0]);
                if(digitVec.size() > 1)
                    second = toInt(digitVec[1]);
               else
                   second = first;
                unsigned int start = std::min( first, second);
                unsigned int stop  = std::max( first, second);
                for(unsigned int i = start; i <= stop; i++)
                    indices.push_back(i);

                sliceIndices.push_back(indices);
            }
        }
        else {
            std::cerr << "slice names to slice vec mismatch." << endl;
            std::cerr  << slice << endl << names << endl;
        }
        for(unsigned int i=0; i < sliceNames.size(); i++) {
            reg.setName( sliceNames[i], sliceIndices[i]);
        }
    }

    return reg;
}

Register reg0( 8, "reg_0", 0x00, "0x55");
Register reg1( 8, "reg_1", 0x01, "0xAA");
Register reg2( 8, "reg_2", 0x01, "0xCC");
Register reg3( 8, "reg_3", 0x01, "0x33");

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

        ASSERT_EQ( dutRegMap.addRegister(reg0), true);
        ASSERT_EQ( dutRegMap.getSize(), 1);

        ASSERT_EQ( dutRegMap.addRegister(reg1), true);
        ASSERT_EQ( dutRegMap.getSize(), 2);

        ASSERT_EQ( dutRegMap.addRegister(reg1), false);
        ASSERT_EQ( dutRegMap.getSize(), 2) << "Check against duplicate name";

        cout << dutRegMap << endl;
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

TEST( RegisterMap, SliceCreation) {
    RegisterMap regMap("ABCDEF");
    regMap.addRegister(reg0);
    regMap.addRegister(reg1);
    regMap.addRegister(reg2);
    regMap.addRegister(reg3);

    cout << regMap << endl;

    vector< pair<string, Register::size_type> > slice;
    slice.push_back( pair<string, Register::size_type>( "reg_0", 0));
    slice.push_back( pair<string, Register::size_type>( "reg_0", 1));
    slice.push_back( pair<string, Register::size_type>( "reg_1", 0));
    slice.push_back( pair<string, Register::size_type>( "reg_1", 1));
    slice.push_back( pair<string, Register::size_type>( "reg_2", 0));
    slice.push_back( pair<string, Register::size_type>( "reg_2", 1));
    slice.push_back( pair<string, Register::size_type>( "reg_3", 0));
    slice.push_back( pair<string, Register::size_type>( "reg_3", 1));


    ASSERT_EQ( regMap.setName( "LSB_2", slice), true);
    ASSERT_EQ( regMap.get("LSB_2"), 201);

    slice.clear();
    slice.push_back( pair<string, Register::size_type>( "reg_0", 0));
    slice.push_back( pair<string, Register::size_type>( "reg_0", 7));

    ASSERT_EQ( regMap.setName( "name1", slice), true);
    ASSERT_EQ( regMap.get("name1"), 1);
}

//
// Use TVP5160 as an example device
// http://focus.ti.com/docs/prod/folders/print/tvp5160.html
//
TEST( RegisterMap, DeviceExampleTVP5160)
{
    vector<unsigned int> indices;

    RegisterMap regMap( "TVP5160");

    regMap.addRegister( Register( 8, "Input/Output Select", 0x00, 0x00));

    Register agcReg( 8, "AFE Gain Control", 0x01, 0x0F);
    agcReg.setBitName( 0, "AGC");
    indices.clear();
    indices.push_back(4);
    indices.push_back(5);
    indices.push_back(6);
    indices.push_back(7);
    agcReg.setName( "Reserved", indices);
    agcReg.setBitName( 4, "some name");
    cout << agcReg << endl;
    regMap.addRegister( agcReg);

#if 0
    regMap.addRegister( Register( 8, "AFE Gain Control", 0x01, 0x0F));
    //regMap["AFE Gain Control"].setBitName( 0, "AGC");
    regMap[0x01].setBitName( 0, "AGC");
    indices.clear();
    indices.push_back( 4); indices.push_back( 5); indices.push_back( 6); indices.push_back( 7);
    //regMap["AFE Gain Control"].setName( "Reserved", indices);
    regMap[0x01].setName( "Reserved", indices);
#endif

    regMap.addRegister( Register( 8, "Video Standard Select", 0x02, 0x00));
    indices.clear();
    indices.push_back( 4); indices.push_back( 5); indices.push_back( 6); indices.push_back( 7);
    regMap["Video Standard Select"].setName( "Reserved", indices);
    indices.clear();
    indices.push_back( 0); indices.push_back( 1); indices.push_back( 2); indices.push_back( 3);
    regMap["Video Standard Select"].setName( "Video standard", indices);

    regMap.addRegister( Register( 8, "Operation Mode", 0x03, 0x00));
    regMap["Operation Mode"].setBitName( 0, "Power save");

    regMap.addRegister( Register( 8, "Autoswitch Mask", 0x04, 0x23));
    regMap["Autoswitch Mask"].setBitName( 0, "(M, J) NTSC");
    regMap["Autoswitch Mask"].setBitName( 1, "PAL");
    regMap["Autoswitch Mask"].setBitName( 2, "(M) PAL");
    regMap["Autoswitch Mask"].setBitName( 3, "(Nc) PAL");
    regMap["Autoswitch Mask"].setBitName( 4, "NTSC 4.43");
    regMap["Autoswitch Mask"].setBitName( 5, "SECAM");
    regMap["Autoswitch Mask"].setBitName( 6, "PAL 60");
    regMap["Autoswitch Mask"].setBitName( 7, "Reserved");

    regMap.addRegister( Register( 8, "Color Killer", 0x05, 0x10));
    indices.clear();
    indices.push_back(5); indices.push_back(6);
    regMap["Color Killer"].setName( "Automatic color killer", indices);
    indices.clear();
    indices.push_back( 0); indices.push_back( 1); indices.push_back( 2); indices.push_back( 3);
    regMap["Color Killer"].setName( "Color killer threshold", indices);
    regMap["Color Killer"].setBitName( 7, "Reserved");

    //regMap.addRegister( createRegisterHelper( "8;Luminance Processing Control 1;0x06;0x00;7,6:5,4:0;Reserved,Automatic color killer,Color killer threshold"));
    //indices.clear();
    //indices.push_back(7);
    //regMap.addRegister( Register( 8, "Luminance Processing Control", 0x06, 0x00));
    //regMap["Luminance Processing Control"].setName( "Reserved", indices);
    //

    cout << regMap[0x00] << endl;
    cout << regMap[0x01] << endl;
    cout << regMap[0x02] << endl;
    cout << regMap[0x03] << endl;
    cout << regMap[0x04] << endl;
    cout << regMap[0x05] << endl;
    //cout << regMap[0x06] << endl;

    cout << regMap << endl;
}

//
// Use TAS3204 as an example device
// http://focus.ti.com/docs/prod/folders/print/tas3204.html
//
TEST( RegisterMap, DeviceExampleTAS3204)
{
    RegisterMap regMap( "TAS3204");
}

int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

	std::string input;
	std::cin >> input;
}

