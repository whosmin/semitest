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
#include <gtest/gtest.h>

using namespace std;

#include "testLib.h"

using namespace TestLib;

int main(int argc, char** argv) {
	//
	// Constructor and Assignment Tests
	//
	Register testReg_0(8, "test_0x00", 0x00);
	testReg_0.setBitName( 0, "bit 0");
	testReg_0.setBitName( 1, "bit 1");
	testReg_0.setBitName( 2, "bit 2");
	testReg_0.setBitName( 3, "bit 3");
	testReg_0.setBitName( 4, "bit 4");
	testReg_0.setBitName( 5, "bit 5");
	testReg_0.setBitName( 6, "bit 6");
	testReg_0.setBitName( 7, "bit 7");

	Register testReg_1(8, "test_0x00", 0x01);

	// Tests for getSize() function
	cout << "Register size " << testReg_0.getSize() << endl;
	cout << testReg_0 << endl;

	//
	//	Printing and stdout tests
	//
	testReg_0.print(cout);
	testReg_0.printDetailed(cout);
	cout.flags ( ios::right | ios::hex | ios::showbase );
	testReg_0.print(cout);
	cout.flags ( ios::right | ios::dec );

	//
	// Tests for LValue assignment
	//
	testReg_0[0] = true;
	testReg_0.print(cout);
	//testReg_0[0] = indeterminate;
	//testReg_0.print(cout);

	//
	// Tests for RValue operations
	//
	bool bit = false;
	bit = testReg_0[0];
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

	cout << "Testing string index" << endl;
	cout << "--------------------" << endl;
	cout << testReg_0["bit 0"] << endl;
	testReg_0["bit 0"] = false;
	cout << testReg_0["bit 0"] << endl;
	ASSERT_EQ( testReg_0["bit 0"], false);


	//
	// Test setDefault
	//
	testReg_0.setDefault("01010101");

	//
	// RegisterBank Tests
	//
	RegisterBank dutRegMap("F761586");
	cout << "dutRegMap.getSize()\t" << dutRegMap.getSize() << endl;
	dutRegMap.addRegister(testReg_0);
	cout << "dutRegMap.getSize()\t" << dutRegMap.getSize() << endl;
	Register temp( 8);
	temp = dutRegMap[0];

	dutRegMap[0].print(cout);
	dutRegMap.printDetailed(cout);

	// BQ51K Tests
	{
		cout << endl << endl << endl;

		Register mem_0( 8, "mem_0", 0x10);
		mem_0.setBitName( 7, "SPARE" );
		mem_0.setBitName( 6, "Quick I2C" );
		mem_0.setBitName( 5, "Soft Reset" );
		mem_0.setBitName( 4, "Enable External Clock" );
		mem_0.setBitName( 3, "Emulator Mode" );
		mem_0.setBitName( 2, "ROM Dump Mode" );
		mem_0.setBitName( 1, "TMOD_LOCKED[1]" );
		mem_0.setBitName( 0, "TMOD_LOCKED[0]" );

		Register mem_1( 8, "mem_1", 0x11);
		mem_1.setBitName( 7, "SPARE");
		mem_1.setBitName( 6, "Digital mux Select[6]");
		mem_1.setBitName( 5, "Digital mux Select[5]");
		mem_1.setBitName( 4, "Digital mux Select[4]");
		mem_1.setBitName( 3, "Digital mux Select[3]");
		mem_1.setBitName( 2, "Digital mux Select[2]");
		mem_1.setBitName( 1, "Digital mux Select[1]");
		mem_1.setBitName( 0, "Digital mux Select[0]");

		Register mem_3( 8, "mem_3", 0x13);
		mem_1.setBitName( 7, "Copy EE");
		mem_1.setBitName( 6, "Use/Read Soft Trim");
		mem_1.setBitName( 5, "Enable EE Burn");
		mem_1.setBitName( 4, "Read EE during Burn");
		mem_1.setBitName( 3, "Force Charge Enable");
		mem_1.setBitName( 2, "Force Enables");
		mem_1.setBitName( 1, "EN1");
		mem_1.setBitName( 0, "EN2");

		RegisterBank bq51k("bq51010");
		bq51k.addRegister(mem_0);
		bq51k.addRegister(mem_1);
		bq51k.addRegister(mem_3);
		bq51k[0].print(cout);
		bq51k.printDetailed(cout);

		bq51k.addRegister( mem_3);
	}

	std::string input;
	std::cin >> input;
}
