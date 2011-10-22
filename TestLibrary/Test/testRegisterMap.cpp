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
#include "../Core/utility.h"
#include "../Core/msRegisterMap.h"

template < class T >
    std::string toString(const T& value) {
            std::ostringstream oss;
            oss << value;
            return oss.str();
    }



using namespace TestLib;

int toInt(string str) {
    int value = 0;

    stringstream sstr;
    sstr << str;
    sstr >> value;

    return value;
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
	//regMap[0].print(cout);
	//Register reg0Ref = regMap[0];

    regMap[0]      = 0x00; //cout << regMap[0] << endl;
	regMap[0]      = 0xAA; //cout << regMap[0] << endl;
	cout << regMap[0].get() << endl;

    regMap["reg0"] = 0xFF; //cout << regMap["reg0"] << endl;

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
RegisterMap tvp5160( "TVP5160");
TEST( RegisterMap, DeviceExampleTVP5160)
{
    vector<unsigned int> indices;


    tvp5160.addRegister( Register( 8, "Input/Output Select", 0x00, 0x00));

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
    tvp5160.addRegister( agcReg);

#if 0
    tvp5160.addRegister( Register( 8, "AFE Gain Control", 0x01, 0x0F));
    //tvp5160["AFE Gain Control"].setBitName( 0, "AGC");
    tvp5160[0x01].setBitName( 0, "AGC");
    indices.clear();
    indices.push_back( 4); indices.push_back( 5); indices.push_back( 6); indices.push_back( 7);
    //tvp5160["AFE Gain Control"].setName( "Reserved", indices);
    tvp5160[0x01].get().setName( "Reserved", indices);
#endif

    tvp5160.addRegister( Register( 8, "Video Standard Select", 0x02, 0x00));
    indices.clear();
    indices.push_back( 4); indices.push_back( 5); indices.push_back( 6); indices.push_back( 7);
    tvp5160["Video Standard Select"].setName( "Reserved", indices);
    indices.clear();
    indices.push_back( 0); indices.push_back( 1); indices.push_back( 2); indices.push_back( 3);
    tvp5160["Video Standard Select"].setName( "Video standard", indices);

    tvp5160.addRegister( Register( 8, "Operation Mode", 0x03, 0x00));
    tvp5160["Operation Mode"].setBitName( 0, "Power save");

#if 0
    tvp5160.addRegister( Register( 8, "Autoswitch Mask", 0x04, 0x23));
    tvp5160["Autoswitch Mask"].setBitName( 0, "(M, J) NTSC");
    tvp5160["Autoswitch Mask"].setBitName( 1, "PAL");
    tvp5160["Autoswitch Mask"].setBitName( 2, "(M) PAL");
    tvp5160["Autoswitch Mask"].setBitName( 3, "(Nc) PAL");
    tvp5160["Autoswitch Mask"].setBitName( 4, "NTSC 4.43");
    tvp5160["Autoswitch Mask"].setBitName( 5, "SECAM");
    tvp5160["Autoswitch Mask"].setBitName( 6, "PAL 60");
    tvp5160["Autoswitch Mask"].setBitName( 7, "Reserved");
#endif
    //tvp5160.addRegister( createRegisterHelper( "8;Autoswitch Mask;0x04;0x23;0,1,2,3,4,5,6,7;(M, J) NTSC,PAL,(M) PAL,(Nc) PAL,NTSC 4.43,SECAM,PAL 60,Reserved"));
    tvp5160.addRegister( Register::createRegisterHelper( "8;Autoswitch Mask;0x04;0x23;0,1,2,3,4,5,6,7;(M J) NTSC,PAL,(M) PAL,(Nc) PAL,NTSC 4.43,SECAM,PAL 60,Reserved"));

#if 0
    tvp5160.addRegister( Register( 8, "Color Killer", 0x05, 0x10));
    indices.clear();
    indices.push_back(5); indices.push_back(6);
    tvp5160["Color Killer"].setName( "Automatic color killer", indices);
    indices.clear();
    indices.push_back( 0); indices.push_back( 1); indices.push_back( 2); indices.push_back( 3);
    tvp5160["Color Killer"].setName( "Color killer threshold", indices);
    tvp5160["Color Killer"].setBitName( 7, "Reserved");
#endif
    tvp5160.addRegister( Register::createRegisterHelper( "8;Color Killer;0x05;0x10;5:6,0:3,7;Automatic color killer,Color killer threshold,Reserved"));

    tvp5160.addRegister( Register::createRegisterHelper( "8;Luminance Processing Control 1;0x06;0x00;7,6:5,4:0;Reserved,Automatic color killer,Color killer threshold"));
    //indices.clear();
    //indices.push_back(7);
    //tvp5160.addRegister( Register( 8, "Luminance Processing Control", 0x06, 0x00));
    //tvp5160["Luminance Processing Control"].setName( "Reserved", indices);
    //

#if 0
    cout << tvp5160[0x00] << endl;
    cout << tvp5160[0x01] << endl;
    cout << tvp5160[0x02] << endl;
    cout << tvp5160[0x03] << endl;
    cout << tvp5160[0x04] << endl;
    cout << tvp5160[0x05] << endl;
    //cout << tvp5160[0x06] << endl;
#endif
    cout << tvp5160 << endl;
}

//
// Use TAS3204 as an example device
// http://focus.ti.com/docs/prod/folders/print/tas3204.html
//
TEST( RegisterMap, DeviceExampleTAS3204)
{
    RegisterMap tas3204( "TAS3204");
}

//
// Test multi-site access
//
TEST( RegisterMap, MultiSiteRegisterMap)
{
#if 0
    MSArray<RegisterMap> temp(tvp5160);
    cout << temp.size() << endl;
    for(unsigned int site = 0; site < temp.size(); site++) {
        temp[site].printDetailed( cout, "site[" + ::toString(site) + "] ");
    }
#endif

    MSRegisterMap<2> map(tvp5160);
    for(std::size_t site = 0; site < map.size(); site++) {
        map[site].printDetailed( cout, "site[" + ::toString(site) + "] ");
        //map[site].printDetailed( cout);
    }
}

int main(int argc, char** argv) {

    ::testing::InitGoogleTest(&argc, argv);
#ifdef _MSC_VER
    RUN_ALL_TESTS();

	std::string input;
	std::cin >> input;
#else
	return RUN_ALL_TESTS();
#endif
}

