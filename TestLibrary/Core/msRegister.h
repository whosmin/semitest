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

#ifndef __TESTLIB_MSREGISTER_H__
#define __TESTLIB_MSREGISTER_H__

#include "register.h"
#include "msvar.h"

namespace TestLib {

    ///
    /// \brief MultiSite Register class
    ///
    /// * Any LValue operations such as assignment should be operated on all sites
    /// * Any RValue operations such as indexing should return an MSArray result
    ///   or reference instead of a single result value that RegisterMap returns
    ///
    template <unsigned int size>
    class MSRegister : public array1d<Register, size>
    {
    public:
        MSRegister()
        {
            array1d<Register, size>::assign(Register());
        }
        MSRegister(const Register& reg)
        {
            array1d<Register, size>::assign(reg);
        }
#if 0
		RegisterMap& operator[] (const string &regName) {
        }
		RegisterMap& operator[] (std::size_t index) {
            return array1d<RegisterMap, size>::elems[index];
        }
#endif
    };

}

#endif

