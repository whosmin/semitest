
#include "Expr.h"
#include "muParser.h"

#include <iostream>

using namespace std;

mu::Parser mp;

double* AddVariable( const char* name, void* pUserData) {
    static double valBuf[1000];
    static int iVal;

    valBuf[iVal] = 0;
    if(iVal >= 1000) {
        std::cerr << "Variable buffer overflow" << std::endl;
        return NULL;
    }

    return &valBuf[iVal++];
}

namespace Stil {

    Expr::Expr() {
    }

    double Expr::eval() {
        double result = 0.0;

        return result;
    }

}

