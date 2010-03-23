//
// This file is part of SemiTest
//
// Copyright (c) 2009 - 2010 Tushar Jog
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

#ifndef __LUT_H__
#define __LUT_H__

#include <map>
#include <string>
#include <iostream>

// \brief Look Up Table
//
// A look up table templated class which is derived from std::map but differs in the following ways
// * read member function is implemented to fill the map from a file
// * write member function is implemented to store contents to a file
// * [] operator is redifined to error out when a key that does not already exist is given, although insert() member
//    function can always be used to add more elements
//
template<typename KeyType, typename ValueType>
    class Lut : public std::map<KeyType, ValueType> {
    public:
        //Lut();
        bool read  ( std::string fileName, std::string delim);
        bool write ( std::string fileName);
        bool print ( std::ostream& os);

        ValueType& operator[]( const KeyType& key);
    };

#endif


