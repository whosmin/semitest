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
    template <std::size_t size>
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
            virtual void print( ostream& os, string prefix="") {
                for(std::size_t i = 0; i < array1d<Register, size>::size(); i++)
                    (*this)[i].print( os, prefix);
            }
            virtual void printDetailed( ostream& os, string prefix="") {
                for(std::size_t i = 0; i < array1d<Register, size>::size(); i++)
                    (*this)[i].printDetailed( os, prefix);
            }
            virtual bool       setState    ( const Register::integer_type& value) {
                bool result = true;

                for(std::size_t i = 0; i < array1d<Register, size>::size(); i++)
                    result &= (*this)[i].setState( value);

                return result;
            }
            virtual bool       setState    ( const string& bitStr) {
                bool result = true;

                for(std::size_t i = 0; i < array1d<Register, size>::size(); i++)
                    result &= (*this)[i].setState( bitStr);

                return result;
            }
            virtual bool       setDefault  ( const string& value) {
                bool result = true;

                for(std::size_t i = 0; i < array1d<Register, size>::size(); i++)
                    result &= (*this)[i].setDefault( value);

                return result;
            }
            virtual array1d<Register::integer_type, size>    get              (void)  {
                array1d<Register::integer_type, size> result;
                for(unsigned int i=0; i < size; i++)
                    result[i] = (*this)[i].get();

                return result;
            }

            virtual array1d<Register::integer_type, size> get              (string name)  {
                array1d<Register::integer_type, size> result;
                for(unsigned int i=0; i < size; i++)
                    result[i] = (*this)[i].get(name);

                return result;
            }

#if 0
            virtual bool set (unsigned long value, unsigned int numBits) {
                bool result = false;
                for(std::size_t i = 0; i < array1d<Register, size>::size(); i++)
                    (*this)[i].set( value, numBits);

                return result;
            }
#endif
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

