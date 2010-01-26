//
// This file is part of SemiTest
//
// SemiTest is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Foobar is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2010 Tushar Jog

#include "utility.h"
#include <cmath>
#include <iostream>

using namespace std;
using namespace boost::logic;

namespace TestLib {

    std::string trim( std::string& s, const std::string& drop)
    {
            std::string r=s.erase(s.find_last_not_of(drop)+1);
            return r.erase(0,r.find_first_not_of(drop));
    }

    std::string trim( const std::string& str, const std::string& drop)
    {
            std::string temp = str;
            temp = temp.erase( temp.find_last_not_of(drop)+1);
            return temp.erase( 0, temp.find_first_not_of(drop));
    }

    bool stringToBool(const std::string& str) {
            bool result = false;

            return result;
    }

    double stringToDouble(const std::string& str) {
            double result;
            std::istringstream iss(str);
            iss >> result;
            return result;
    }

    template < class T >
    std::string toString(const T& value) {
            std::ostringstream oss;
            oss << value;
            return oss.str();
    }

		//                         Index
		//                         76543210
		//  -------------------------------
		//	"01110111"	=> 0x77	=> 01110111
		//  "0111_0111" => 0x77 => 01110111
		//  "0b01110111 => 0x77	=> 01110111
		//  "0x77"      => 0x77	=> 01110111
	bool stringToBool(const std::string& str, vector<tribool> binaryVec, const unsigned int maxSize) {
        bool result = true;

		std::string mystr = trim(str);
        remove_substr( mystr, "_");
        binaryVec.clear();

		bool isHexPrefix   = false;
		bool isBoolPrefix  = false;
		bool isOctalPrefix = false;

		if(mystr.size() > 2) {
			if(mystr[0] == '0' && mystr[1] == 'x') {
				isHexPrefix = true;
				mystr.erase( 0, 2);
				std::stringstream sstr(mystr);
				//sstr >> bin >> mystr;
			}
			else if(mystr[0] == '0' && mystr[1] == 'b') {
				isBoolPrefix = true;
				mystr.erase( 0, 2);
			}
		}
		bool isPrefix = isHexPrefix | isBoolPrefix | isOctalPrefix;




		bool isBinaryValue  = false;
		bool isOctalValue = false;
		bool isHexValue   = false;
		bool isInvalidValue = false;
		for(unsigned int i=0; i < mystr.size(); i++) {
			switch(mystr[i]) {
				case '0': 
				case '1': isBinaryValue = true; break;
				case '2': 
				case '3':
				case '4':
				case '5':
				case '6':
				case '7': isOctalValue = true; break;
				case '8': 
				case '9':
				case 'A':
				case 'B':
				case 'C':
				case 'D':
				case 'E':
				case 'F': isHexValue = true; break;
				default: isInvalidValue = true; break;
			};
		}

        unsigned long int value;
        if(isHexValue) {
            stringstream sstr;
            sstr << sstr;
            sstr >> hex >> value;
        }
        else if(isOctalValue) {
            stringstream sstr;
            sstr << sstr;
            sstr >> oct >> value;
        }
        else if(isBinaryValue) {
        }
        cout << __func__ << " : " << value << endl;

		// Truncate extra bits
		if( maxSize > 0 && mystr.size() > maxSize) {
			reverse(mystr.begin(), mystr.end());
			mystr.resize(maxSize);
			reverse(mystr.begin(), mystr.end());
		}

		// Convert to lower case
        std::transform(mystr.begin(), mystr.end(), mystr.begin(), ::tolower);

		// Conver to binary


		return result;
	}

    long int stringToLong(const string &str, unsigned int base) {
        const unsigned int max_base = 16;
        // Check if base is valid
        if((base <= 1) || (base > max_base)) base = 10;

        long int result = 0L;
        register long int num1 = 0L;
        register long int num2 = 0L;
        register long int lbase = (long int) base;
        long int sign  = 1;

        int index;
        int max = str.size();

        bool exp_notation = false;
        bool found = false;
        for(index = 0; index < max; index++) {
            char chr = str[index];
            if((chr == ' ') || (chr == '\t') || (chr == '\r')) {
                if(found) break; else continue;
            }
            if((chr == '-') && (found == false)) { sign = -1; found = true; continue; }
            if((chr == '+') && (found == false)) { sign = +1; found = true; continue; }

            chr = toupper(chr);
    //        if(chr > 'F') { if(found) break; else continue; }

            if(::isalnum(chr)) {
                register long int num = 0L;
                if(::isdigit(chr))
                    num = chr - '0';
                else
                    num = chr - 'A' + 10;

                if(num >= lbase) {
                    if((base == 10) && (chr == 'E') && (found == true)) {
                        exp_notation = true;
                        continue;
                    }
                    else
                        break;
                }
                else {
                    found = true;
                    if(exp_notation == true)
                        num2 = num2*lbase + num;
                    else
                        num1 = num1*lbase + num;
                }
            }

        }
        
    //    cout << num1 << "\t" << num2 << "\t" << exp_notation << endl;

        result = num1;
        if(exp_notation == true) result *= (long int) pow((double) lbase, (double) num2);

        result = result * sign;

        return result;
    }

//    double stringToDouble(const string& str) {
//        double value = 0.0;
//        stringstream sstr(str);
//        sstr >> value;
//        if(sstr.fail())
//            value = 0.0;
//        return value;
//    }

    void remove_substr(string &str, string unwanted) {

        string::size_type pos = str.find(unwanted, 0);
        while(pos != string::npos) { // Found
            str.erase(pos, unwanted.size());
            pos = str.find(unwanted, 0);
        }

        return;
    }




}

