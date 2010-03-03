
#include "Expr.h"
#include "muParser.h"

#include <iostream>

using namespace std;

mu::Parser mp;

double* AddVariable( const char* name, void* pUserData) {
    static double valBuf[1000];
    static int iVal = 0;

    cout << "Generating new variable " << name << " (slots left: " << 1000 - (iVal + 1) << ")" << endl;

    valBuf[iVal] = 0;
    if(iVal >= 1000) {
        std::cerr << "Variable buffer overflow" << std::endl;
        return NULL;
    }

    return &valBuf[iVal++];
}


double unit_1(double val) {
    return val;
}
double unit_m(double val) {
    return val / 1e3;
}
double unit_u(double val) {
    return val / 1e6;
}
double unit_n(double val) {
    return val / 1e9;
}
double unit_p(double val) {
    return val / 1e12;
}

namespace Stil {

    Expr::Expr() {
        value = 0.0;
        unit = "";
    }

    double Expr::eval() {
        double result = 0.0;

        string tempstr = str;

        if(tempstr.size() > 1) {
            if(tempstr[0] == '\'' && tempstr[tempstr.size()-1] == '\'') {
                tempstr.erase( 0, 1);
                tempstr.erase(tempstr.size()-1, 1);
            }
        }

        try {
            double fval = 0.0;

            mp.SetVarFactory( AddVariable, NULL);
            //
            // Engineering units
            //
            mp.DefinePostfixOprt( "V", unit_1);
            mp.DefinePostfixOprt( "A", unit_1);
            mp.DefinePostfixOprt( "mA", unit_m);
            mp.DefinePostfixOprt( "uA", unit_u);
            mp.DefinePostfixOprt( "nA", unit_n);
            mp.DefinePostfixOprt( "pA", unit_p);
            mp.DefinePostfixOprt( "ms", unit_m);
            mp.DefinePostfixOprt( "us", unit_u);
            mp.DefinePostfixOprt( "ns", unit_n);
            mp.DefinePostfixOprt( "ps", unit_p);

            mp.SetExpr(tempstr);
            fval = mp.Eval();
            result = fval;
        }
        catch (mu::Parser::exception_type &e)
        {
            std::cout << e.GetMsg() << std::endl;
        }

        return result;
    }

    Expr& Expr::operator=(const string& rstr)
    {
        str = rstr;
        return *this;
    }
}

