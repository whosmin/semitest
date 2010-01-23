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

#include "../Core/testLib.h"

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
        //ASSERT_EQ( testReg_0["bit 0"], false);


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

	

	std::string input;
	std::cin >> input;
}
