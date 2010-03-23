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
#include <map>
#include <limits>

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
        //  "0b011x_xxx0 =>
    bool stringToBool(const std::string& str, vector<tribool>& binaryVec,
            const unsigned int maxSize,
            unsigned long long& value) {
        bool result = true;


        map<char, unsigned int> hexMap;
        map<char, string>       hexToBinaryMap, octToBinaryMap;

        hexMap['0'] = 0;      hexToBinaryMap['0'] = "0000";   octToBinaryMap['0'] = "000";
        hexMap['1'] = 1;      hexToBinaryMap['1'] = "0001";   octToBinaryMap['1'] = "001";
        hexMap['2'] = 2;      hexToBinaryMap['2'] = "0010";   octToBinaryMap['2'] = "010";
        hexMap['3'] = 3;      hexToBinaryMap['3'] = "0011";   octToBinaryMap['3'] = "011";
        hexMap['4'] = 4;      hexToBinaryMap['4'] = "0100";   octToBinaryMap['4'] = "100";
        hexMap['5'] = 5;      hexToBinaryMap['5'] = "0101";   octToBinaryMap['5'] = "101";
        hexMap['6'] = 6;      hexToBinaryMap['6'] = "0110";   octToBinaryMap['6'] = "110";
        hexMap['7'] = 7;      hexToBinaryMap['7'] = "0111";   octToBinaryMap['7'] = "111";
        hexMap['8'] = 8;      hexToBinaryMap['8'] = "1000";
        hexMap['9'] = 9;      hexToBinaryMap['9'] = "1001";
        hexMap['a'] = 10;     hexToBinaryMap['a'] = "1010";
        hexMap['b'] = 11;     hexToBinaryMap['b'] = "1011";
        hexMap['c'] = 12;     hexToBinaryMap['c'] = "1100";
        hexMap['d'] = 13;     hexToBinaryMap['d'] = "1101";
        hexMap['e'] = 14;     hexToBinaryMap['e'] = "1110";
        hexMap['f'] = 15;     hexToBinaryMap['f'] = "1111";

        // Trim leading and lagging whitespace
		std::string mystr = trim(str);
        // Remove unwanted characters
        remove_substr( mystr, "_");
        // Convert to lower case
        std::transform(mystr.begin(), mystr.end(), mystr.begin(), ::tolower);

        binaryVec.clear();

		bool isHexPrefix   = false;
        bool isBinaryPrefix = false;
		bool isOctalPrefix = false;

        //
        // Determine if prefix exists and if so determine if prefix is for bool,hex or octal
        // "0b" => bool
        // "0o" => octal
        // "0x" => hex
        //
		if(mystr.size() > 2) {
			if(mystr[0] == '0' && mystr[1] == 'x') {
				isHexPrefix = true;
				mystr.erase( 0, 2);
				std::stringstream sstr(mystr);
				//sstr >> bin >> mystr;
			}
			else if(mystr[0] == '0' && mystr[1] == 'b') {
                isBinaryPrefix = true;
				mystr.erase( 0, 2);
			}
		}
        bool isPrefix = isHexPrefix | isBinaryPrefix | isOctalPrefix;


        bool hasBinaryChar   = false;
        bool hasTriboolChar   = false;
        bool hasOctalChar    = false;
        bool hasDecimalChar  = false;
        bool hasHexChar      = false;
        bool hasInvalidChar  = false;
        for(unsigned int i=0; i < mystr.size(); i++) {
			switch(mystr[i]) {
				case '0': 
                case '1': hasBinaryChar = true; break;
                case 'x': hasTriboolChar = true; hasBinaryChar = true; break;
				case '2': 
				case '3':
				case '4':
				case '5':
				case '6':
                case '7': hasOctalChar = true; break;
				case '8': 
                case '9': hasDecimalChar = true; break;
                case 'a':
                case 'b':
                case 'c':
                case 'd':
                case 'e':
                case 'f': hasHexChar = true; break;
                default:  hasInvalidChar = true; break;
			};
		}

        //bool isBinaryValue  = (isBinaryPrefix & hasBinaryChar) | ((!isPrefix) & ((hasTriboolChar | hasBinaryChar) & (!hasOctalChar) & (!hasDecimalChar) & (!hasHexChar)));
        bool isBinaryValue  = (isBinaryPrefix & (hasBinaryChar | hasTriboolChar))   |    ((!isPrefix) & ((hasTriboolChar) & (!hasOctalChar) & (!hasDecimalChar) & (!hasHexChar)));
        bool isOctalValue   = isOctalPrefix & (hasOctalChar | hasBinaryChar);
        bool isDecimalValue = (!isPrefix) & (hasDecimalChar | hasOctalChar | hasBinaryChar) & (!hasHexChar) & (!hasTriboolChar);
        bool isHexValue     = isHexPrefix & (!hasInvalidChar);
        bool isInvalidValue = hasInvalidChar | ((isOctalValue | isDecimalValue | isHexValue) & hasTriboolChar);

        if(isInvalidValue) {
            cerr << "ERROR " << __func__ << " : Input string \"" << str << "\" has invalid characters." << endl;
            return false;
        }

        value = 0;
        string binaryStr;

        if(isBinaryValue) {
            int j=0;
            for(int i=mystr.size()-1; i >= 0; i--,j++)
                value += ((mystr[j] == '1') ? 1UL : 0UL) << i; // 'x' is treated as 0 for value
            binaryStr = mystr;
        }
        else if(isHexValue) {
            for(unsigned int i=0; i < mystr.size(); i++) {
                binaryStr += hexToBinaryMap[mystr[i]];
            }
        }
        else if(isOctalValue) {
            for(unsigned int i=0; i < mystr.size(); i++)
                binaryStr += octToBinaryMap[mystr[i]];
        }
        else if(isDecimalValue) {
            stringstream sstr(mystr);
            sstr >> value;
            if(value == 0)
                binaryStr = "0";
            else {
                for(int i = numeric_limits<unsigned long long int>::digits - 1; i >= 0; i--) {
                    if(value & (1 << i))
                        binaryStr += "1";
                    else
                        binaryStr += "0";
                }
            }
        }
        else
            result = false;

		// Truncate extra bits
        if( maxSize > 0 && binaryStr.size() > maxSize) {
            reverse(binaryStr.begin(), binaryStr.end());
            binaryStr.resize(maxSize);
            reverse(binaryStr.begin(), binaryStr.end());
		}
        if(maxSize > 0 && binaryStr.size() < maxSize) {
            while(binaryStr.size() < maxSize)
                binaryStr = "0" + binaryStr;
        }

        //cout << __func__ << " : Input \"" << str << "\" => Value " << value << " => BinaryString " << binaryStr << endl;

        // Convert to binary vector
        for(int i=binaryStr.size()-1; i >= 0; i--) {
            boost::logic::tribool bit = indeterminate;
            if(binaryStr[i] == '1')
                bit = true;
            else if(binaryStr[i] == '0')
                bit = false;
            binaryVec.push_back( bit);
        }

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



string concOrPad(string org, unsigned int max, int align , string c ) {
    bool center = 0;
    if(org.size() > max) {
        org.erase(max, org.size());
    }
    else if(org.size() < max) {
        while(org.size() < max) {
            if(align == 1) // RHS
                org = c + org;
            else if (align == 2) { // CENTER
                if(center) { // RHS
                    org = c + org;
                    center = 0;
                }
                else { // LHS
                    org += c;
                    center = 1;
                }
            }
            else // LHS
                org += c;
        }
    }
    return org;
}


}

