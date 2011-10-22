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
/*
 * register.h
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */


#ifndef __TESTLIB_REGISTER_H__
#define __TESTLIB_REGISTER_H__

#include <string>
#include <vector>
#include <map>
#include <boost/logic/tribool.hpp>
#include <iostream>
#include <cassert>

#include "reference.h"
//#include "/home/tjog/library/cpp/bit.h"

using namespace std;
using namespace boost::logic;

// TODO: Change all index variables to size_t type

namespace TestLib {


    class AbstractRegisterInterface
    {
    public:
        AbstractRegisterInterface();
        typedef std::size_t size_type;

        virtual size_type getSize(void) = 0; // Get size in integers
        virtual void      print(ostream& os, string prefix="") = 0; // Print single line description to output stream
        virtual void      printDetailed(ostream& os, string prefix="") = 0; // Print detailed multi-line description to output stream

    };

	//
    // \brief Data structure to represent internal data behind every bit
    //
    struct BitInfo {
        string     name;            ///< the name of the bit
        tribool state;           ///< Stores the current binary state of this bit
        tribool resetState;      ///< Stores the state to go to upon reset
        tribool defaultState;    ///< Stores the default state (Is this useful?)
        BitInfo(const string& bitName = "") {
            state = resetState = defaultState = indeterminate;
			name = bitName;
            //Bit unknown;
            //state = unknown;
            //resetState = unknown;
            //defaultState = unknown;
        }
        BitInfo(tribool value) {
            state			= value;
            resetState		= value;
            defaultState	= value;
            name			= "";
        }
		BitInfo(tribool value, tribool rValue, tribool dValue) {
            state			= value;
            resetState		= rValue;
            defaultState	= dValue;
            name			= "";
        }
		BitInfo& operator=(tribool rhs) {
			state = rhs;
			return *this;
		}

    };


    //
    // \brief Encapsulates a single register worth of data
    //
    //      All access and modifier member functions are indexed in a linear fashion
    //
    //  Here is the usage scenario
    //  Register reg0( 8, "mem0", 0x00);
    //  reg0.setDefault("1111 xx00");
    //
    // * Array index should get the base type that is a value_type
    // * get(string name) should get the integer_type
    //
    class Register : public AbstractRegisterInterface
    {

    public:
        typedef tribool            value_type;
        //typedef Bit              value_type;
        typedef value_type&        reference;
        typedef const value_type&  const_reference;
        typedef value_type*        iterator;
        typedef const value_type*  const_iterator;
        typedef unsigned long long integer_type;

        friend class RegisterBank;
        friend class RegisterMap;
        friend class ValueReference<Register, value_type>;
        friend ostream& operator<<(ostream& os, Register& reg);
        friend class SliceReference<Register, Register::value_type>;
		//friend class ContainerReference<RegisterMap, RegisterMap::value_type>;

    public:
        enum Base { decimal, binary, hex, octal};



        Register( size_type size=0, string regName="", unsigned int add = 0x00, string defaultValue = "");
        Register( size_type size, string regName,    unsigned int add,        integer_type defaultValue);
        Register( size_type size, string regName, string add, string defaultValue = "");
        Register( const Register& reg); ///< \brief Copy constructor

        //
        // \brief Set the default state for all bits of a register.
        // \input value String representing the default state of the register, left (msb) extended with "x" to fill register
        //
        virtual bool       setDefault  ( const string& value);
        virtual bool       setState    ( const string& bitStr);
        virtual bool       setState    ( const integer_type& value);

        // Convenience function for registers with bits <= 64, should not work for larger sizes
        //virtual bool       set (unsigned long value, size_type size);
                           
        virtual bool       setBitName         ( size_type index, string name);
        virtual bool       setBitValues       ( size_type index, value_type value, value_type resetValue, value_type defaultValue);
        virtual bool       setBitValues       ( const string& name, value_type value, value_type resetValue, value_type defaultValue);
        virtual bool       setBitState        ( size_type index, value_type value);
        virtual bool       setBitResetState   ( size_type index, value_type resetValue);
        virtual bool       setBitDefaultState ( size_type index, value_type defaultValue);

		virtual bool       set                ( const string& name, integer_type value);

        virtual string          getBitName       ( size_type index);
        virtual string          getDefaultState  (void);
        virtual string          getState         (void);
        virtual integer_type    getStateInteger  (void);
        virtual integer_type    get              (void);
        virtual integer_type    get              (string name);
        //template<class ReturnType> ReturnType  get (string name); 


        //
        // Cannot have a "value_type get(string name)" function if value_type is boost::logic::tribool
        // as boost::logic::tribool can be converted to a integer type automatically and the compiler
        // gets confused
        //
        // virtual value_type      get(string name);

        virtual void       clearState         (void); ///< Clear state only
        virtual void       clear              (void); ///< Clear state and bitNames

        virtual size_type  getSize            (void) { return bits.size(); }
        virtual size_type  size               (void) { return bits.size(); }
                                              
        virtual void       setPrintBase       ( Base newbase) { printBase = newbase; }
        virtual void       print              ( ostream& os, string prefix="");
        virtual void       printDetailed      ( ostream& os, string prefix="");

        //
        // Advanced
        //
        virtual bool setName( const string& name, vector<size_type> indices);

    /////////////////////////////////////////////////////////////////////////////////
    //
    // These two member functions are so that we can use the Reference template class
    //
    /////////////////////////////////////////////////////////////////////////////////
    /**/     value_type get(size_type index)
    /**/     {
    /**/         if(index >= getSize()) {
                     std::cerr << "Index : " << index << " getSize() : " << getSize() << endl;
                     std::cout << "Index : " << index << " getSize() : " << getSize() << endl;
                     //assert(index < getSize());
                     return false;
                 }
                 else
        /**/         return bits[index].state;
    /**/     }
    /**/     //void    set(unsigned int index, value_type value)
    /**/     void    set(size_type index, value_type value)
    /**/     {
    /**/         assert(index < getSize());
    /**/         bits[index].state = value;
    /**/     }
    /////////////////////////////////////////////////////////////////////////////////
    //

        //
        //  Utility member functions
        //

        Register& flip  ( void); ///< \brief Flip bits
        size_t    count ( void); ///< \brief Count bits set to '1'
        bool      any   ( void); ///< \brief Test if any bit is set to '1'
        bool      none  ( void); ///< \brief Test if no bit is set to '1'

        //
        // Operator Overloads
        //

        //friend ostream& operator<<(ostream& os, Register& reg);
        //value_type operator[](const unsigned int index);
        value_type operator[](size_type index) const;
        ValueReference<Register, value_type> operator[](size_type index);
        //tribool& operator[](size_type index);

        //value_type& operator[](const string& name);
		SliceReference<Register, value_type> operator[](const string& name);
        value_type operator[](const string& name) const;

        Register&             operator=(const Register& reg);
        const string&         operator=(const string& str);
        const integer_type&   operator=(const integer_type& val);

		//operator bool() 		{			return true;		}

        static Register createRegisterHelper( string str);

    protected:
        bool resize     ( size_type size, value_type value=indeterminate); ///< Resize to new size
        //bool resize     ( size_type size, value_type value=value_type()); ///< Resize to new size
        bool nameExists ( string name);
        bool setAddress( const string& value);
		bool setAddress( unsigned int value);

    protected:
        Base            printBase;
        unsigned int    address, altAddress;
        string          name;
        vector<BitInfo> bits;

        map<string, size_type>                                     bitNameToIndex;
        map< string, SliceReference<Register, Register::value_type> > nameToSlice;

    };


    } // end namespace TestLib

#endif


