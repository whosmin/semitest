
#ifndef __EXPR_H__
#define __EXPR_H__

#include <string>

using namespace std;

namespace Stil {

    class Expr {
        public:
            Expr();

            Expr& operator=(const string& rstr);
            string str;
            double eval();

        protected:
            double value;
            string unit;
    };

}

#endif

