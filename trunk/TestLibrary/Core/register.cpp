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
#include <limits>

namespace TestLib {
//ostream& operator<<(ostream& os, Bit& bit) {
//    return os;
//}

   template<class BitType>
   string bitToString(BitType tri) {
       string result = "x";
       if(tri == true)
           result = "1";
       if(tri == false)
           result = "0";

       //cout << tri << "\t" << result << endl;

        return result;
    }
#if 0
   inline string bitToString(boost::logic::tribool tri) {
       string result = "x";
       if(tri == true)
           result = "1";
       if(tri == false)
           result = "0";

        return result;
    }
#endif

	AbstractRegisterInterface::AbstractRegisterInterface() {

	}

	Register::Register( size_type size, string regName, int add, string defaultValue)
		: address(add), name(regName)
	{
		printBase = decimal;
        // This resize operation will already set the bits to indeterminate state
		resize(size);

       //while(defaultValue.size() < size)
       //    defaultValue = "x" + defaultValue;
       if(defaultValue.size() > 0)
           setDefault(defaultValue);

       for(unsigned int i=0; i < getSize(); i++)
           bits[i].state = bits[i].defaultState;

	}

    Register::Register( unsigned int size, string regName, int add, integer_type defaultValue)
        : address(add), name(regName)
    {
        printBase = decimal;
        resize(size);

        setState(defaultValue);
        for(unsigned int i=0; i < getSize(); i++)
            bits[i].defaultState = bits[i].state;
    }
    Register::Register( unsigned int size, string regName, string add, string defaultValue)
        : name(regName)
    {
        printBase = decimal;
        resize(size);

        if(add.size() > 0)
            setAddress( add);

        if(defaultValue.size() > 0) {
            setState( defaultValue);
            for(unsigned int i=0; i < getSize(); i++)
                bits[i].defaultState = bits[i].state;
        }
    }

    Register::Register( const Register& reg) {
        printBase      = reg.printBase;
        address        = reg.address;
        name           = reg.name;
        bits           = reg.bits;
        bitNameToIndex = reg.bitNameToIndex;
        nameToSlice    = reg.nameToSlice;
    }

	bool Register::resize(size_type size, value_type value) {
		bits.resize(size, BitInfo(value));
		return true;
	}

	bool Register::setDefault(const string& value) {
		if(getSize() == 0)
			return false;

        vector<value_type> bitVec;
        integer_type decValue = 0;
        stringToBool<value_type>( value, bitVec, getSize(), decValue);

        for(unsigned int i=0; i < getSize(); i++)
            bits[i].defaultState = bitVec[i];

		return true;
	}

	bool Register::setAddress(const string& value) {
		if(getSize() == 0)
			return false;

        vector<value_type> bitVec;
        integer_type decValue = 0;
        stringToBool<value_type>( value, bitVec, getSize(), decValue);

        address = decValue;

		return true;
	}

    bool Register::setState(const string& bitStr) {
        if(getSize() == 0)
            return false;

        vector<value_type> bitVec;
        integer_type value = 0;
        stringToBool<value_type>( bitStr, bitVec, getSize(), value);

        for(unsigned int i=0; i < getSize(); i++)
            bits[i].state = bitVec[i];

        return true;
    }
    bool Register::setState( const integer_type& value) {
        if(getSize() == 0) return false;

        int maxSize = std::min( (int) getSize(), numeric_limits<integer_type>::digits);
        for(int i = 0; (i < maxSize); i++) {
            if((value >> i) % 2)
                bits[i].state = true;
           else
                bits[i].state = false;
        }

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

	string Register::getBitName(size_type index) {
        string name;
		assert(index < getSize());
		if(index > getSize())
			return name;

        return bits[index].name;
    }

	bool Register::setBitValues( size_type index, value_type value, value_type resetValue, value_type defaultValue) {
		if(index > getSize())
			return false;

		bits[index].state = value;
		bits[index].resetState = resetValue;
		bits[index].defaultState = defaultValue;
		return true;
	}

	bool Register::setBitValues( const string& name, value_type value, value_type resetValue, value_type defaultValue) {
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
            defStr = bitToString<value_type>(bits[i].defaultState) + defStr;
        }
        return defStr;
    }
    string Register::getState() {
        string str;
        for(unsigned int i=0; i < getSize(); i++) {
            str = bitToString<value_type>(bits[i].state) + str;
        }
        return str;
    }
    Register::integer_type Register::getStateInteger() {
        integer_type value = 0;
        for(unsigned int i=0; i < getSize(); i++) {
            integer_type bitValue = bits[i].state == true ? 1 : 0;
            value += bitValue << i;
        }

        return value;
    }

    Register::integer_type Register::get(void) {
        return getStateInteger();
    }

    Register::integer_type Register::get(string name) {
        integer_type value = 0;

        if(nameToSlice.find(name) != nameToSlice.end()) {
            SliceReference<Register, Register::value_type> slice = nameToSlice[name];
            unsigned int sliceSize = slice.size();
#if 0
            for(unsigned int i=0; i < slice.size(); i++) {
                integer_type bitValue = 0;
                cout << __PRETTY_FUNCTION__ << " " << "slice.get(" << i << endl;
                Register::value_type vt = slice.get(i);
                bitValue = (vt == true ? 1 : 0);
                value += bitValue << i;
            }
#endif
            vector<Register::size_type> indices = slice.getIndices();
            for(unsigned int i=0; i < indices.size(); i++) {
                integer_type bitValue = bits[i].state == true ? 1 : 0;
                value += bitValue << i;
            }
        }
        else if(bitNameToIndex.find(name) != bitNameToIndex.end()) {
            integer_type bitValue = bitNameToIndex[name] == true ? 1 : 0;
        }

        return value;
    }

#if 0
    Register::value_type Register::get(string name) {
        value_type value;

        return value;
    }
#endif

