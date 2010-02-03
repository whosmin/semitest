

#include <iostream>
#include <string>
#include "lut.h"

using namespace std;

int main(int argc, char** argv) {

    Lut<string, unsigned int> digmux;

    digmux.read( "../resource/bq2409x_digital_mux.ini", ",");

    //digmux["chg_stat_w"] = 64;

    cout << digmux["chg_stat_w"] << endl;
    cout << digmux["chg_stat_wa"] << endl;

    return 0;
}

