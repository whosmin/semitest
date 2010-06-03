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

        // Get size in integers
        virtual size_type getSize(void) = 0;
        // Print single line description to output stream
        virtual void print(ostream& os, string prefix="") = 0;
        // Print detailed multi-line description to output stream
        virtual void printDetailed(ostream& os, string prefix="") = 0;

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
        typedef tribool         value_type;
        //typedef Bit             value_type;
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

    public:
        enum Base { decimal, binary, hex, octal};

        //
        // \brief Data structure to represent internal data behind every bit
        //
        struct BitInfo {
            string     name;            ///< the name of the bit
            value_type state;           ///< Stores the current binary state of this bit
            value_type resetState;      ///< Stores the state to go to upon reset
            value_type defaultState;    ///< Stores the default state (Is this useful?)
            BitInfo() {
                //state = resetState = defaultState = indeterminate;
                //Bit unknown;
                //state = unknown;
                //resetState = unknown;
                //defaultState = unknown;
            }
            BitInfo(value_type value) {
                state = value;
                resetState = value;
                defaultState = value;
                name = "";
            }
        };

        Register( unsigned int size=0, string regName="", int add = 0x00, string defaultValue = "");
        Register( unsigned int size, string regName,    int add,        integer_type defaultValue);
        Register( unsigned int size, string regName, string add, string defaultValue = "");
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
                           
        virtual bool       setBitName         ( unsigned int index, string name);
        virtual bool       setBitValues       ( unsigned int index, value_type value, value_type resetValue, value_type defaultValue);
        virtual bool       setBitValues       ( const string& name, value_type value, value_type resetValue, value_type defaultValue);
                           
        virtual bool       setBitState        ( unsigned int index, value_type value);
        virtual bool       setBitResetState   ( unsigned int index, value_type resetValue);
        virtual bool       setBitDefaultState ( unsigned int index, value_type defaultValue);

        virtual string     getBitName         ( unsigned int index);

        virtual string          getDefaultState  (void);
        virtual string          getState         (void);
        virtual integer_type    getStateInteger  (void);
        virtual integer_type    get              (void);

        //template<class ReturnType> ReturnType  get (string name); 

        virtual integer_type    get(string name);


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
    /**/     value_type get(unsigned int index)
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
    /**/     void    set(unsigned int index, value_type value)
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
        value_type operator[](unsigned int index) const;
        ValueReference<Register, value_type> operator[](unsigned int index);
        //tribool& operator[](size_type index);

        value_type& operator[](const string& name);
        //const value_type& operator[](const string& name) const;

        Register&             operator=(const Register& reg);
        const string&         operator=(const string& str);
        const integer_type&   operator=(const integer_type& val);

    protected:
        bool resize     ( size_type size, value_type value=indeterminate); ///< Resize to new size
        //bool resize     ( size_type size, value_type value=value_type()); ///< Resize to new size
        bool nameExists ( string name);
        bool setAddress( const string& value);

    protected:
        Base            printBase;
        int             address;
        string          name;
        vector<BitInfo> bits;

        map<string, unsigned int>                                     bitNameToIndex;
        map< string, SliceReference<Register, Register::value_type> > nameToSlice;

    };


    } // end namespace TestLib

#endif


