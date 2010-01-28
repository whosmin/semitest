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
		virtual void print(ostream& os) = 0;
		// Print detailed multi-line description to output stream
		virtual void printDetailed(ostream& os) = 0;

	};


	//
	// \brief Encapsulates a single register worth of data
	//
	//		All access and modifier member functions are indexed in a linear fashion
	//
	//	Here is the usage scenario
	//	Register reg0( 8, "mem0", 0x00);
	//  reg0.setDefault("1111 xx00");
	//
	class Register : public AbstractRegisterInterface
	{
        friend class RegisterBank;
        friend class RegisterMap;
	    friend ostream& operator<<(ostream& os, Register& reg);

	public:
		typedef tribool			value_type;
		typedef tribool&		reference;
		typedef const tribool&  const_reference;
		typedef tribool*		iterator;
		typedef const tribool*	const_iterator;

	public:
		enum Base { decimal, binary, hex, octal};

		//
		// \brief Data structure to represent internal data behind every bit
		//
		struct BitInfo {
            string     name;			///< the name of the bit
			value_type state; 			///< Stores the current binary state of this bit
			value_type resetState;		///< Stores the state to go to upon reset
            value_type defaultState;    ///< Stores the default state (Is this useful?)
			BitInfo() {
				state = resetState = defaultState = indeterminate;
			}
			BitInfo(value_type value) {
				state = resetState = defaultState = value;
				name = "";
			}
		};

		Register( unsigned int size, string regName="", int add = 0x00, string defaultValue = "");

		//
		// \brief Set the default state for all bits of a register.
		// \input value String representing the default state of the register, left (msb) extended with "x" to fill register
		//
        virtual bool setDefault  ( const string& value);
        virtual bool setState    ( const string& bitStr);

		// Convenience function for registers with bits <= 64, should not work for larger sizes
		virtual bool set (unsigned long value, size_type size);

		virtual bool setBitName         ( unsigned int index, string name);
        virtual bool setBitValues       ( unsigned int index, value_type value, value_type resetValue, value_type defaultValue);
		virtual bool setBitValues       (const string name, value_type value, value_type resetValue, value_type defaultValue);

		virtual bool setBitState        ( unsigned int index, value_type value);
		virtual bool setBitResetState   ( unsigned int index, value_type resetValue);
		virtual bool setBitDefaultState ( unsigned int index, value_type defaultValue);

        virtual string getDefaultState (void);
        virtual string getState (void);

		/// Clear state only
		virtual void clearState(void);
		/// Clear state and bitNames
		virtual void clear(void);

		virtual size_type  getSize        (void)
		{
			return bits.size();
		}

		virtual void setPrintBase   ( Base newbase)
		{
			printBase = newbase;
		}
		virtual void print          ( ostream& os);
		virtual void printDetailed  ( ostream& os);

		//
		// These two member functions are so that we can use the Reference template class
		//
		value_type get(unsigned int index)
		{
			assert(index < getSize());
			return bits[index].state;
		}
		void    set(unsigned int index, bool value)
		{
			assert(index < getSize());
			bits[index].state = value;
		}

		//friend ostream& operator<<(ostream& os, Register& reg);
		//value_type operator[](const unsigned int index);
		value_type operator[](unsigned int index) const;
		Reference<Register> operator[](unsigned int index);

		value_type& operator[](const string& name);
		//const value_type& operator[](const string& name) const;

		Register& operator=(const Register& reg);
        string&   operator=(const string& str);

	protected:
		bool resize(size_type size, value_type value=indeterminate); ///< Resize to new size

	protected:
		Base printBase;

		int address;
		string name;

		vector<BitInfo> bits;

		map<string, unsigned int> bitNameToIndex;

	};



	} // end namespace TestLib

#endif


