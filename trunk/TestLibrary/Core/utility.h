
#ifndef __CORE_UTILITY_H__
#define __CORE_UTILITY_H__

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <boost/logic/tribool.hpp>

namespace TestLib {

	std::string trim( std::string& s, const std::string& drop = " ")
	{
		std::string r=s.erase(s.find_last_not_of(drop)+1);
		return r.erase(0,r.find_first_not_of(drop));
	}

	std::string trim( const std::string& str, const std::string& drop = " ") 
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

	std::vector<boost::logic::tribool> stringToBool(const std::string& str, const unsigned int maxSize = 0);

}

#endif
