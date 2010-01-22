
#ifndef __CORE_UTILITY_H__
#define __CORE_UTILITY_H__

#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <boost/logic/tribool.hpp>

namespace TestLib {

        std::string         trim( std::string& s, const std::string& drop = " ");
        std::string         trim( const std::string& str, const std::string& drop = " ");

        bool                stringToBool(const std::string& str);
        double              stringToDouble(const std::string& str);

        template < class T > std::string toString(const T& value);

	std::vector<boost::logic::tribool> stringToBool(const std::string& str, const unsigned int maxSize = 0);

}

#endif
