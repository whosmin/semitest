
#include "utility.h"

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
	std::vector<boost::logic::tribool> stringToBool(const std::string& str, const unsigned int maxSize) {
		std::string mystr = trim(str);
		std::vector<boost::logic::tribool> binaryVec;

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

		bool isBoolValue  = false;
		bool isOctalValue = false;
		bool isHexValue   = false;
		bool isInvalidValue = false;
		for(unsigned int i=0; i < mystr.size(); i++) {
			switch(mystr[i]) {
				case '0': 
				case '1': isBoolValue = true; break;
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
			
		

		// Truncate extra bits
		if( maxSize > 0 && mystr.size() > maxSize) {
			reverse(mystr.begin(), mystr.end());
			mystr.resize(maxSize);
			reverse(mystr.begin(), mystr.end());
		}

		// Convert to lower case
		std::transform(mystr.begin(), mystr.end(), mystr.begin(), tolower);

		// Conver to binary


		return binaryVec;
	}

}
