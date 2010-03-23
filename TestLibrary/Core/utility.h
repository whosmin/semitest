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

#ifndef __func__
#define __func__ __FUNCTION__
#endif

namespace TestLib {

    std::string         trim( std::string& s, const std::string& drop = " ");
    std::string         trim( const std::string& str, const std::string& drop = " ");

    double              stringToDouble(const std::string& str);

    template <class T>  std::string toString(const T& value);

	bool                stringToBool(const std::string& str,
                                    std::vector<boost::logic::tribool>& binaryVec,
                                    const unsigned int maxSize,
                                    unsigned long long& value);
    void                remove_substr( std::string &str, std::string unwanted);
    long int stringToLong(const std::string &str, unsigned int base);

    /// \brief Concatenate or Pad string to a particular length
    /// \param[in] max 	 desired Max length of string
    /// \param[in] align Set alignment of string, 0 = Left, 1 = Right, 2 = Center
    /// \param[in] c	 Optional pad char incase string size is less that max
    std::string concOrPad(std::string org, unsigned int max, int align = 0, std::string c = " ");
}

#endif