    //template<class ReturnType> ReturnType  Register::get (string name) {
    //}

    Register& Register::flip(void) {
        for(unsigned int i=0; i < getSize(); i++) {
            bits[i].state = !bits[i].state;
        }

        return *this;
    }

    size_t Register::count(void) {
        size_t num = 0;

        for(unsigned int i=0; i < getSize(); i++)
            if(bits[i].state == true)
                num++;

        return num;
    }

    bool Register::any(void) {
        bool result = false;

        for(unsigned int i=0; i < getSize(); i++)
            if(bits[i].state == true)
                result = true;

        return result;
    }

    bool Register::none(void) {
        bool result = true;

        for(unsigned int i=0; i < getSize(); i++)
            if(bits[i].state == true)
                result = false;

        return result;
    }

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

//    unsigned long long Register::operator[](const string& name) {
//        unsigned long long value = 0;
//
//        return value;
//    }

	/*
	const value_type& Register::operator[](const string& name) const {
		map<string, unsigned int>::const_iterator iter = bitNameToIndex.find(name);
		assert(iter != bitNameToIndex.end());

		unsigned int bitIndex = bitNameToIndex[name];

		return bits[bitIndex].state;
	}
	*/


	ValueReference<Register, Register::value_type> Register::operator[](size_type index) {
		assert(index < getSize());

		return ValueReference<Register, Register::value_type>( *this, index);
	}

    /*
    tribool& Register::operator[](size_type index) {
        return bits[index].state;
    }
    */

	Register& Register::operator=(const Register& reg) {

		if(this != &reg) {
			// Do copy here
			printBase          = reg.printBase;
			address            = reg.address;
			name               = reg.name;
			bits               = reg.bits;
			bitNameToIndex     = reg.bitNameToIndex;
			nameToSlice = reg.nameToSlice;
		}

		return *this;
	}
   const string&   Register::operator=(const string& str) {
       setState(str);
       return str;
   }

   const Register::integer_type&   Register::operator=(const integer_type& val) {
       setState(val);
       return val;
   }
    bool Register::nameExists(string name) {
        bool exists = false;

        if(nameToSlice.find(name) != nameToSlice.end())
            exists = true;

        if(bitNameToIndex.find(name) != bitNameToIndex.end())
            exists = true;

        return exists;
    }

    bool Register::setName( const string& name, vector<size_type> indices) {
        bool result = true;

        for(unsigned int i=0; i < indices.size(); i++) {
            if(indices[i] > size())
                result = false;
        }

        if(nameExists(name))
            result = false;

        if(result == true) {
            map< string, SliceReference<Register, Register::value_type> >::iterator iter;
            SliceReference<Register, Register::value_type> ref( *this, indices);
            nameToSlice[name] = ref;
        }

        return result;
    }

	void Register::print(ostream& os, string prefix) {
		string sep = "\t";
		//ios::fmtflags flags = os.flags();

		os << prefix << "Register " << name << sep << getSize() << sep << address << sep;

		if(printBase != binary) {
			unsigned long int valueHolder = 0;
			for(int i=getSize()-1; i>=0; i--)
				valueHolder = valueHolder + ((bits[i].state == 1 ? 1 : 0) <<i);
				//valueHolder = valueHolder + ((if((bool) bits[i].state) ? 1 : 0) <<i);
			os << prefix << valueHolder;
		}
		else {
			// binary
			for(int i=getSize()-1; i >= 0; i--)
				os << prefix << bits[i].state;
		}

		os << prefix << endl;
	}



	void Register::printDetailed(ostream& os, string prefix) {
        string sep = "\t";
        string dq  = "\"";
        vector<string> header;
        vector<string> values;

        header.push_back("Name   ");
        header.push_back("Size");
        header.push_back("Address");

        values.push_back(name);
        //values.push_back(TestLib::bitToString(getSize()));
        //values.push_back(TestLib::bitToString(address));
        //TestLib::bitToString(1);

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

        os << prefix 
            << concOrPad("Name", 20)
            << sep << concOrPad("Size", 5)
            << sep << "Address"
            << sep << concOrPad("State", std::max( 6, (int) getSize() + 1))
            << sep << "Default"
            << endl;
        //os << prefix << concOrPad(name, 20)   << sep << concOrPad(toString(getSize()), 5) << sep << concOrPad(toString(address), 8) << sep << concOrPad(getState(), 6) << sep << getDefaultState() << endl;
        os << prefix
            << concOrPad(name, 20)
            << sep << getSize()
            << sep << address
            << sep << concOrPad(getState(), std::max( 6, (int) getSize() + 1))
            << sep << getDefaultState()
            << endl;


        //
        // Now print the individual bit information
        //
        for(unsigned int i=0; i < getSize(); i++) {
            os << prefix << sep << i << " | " 
                << "\"" << getBitName(i) << "\" : "
                << bits[i].state 
                << endl;
        }

        //
        // Now print the Grouped bits information
        //
        map< string, SliceReference<Register, Register::value_type> >::iterator iter;
        for(iter = nameToSlice.begin(); iter != nameToSlice.end(); iter++) {
            os << prefix << sep << dq << iter->first << dq << " | [";
            vector<size_type> indices = iter->second.getIndices();
            for(unsigned int i=0; i < indices.size(); i++) {
                os << indices[i]; if (i < (indices.size() - 1)) os << ",";
            }
            os << prefix << "]" << " : " << get(iter->first) << endl;
        }
	}

    ostream& operator<<(ostream& os, Register& reg) {
        reg.printDetailed(os);
    	return os;
    }



} // end namespace TestLib

