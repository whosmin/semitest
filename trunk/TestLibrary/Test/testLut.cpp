

#include <cstdlib>
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "../Core/testLib.h"

using namespace std;
using namespace TestLib;

void custom_exit(void) {
    cout << "Exiting. Goodbye...." << endl;
}

#ifdef _MSC_VER
const std::string fileName = "../../Test/lut.txt";
#else
const std::string fileName = "../../../Test/lut.txt";
#endif

TEST(Lut, Read) {
    Lut<string, unsigned int> digmux;
    ASSERT_EQ( digmux.read( fileName, ","), true);
}
TEST(Lut, InvalidKey) {
    Lut<string, unsigned int> digmux;

    digmux.read( fileName, ",");

    cout << digmux["Two"] << endl;
    digmux["Two"] = 10;
    cout << digmux["Two"] << endl;

    EXPECT_DEATH( digmux["Eleven"], "Invalid key");
    //cout << digmux["Eleven"] << endl;
    digmux.insert( pair<string, unsigned int>( "Eleven", 11));
    EXPECT_EQ( digmux["Eleven"], 11);
    cout << digmux["Eleven"] << endl;

}

int main(int argc, char** argv) {
    atexit(custom_exit);

    ::testing::InitGoogleTest(&argc, argv);
    //return RUN_ALL_TESTS();

        return RUN_ALL_TESTS();
	
        //std::string input;
        //std::cin >> input;

}

