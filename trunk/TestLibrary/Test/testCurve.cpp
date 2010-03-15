#include <cstdlib>
#include <iostream>
#include <string>
#include <gtest/gtest.h>
#include "../Core/testLib.h"
#include "../Core/curve.h"

using namespace std;
using namespace TestLib;

void custom_exit(void) {
    cout << "Exiting. Goodbye...." << endl;
}

double x[7] = { 1.5, 2.4, 3.2, 4.8,  5.0, 7.0,  8.43 };
double y[7] = { 3.5, 5.3, 7.7, 6.2, 11.0, 9.5, 10.27 };
double reg_x[6] = { 0.0, 0.6, 1.2, 1.8, 2.4, 3.0 };

TEST(Curve, CubicSpline) {
    TestLib::Curve curve(Curve::NATURAL_CUBIC_SPLINE);
    for(unsigned int i=0; i < 7; i++)
        curve.addPoint( x[i], y[i]);

    string sep = " ";
    for(unsigned int i=0; i < 6; i++) {
        cout << reg_x[i] << sep << curve.value( reg_x[i]) << endl;
    }
}
TEST(Curve, Linear) {
}

int main(int argc, char** argv) {
    atexit(custom_exit);

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

