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
//

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

    template <class T>  std::string toString(const T& value);

	bool                stringToBool(const std::string& str,
                            std::vector<boost::logic::tribool> binaryVec, const unsigned int maxSize = 0);
    void                remove_substr( std::string &str, std::string unwanted);
}

#endif
