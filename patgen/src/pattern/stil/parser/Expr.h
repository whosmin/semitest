
#ifndef __EXPR_H__
#define __EXPR_H__

#include <string>

using namespace std;

namespace Stil {

    class Expr {
        public:
            Expr();
            Expr(const string& exprStr);

            Expr& operator=(const string& rstr);
            Expr& operator=(const double val);
            string str;
            double eval();
            double getValue() { return value; }

            static bool addVar( string name, double value);
        protected:
            static double _eval(string str);
            static string removeUnwanted(const string& str);

        protected:
            double value;
            string unit;
    };


}

#endif

