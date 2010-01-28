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
#include <vector>

namespace TestLib {

   inline string triboolToString(boost::logic::tribool tri) {
       string result = "x";
       if(tri == true)
           result = "1";
       if(tri == false)
           result = "0";

        return result;
    }

	AbstractRegisterInterface::AbstractRegisterInterface() {

	}

	Register::Register( size_type size, string regName, int add, string defaultValue)
		: address(add), name(regName)
	{
		printBase = decimal;
		resize(size);

       while(defaultValue.size() < size)
           defaultValue = "x" + defaultValue;
       setDefault(defaultValue);
       setState(defaultValue);

	}

	bool Register::resize(size_type size, value_type value) {
		bits.resize(size, BitInfo(value));
		return true;
	}

	bool Register::setDefault(const string& value) {
		if(getSize() == 0)
			return false;

        vector<value_type> bitVec;
        stringToBool( value, bitVec, getSize());

        for(unsigned int i=0; i < getSize(); i++)
            bits[i].defaultState = bitVec[i];

		return true;
	}

    bool Register::setState(const string& bitStr) {
        if(getSize() == 0)
            return false;

        vector<value_type> bitVec;
        stringToBool( bitStr, bitVec, getSize());

        for(unsigned int i=0; i < getSize(); i++)
            bits[i].state = bitVec[i];

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

    string Register::getDefaultState() {
        string defStr;
        for(unsigned int i=0; i < getSize(); i++) {
            defStr = triboolToString(bits[i].defaultState) + defStr;
        }
        return defStr;
    }
    string Register::getState() {
        string str;
        for(unsigned int i=0; i < getSize(); i++) {
            str = triboolToString(bits[i].state) + str;
        }
        return str;
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
   string&   Register::operator=(const string& str) {
       string tempStr(str);

       setState(tempStr);

       return tempStr;
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
        string sep = "\t";
        vector<string> header;
        vector<string> values;

        header.push_back("Name   ");
        header.push_back("Size");
        header.push_back("Address");

        values.push_back(name);
        //values.push_back(TestLib::toString(getSize()));
        //values.push_back(TestLib::toString(address));
        //TestLib::toString(1);

        vector<unsigned int> maxSizes;
        for(unsigned int i=0; i < header.size(); i++) {
            unsigned int maxSize = 0;
            if(header[i].size() > maxSize)
                maxSize = header[i].size();
            if(i < values.size())
                if(values[i].size() > maxSize)
                    maxSize = values[i].size();
            maxSizes.push_back(maxSize);
        }

        //for(unsigned int i=0; i < header.size(); i++) {
         //   os << concOrPad(header[i], maxSizes[i]);
       // }

        os << "Name      " << sep << "Size" << sep << "Address" << sep << "State" << sep << "Default" << endl;
        os << name   << sep << getSize() << sep << address << sep << getState() << sep << getDefaultState() << endl;
	}

    ostream& operator<<(ostream& os, Register& reg) {
        reg.printDetailed(os);
    	return os;
    }



} // end namespace TestLib

