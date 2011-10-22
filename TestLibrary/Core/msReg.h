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
 * msReg.h
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */


#ifndef __TESTLIB_MSREG_H__
#define __TESTLIB_MSREG_H__

#include <string>
#include <vector>
#include <map>
#include <boost/logic/tribool.hpp>
#include <iostream>
#include <cassert>

#include "reference.h"
#include "register.h"
#include "msvar.h"
//#include "/home/tjog/library/cpp/bit.h"

using namespace std;
using namespace boost::logic;

// TODO: Change all index variables to size_t type

namespace TestLib {


	//
    // \brief Data structure to represent internal data behind every bit
    //
#if 0
    struct MSBitInfo {
        string     name;            ///< the name of the bit
        tribool state;           ///< Stores the current binary state of this bit
        tribool resetState;      ///< Stores the state to go to upon reset
        tribool defaultState;    ///< Stores the default state (Is this useful?)
        MSBitInfo() {
            state = resetState = defaultState = indeterminate;
            //Bit unknown;
            //state = unknown;
            //resetState = unknown;
            //defaultState = unknown;
        }
        MSBitInfo(tribool value) {
            state = value;
            resetState = value;
            defaultState = value;
            name = "";
        }
		MSBitInfo& operator=(tribool rhs) {
			state = rhs;
			return *this;
		}
    };
#endif
	typedef MSVar<BitInfo> MSBitInfo;

    //
    // \brief Encapsulates a single MSReg worth of data
    //
    //      All access and modifier member functions are indexed in a linear fashion
    //
    //  Here is the usage scenario
    //  MSReg reg0( 8, "mem0", 0x00);
    //  reg0.setDefault("1111 xx00");
    //
    // * Array index should get the base type that is a value_type
    // * get(string name) should get the integer_type
    //
	class MSReg : public TestLib::AbstractRegisterInterface
    {

    public:
        typedef tribool            value_type;
        //typedef Bit              value_type;
        typedef value_type&        reference;
        typedef const value_type&  const_reference;
        typedef value_type*        iterator;
        typedef const value_type*  const_iterator;
        typedef unsigned long long integer_type;

        friend class MSRegBank;
        friend class MSRegMap;
        friend class ValueReference<MSReg, value_type>;
        friend ostream& operator<<(ostream& os, MSReg& reg);
        friend class SliceReference<MSReg, MSReg::value_type>;
		//friend class ContainerReference<MSRegMap, MSRegMap::value_type>;

    public:
        enum Base { decimal, binary, hex, octal};



        MSReg( size_type size=0, string regName="", unsigned int add = 0x00, string defaultValue = "");
        MSReg( size_type size, string regName,    unsigned int add,        integer_type defaultValue);
        MSReg( size_type size, string regName, string add, string defaultValue = "");
        MSReg( const MSReg& reg); ///< \brief Copy constructor

        //
        // \brief Set the default state for all bits of a MSReg.
        // \input value String representing the default state of the MSReg, left (msb) extended with "x" to fill MSReg
        //
        virtual bool       setDefault  ( const string& value);
        virtual bool       setState    ( const string& bitStr);
        virtual bool       setState    ( const integer_type& value);

        // Convenience function for MSRegs with bits <= 64, should not work for larger sizes
        //virtual bool       set (unsigned long value, size_type size);
                           
        virtual bool       setBitName         ( size_type index, string name);
        virtual bool       setBitValues       ( size_type index, value_type value, value_type resetValue, value_type defaultValue);
        virtual bool       setBitValues       ( const string& name, value_type value, value_type resetValue, value_type defaultValue);
        virtual bool       setBitState        ( size_type index, value_type value);
        virtual bool       setBitResetState   ( size_type index, value_type resetValue);
        virtual bool       setBitDefaultState ( size_type index, value_type defaultValue);

		virtual bool       set                ( const string& name, integer_type value);

        virtual string          getBitName       ( size_type index);
#if 0
        virtual string          getDefaultState  (void);
        virtual string          getState         (void);
        virtual integer_type    getStateInteger  (void);
        virtual integer_type    get              (void);
        virtual integer_type    get              (string name);
        //template<class ReturnType> ReturnType  get (string name); 
#endif

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

#if 0
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
#endif
        //
        //  Utility member functions
        //

        MSReg& flip  ( void); ///< \brief Flip bits
#if 0
        size_t    count ( void); ///< \brief Count bits set to '1'
        bool      any   ( void); ///< \brief Test if any bit is set to '1'
        bool      none  ( void); ///< \brief Test if no bit is set to '1'
#endif
        //
        // Operator Overloads
        //

        //friend ostream& operator<<(ostream& os, MSReg& reg);
        //value_type operator[](const unsigned int index);
        MSBitInfo operator[](size_type index) const;
        ValueReference<MSReg, value_type> operator[](size_type index);
        //tribool& operator[](size_type index);

        //value_type& operator[](const string& name);
		SliceReference<MSReg, value_type> operator[](const string& name);
        //value_type operator[](const string& name) const;
		MSBitInfo operator[](const string& name) const;

        MSReg&             operator=(const MSReg& reg);
        const string&         operator=(const string& str);
        const integer_type&   operator=(const integer_type& val);

		//operator bool() 		{			return true;		}

        static MSReg createMSRegHelper( string str);

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
        vector<MSBitInfo> bits;

        map<string, size_type>                                     bitNameToIndex;
        map< string, SliceReference<MSReg, MSReg::value_type> > nameToSlice;

    };


    } // end namespace TestLib

#endif


