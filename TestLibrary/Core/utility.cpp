
#include "utility.h"

namespace TestLib {

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
