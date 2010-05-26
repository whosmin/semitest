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

#ifndef __TESTLIB_MSREGISTERMAP_H__
#define __TESTLIB_MSREGISTERMAP_H__

#include "registerMap.h"
#include "msvar.h"

namespace TestLib {

    ///
    /// \brief MultiSite RegisterMap class
    ///
    /// * Any LValue operations such as assignment should be operated on all sites
    /// * Any RValue operations such as indexing should return an MSArray result
    ///   or reference instead of a single result value that RegisterMap returns
    ///
    template <unsigned int size>
    class MSRegisterMap : public array1d<RegisterMap, size>
    {
    public:
        MSRegisterMap()
        {
            array1d<RegisterMap, size>::assign(RegisterMap());
        }
        MSRegisterMap(const RegisterMap& map)
        {
            array1d<RegisterMap, size>::assign(map);
        }
		RegisterMap& operator[] (const string &regName) {
        }
		RegisterMap& operator[] (std::size_t index) {
            return array1d<RegisterMap, size>::elems[index];
        }
    };

}

#endif

