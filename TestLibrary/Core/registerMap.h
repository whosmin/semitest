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

/*
 * registerMap.h
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */


#ifndef __TESTLIB_REGISTERMAP_H__
#define __TESTLIB_REGISTERMAP_H__

#include <string>
#include <vector>
#include <map>
#include <boost/logic/tribool.hpp>
#include <iostream>
#include <cassert>

#include "register.h"

namespace TestLib {

    class RegisterSlice {
        public:
            typedef unsigned long long integer_type;

            RegisterSlice() {}

            void addBit( Register& reg, Register::size_type index) {
                ValueReference<Register, Register::value_type> vref( reg, index);
                bits.push_back(vref);
            }
            void addBit( Register* pReg, Register::size_type index) {
                ValueReference<Register, Register::value_type> vref( pReg, index);
                bits.push_back(vref);
            }
            void clear() { bits.clear(); }

            integer_type get() {
                integer_type value = 0;
                for(unsigned int i=0; i < bits.size(); i++) {
                    integer_type bitValue = bits[i].get() == true ? 1 : 0;
                    value += bitValue << i;
                }
                
                return value;
            }

            friend class RegisterMap;

        protected:
            vector< ValueReference<Register, Register::value_type> > bits;
    };


	//
	// \brief Encapsulates an entire Register Mapping worth of data
	//
    // * Array index should get the base type that is a register
    // * get(string name) should get the integer_type
    //
	class RegisterMap : public AbstractRegisterInterface
	{
	public:
        typedef Register     value_type;
        typedef Register&    reference;
        typedef vector< pair< size_type, Register::size_type > > KeywordVec;
        typedef unsigned long long integer_type;

    public:
		RegisterMap(const string _name="");
        /// Copy Constructor
        RegisterMap( const RegisterMap& regMap);

    /////////////////////////////////////////////////////////////////////////////////
    //
    // These member functions are so that we conform to AbstractRegisterInterface
    //
    /////////////////////////////////////////////////////////////////////////////////
		virtual size_type getSize(void)
		{
			return regs.size();
		}
		virtual void print         ( ostream& os, string prefix="");
		virtual void printDetailed ( ostream& os, string prefix="");

    /////////////////////////////////////////////////////////////////////////////////
    //
    // These two member functions are so that we can use the Reference template class
    //
    /////////////////////////////////////////////////////////////////////////////////
		value_type get(size_type index)
		{
			assert(index < getSize());
			return regs[index];
		}
		void    set(size_type index, value_type value)
		{
			assert(index < getSize());
			regs[index] = value;
		}
    /////////////////////////////////////////////////////////////////////////////////


		// \brief Add a register to the register map
		// \parm[in] reg The register to be added
		// \parm[in] index The index to which to add.
		// 			 If this value is < 0 then the register will be appended to the RegisterMap,
		//           otherwise the Register at index will be replaced.
		virtual bool      addRegister(const value_type& reg);
        //virtual bool      addKeyword( const string& keyword, KeywordVec& vec);
        virtual bool setName( string name, vector< pair<string, value_type::size_type> >& values);

		virtual value_type& getRegister(size_type index);
		virtual value_type& getRegister(const string regName);

		// see http://www.parashift.com/c++-faq-lite/const-correctness.html
		value_type operator[] ( size_type index) const;
		value_type& operator[] ( size_type index);
		//ContainerReference<RegisterMap, Register> operator[]( size_type index);
		value_type& operator[] (const string &regName);

        integer_type get(string name);

        friend ostream& operator<<(ostream& os, RegisterMap& reg);

    protected:
        bool nameExists(string name);


	protected:
		string                 name;
		vector<value_type>       regs;
		map<string, size_type>   regNameToIndex; // In order to index via register name
        //map<string, KeywordVec > keywordToIndices;
        map<string, RegisterSlice> nameToSlice;
	};


}



#endif

