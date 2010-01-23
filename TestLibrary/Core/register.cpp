/*
 * register.cpp
 *
 *  Created on: Aug 15, 2009
 *      Author: x0105974
 */

#include "register.h"
#include "utility.h"

#include <algorithm>
#include <cctype>

namespace TestLib {

	AbstractRegisterInterface::AbstractRegisterInterface() {

	}

	Register::Register( size_type size, string regName, int add, string defaultValue)
		: address(add), name(regName)
	{
		printBase = decimal;
		resize(size);
		std::vector<value_type> valueVec = stringToBool(defaultValue, getSize());
		for(size_type i=0; i < valueVec.size(); i++) {
			bits[i].defaultState = valueVec[i];
		}
	}

	bool Register::resize(size_type size, value_type value) {
		bits.resize(size, BitInfo(value));
		return true;
	}

	bool Register::setDefault(const string& value) {
		if(getSize() == 0)
			return false;

		string trimmedValue = trim( value);

		if(trimmedValue.size() > getSize()) {
			reverse(trimmedValue.begin(), trimmedValue.end());
			trimmedValue.resize(getSize());
			reverse(trimmedValue.begin(), trimmedValue.end());
		}

                std::transform(trimmedValue.begin(), trimmedValue.end(), trimmedValue.begin(), ::tolower);

		return true;
	}

	bool Register::setBitName(size_type index, string name) {
		if(index > getSize())
			return false;

		map<string, size_type>::iterator iter = bitNameToIndex.find(name);
		if(iter != bitNameToIndex.end()) {
			cerr << "Bit name " << name << " already exists" << endl;
			return false;
		}

		bitNameToIndex[name] = index;

		bits[index].name = name;
		return true;
	}

	bool Register::setBitValues( size_type index, value_type value, value_type resetValue, value_type defaultValue) {
		if(index > getSize())
			return false;

		bits[index].state = value;
		bits[index].resetState = resetValue;
		bits[index].defaultState = defaultValue;
		return true;
	}

	bool Register::setBitValues( const string name, value_type value, value_type resetValue, value_type defaultValue) {
		//for(unsigned int index=0; index < getSize(); )

		return true;
	}
	bool Register::setBitState( size_type index, value_type value) {
		if(index > getSize())
			return false;
		bits[index].state = value;
		return true;
	}
	bool Register::setBitResetState(size_type index, value_type resetValue) {
		if(index > getSize())
			return false;
		bits[index].resetState = resetValue;
		return true;
	}

	bool Register::setBitDefaultState( size_type index, value_type defaultValue) {
		if(index > getSize())
			return false;
		bits[index].defaultState = defaultValue;
		return true;
	}

	/*
	value_type Register::operator[](const unsigned int index) {
		value_type temp;
		if(index > getSize())
			return temp;
		return state[index];
	}
	*/
	Register::value_type Register::operator[](size_type index) const {
		//assert(index < this->getSize());

		return bits[index].state;
	}

	Register::reference Register::operator[](const string& name) {
		map<string, size_type>::const_iterator iter = bitNameToIndex.find(name);
		assert(iter != bitNameToIndex.end());

		//return bits[bitNameToIndex[name]].state;
		unsigned int bitIndex = bitNameToIndex[name];

		return bits[bitIndex].state;
	}

	/*
	const value_type& Register::operator[](const string& name) const {
		map<string, unsigned int>::const_iterator iter = bitNameToIndex.find(name);
		assert(iter != bitNameToIndex.end());

		unsigned int bitIndex = bitNameToIndex[name];

		return bits[bitIndex].state;
	}
	*/

	void Register::clear(void) {
		for(size_type index=0; index < getSize(); index++)
			bits[index].name = "";
		clearState();
	}

	void Register::clearState(void) {
		for(size_type index = 0; index < getSize(); index++) {
			bits[index].state = indeterminate;
			bits[index].resetState = indeterminate;
			bits[index].defaultState = indeterminate;
		}
	}

	bool Register::set( unsigned long value, size_type size) {
		return true;
	}

	Reference<Register> Register::operator[](size_type index) {
		assert(index < getSize());

		return Reference<Register>( *this, index);
	}

	Register& Register::operator=(const Register& reg) {

		if(this != &reg) {
			// Do copy here
			printBase = reg.printBase;
			address   = reg.address;
			name      = reg.name;
			bits      = reg.bits;
		}

		return *this;
	}

	void Register::print(ostream& os) {
		string sep = "\t";
		//ios::fmtflags flags = os.flags();

		os << "Register " << name << sep << getSize() << sep << address << sep;

		if(printBase != binary) {
			unsigned long int valueHolder = 0;
			for(int i=getSize()-1; i>=0; i--)
				valueHolder = valueHolder + ((bits[i].state == 1 ? 1 : 0) <<i);
			os << valueHolder;
		}
		else {
			// binary
			for(int i=getSize()-1; i >= 0; i--)
				os << bits[i].state;
		}

		os << endl;
	}



	void Register::printDetailed(ostream& os) {
		print(os);
	}

    ostream& operator<<(ostream& os, Register& reg) {
    	reg.print(os);
    	return os;
    }



} // end namespace TestLib

