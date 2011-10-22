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
 * MSReg.cpp
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */

#include "MSReg.h"
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


	MSReg::MSReg( size_type size, string regName, unsigned int add, string defaultValue)
		: address(add), name(regName)
	{
		printBase = decimal;
        // This resize operation will already set the bits to indeterminate state
		resize(size);

       //while(defaultValue.size() < size)
       //    defaultValue = "x" + defaultValue;
       if(defaultValue.size() > 0)
           setDefault(defaultValue);

       for(size_type i=0; i < getSize(); i++)
		   for(unsigned int j=0; j < bits[i].size(); j++)
			bits[i][j].state = bits[i][j].defaultState;

	   altAddress = 0;
	}

    MSReg::MSReg( size_type size, string regName, unsigned int add, integer_type defaultValue)
        : address(add), name(regName)
    {
        printBase = decimal;
        resize(size);

        setState(defaultValue);
        for(size_type i=0; i < getSize(); i++)
			for(unsigned int j=0; j < bits[i].size(); j++)
				bits[i][j].defaultState = bits[i][j].state;

		altAddress = 0;
    }
    MSReg::MSReg( size_type size, string regName, string add, string defaultValue)
        : name(regName)
    {
        printBase = decimal;
        resize(size);

        if(add.size() > 0)
            setAddress( add);

        if(defaultValue.size() > 0) {
            setState( defaultValue);
            for(size_type i=0; i < getSize(); i++)
				for(unsigned int j=0; j < bits[i].size(); j++)
					bits[i][j].defaultState = bits[i][j].state;
        }
		altAddress = 0;
    }

    MSReg::MSReg( const MSReg& reg) {
        printBase      = reg.printBase;
        address        = reg.address;
        name           = reg.name;
        bits           = reg.bits;
        bitNameToIndex = reg.bitNameToIndex;
        nameToSlice    = reg.nameToSlice;
		altAddress     = reg.altAddress;
    }

	bool MSReg::resize(size_type size, value_type value) {
		bits.resize(size, MSBitInfo(value));
		return true;
	}

	bool MSReg::setDefault(const string& value) {
		if(getSize() == 0)
			return false;

        vector<value_type> bitVec;
        integer_type decValue = 0;
        stringToBool<value_type>( value, bitVec, (unsigned int) getSize(), decValue);

        for(size_type i=0; i < min(getSize(), bitVec.size()); i++)
			for(unsigned int j=0; j < bits[i].size(); j++)
				bits[i][j].defaultState = bitVec[i];

		return true;
	}

	bool MSReg::setAddress(const string& value) {
		//if(getSize() == 0)
		//	return false;

        vector<value_type> bitVec;
        integer_type decValue = 0;
        stringToBool<value_type>( value, bitVec, (unsigned int) getSize(), decValue);

		address = (unsigned int) decValue;

		return true;
	}

	bool MSReg::setAddress(unsigned int value) {
		address = value;

		return true;
	}

    bool MSReg::setState(const string& bitStr) {
        if(getSize() == 0)
            return false;

        vector<value_type> bitVec;
        integer_type value = 0;
        stringToBool<value_type>( bitStr, bitVec, (unsigned int) getSize(), value);

        for(size_type i=0; i < min(getSize(), bitVec.size()); i++)
            bits[i] = bitVec[i];

        return true;
    }
    bool MSReg::setState( const integer_type& value) {
        if(getSize() == 0) return false;

        size_type maxSize = std::min( (int) getSize(), numeric_limits<integer_type>::digits);
        for(size_type i = 0; (i < maxSize); i++) {
            if((value >> i) % 2)
                bits[i] = (value_type) true;
           else
                bits[i] = (value_type) false;
        }

        return true;
    }

	bool MSReg::setBitName(size_type index, string name) {
		if(index > getSize())
			return false;

		map<string, size_type>::iterator iter = bitNameToIndex.find(name);
		if(iter != bitNameToIndex.end()) {
			cerr << "Bit name " << name << " already exists" << endl;
			return false;
		}

		bitNameToIndex[name] = index;

		for(unsigned int j=0; j < bits[index].size(); j++)
			bits[index][j].name = name;
		return true;
	}

	string MSReg::getBitName(size_type index) {
        string name;
		assert(index < getSize());
		if(index > getSize())
			return name;

        return bits[index][0].name;
    }

	bool MSReg::setBitValues( size_type index, value_type value, value_type resetValue, value_type defaultValue) {
		if(index > getSize())
			return false;

		//bits[index].state = value;
		//bits[index].resetState = resetValue;
		//bits[index].defaultState = defaultValue;

		bits[index] = BitInfo( value, resetValue, defaultValue);
		return true;
	}

	bool MSReg::setBitValues( const string& name, value_type value, value_type resetValue, value_type defaultValue) {
		//for(unsigned int index=0; index < getSize(); )

		return true;
	}
	bool MSReg::setBitState( size_type index, value_type value) {
		if(index > getSize())
			return false;
		bits[index] = value;
		return true;
	}
	bool MSReg::setBitResetState(size_type index, value_type resetValue) {
		if(index > getSize())
			return false;

		for(unsigned int j=0; j < bits[index].size(); j++)
			bits[index][j].resetState = resetValue;

		return true;
	}

	bool MSReg::setBitDefaultState( size_type index, value_type defaultValue) {
		if(index > getSize())
			return false;

		for(unsigned int j=0; j < bits[index].size(); j++)
			bits[index][j].defaultState = defaultValue;

		return true;
	}

	bool MSReg::set( const string& name, integer_type value) {
		if(!this->nameExists(name))
			return false;

		if(this->nameToSlice.find(name) != this->nameToSlice.end()) {
            SliceReference<MSReg, MSReg::value_type> slice = this->nameToSlice[name];
            size_type sliceSize = slice.size();
			//slice = value;
			
			{
				vector<size_type> indices = slice.getIndices();
				for(size_type i=0; i < indices.size(); i++) {
                    if(value % 2)
                        this->setBitState( indices[i], true);
                    else
                        this->setBitState( indices[i], false);
                    value = value >> 1;
                }
			}
        }
        else if(bitNameToIndex.find(name) != bitNameToIndex.end()) {
            //integer_type bitValue = bitNameToIndex[name] == true ? 1 : 0;
			this->bits[bitNameToIndex[name]] = (value_type) (value > 0 ? true : false);
        }

		return true;
	}

#if 0
    string MSReg::getDefaultState() {
        string defStr;
        for(size_type i=0; i < getSize(); i++) {
            defStr = bitToString<value_type>(bits[i].defaultState) + defStr;
        }
        return defStr;
    }
    string MSReg::getState() {
        string str;
        for(size_type i=0; i < getSize(); i++) {
            str = bitToString<value_type>(bits[i].state) + str;
        }
        return str;
    }
    MSReg::integer_type MSReg::getStateInteger() {
        integer_type value = 0;
        for(size_type i=0; i < getSize(); i++) {
            integer_type bitValue = bits[i].state == true ? 1 : 0;
            value += bitValue << i;
        }

        return value;
    }

    MSReg::integer_type MSReg::get(void) {
        return getStateInteger();
    }

    MSReg::integer_type MSReg::get(string name) {
        integer_type value = 0;

        if(nameToSlice.find(name) != nameToSlice.end()) {
            SliceReference<MSReg, MSReg::value_type> slice = nameToSlice[name];
            size_type sliceSize = slice.size();

            vector<MSReg::size_type> indices = slice.getIndices();
            for(size_type i=0; i < indices.size(); i++) {
                integer_type bitValue = bits[indices[i]].state == true ? 1 : 0;
                value += bitValue << i;
            }
        }
        else if(bitNameToIndex.find(name) != bitNameToIndex.end()) {
            integer_type bitValue = bitNameToIndex[name] == true ? 1 : 0;
        }

        return value;
    }
#endif

#if 0
    MSReg::value_type MSReg::get(string name) {
        value_type value;

        return value;
    }
#endif

    //template<class ReturnType> ReturnType  MSReg::get (string name) {
    //}

    MSReg& MSReg::flip(void) {
        for(size_type i=0; i < getSize(); i++) {
			for(unsigned int j=0; j < bits[i].size(); j++)
				bits[i][j].state = !bits[i][j].state;
        }

        return *this;
    }

#if 0
    size_t MSReg::count(void) {
        size_t num = 0;

        for(size_type i=0; i < getSize(); i++)
            if(bits[i].state == true)
                num++;

        return num;
    }

    bool MSReg::any(void) {
        bool result = false;

        for(size_type i=0; i < getSize(); i++)
            if(bits[i].state == true)
                result = true;

        return result;
    }

    bool MSReg::none(void) {
        bool result = true;

        for(size_type i=0; i < getSize(); i++)
            if(bits[i].state == true)
                result = false;

        return result;
    }
#endif
	void MSReg::clear(void) {
		for(size_type index=0; index < getSize(); index++)
			bits[index] = BitInfo();
		clearState();
	}

	void MSReg::clearState(void) {
		for(size_type index = 0; index < getSize(); index++) {
			bits[index] = BitInfo(bits[index][0].name);
		}
	}

	//bool MSReg::set( unsigned long value, size_type size) {
	//	return true;
	//}

	/*
	value_type MSReg::operator[](const unsigned int index) {
		value_type temp;
		if(index > getSize())
			return temp;
		return state[index];
	}
	*/


	MSBitInfo MSReg::operator[](size_type index) const {
		return bits[index];
	}

#if 0
	MSReg::reference MSReg::operator[](const string& name) {
		size_type bitIndex = -1;
		if(nameToSlice.find(name) != nameToSlice.end()) {
			vector<size_type> indices = nameToSlice[name].getIndices();
			if(indices.size() == 1)
				bitIndex = indices[0];
			else {
				cerr << __FUNCTION__ << " argument not evaluating to a bit type" << endl;
				assert(indices.size() == 1);
			}
		}
		else
			if(bitNameToIndex.find(name) == bitNameToIndex.end()) {
				cerr << __FUNCTION__ << " argument not evaluating to a bit type" << endl;
				assert(bitNameToIndex.find(name) != bitNameToIndex.end());
			}
			else
				bitIndex = bitNameToIndex[name];

		assert(bitIndex >= 0 && bitIndex < bits.size());

		return bits[bitIndex].state;
	}
#else
	SliceReference<MSReg, MSReg::value_type> MSReg::operator[](const string& name) {
		if(bitNameToIndex.find(name) != bitNameToIndex.end()) {
			size_type bitIndex = bitNameToIndex[name];
			vector<size_type> indices;
			indices.push_back(bitIndex);
			return SliceReference<MSReg, MSReg::value_type>( *this, indices);
		}

		if(nameToSlice.find(name) != nameToSlice.end()) {
			size_type bitIndex = -1;
			vector<size_type> indices = nameToSlice[name].getIndices();
			return SliceReference<MSReg, MSReg::value_type>(*this, indices);
		}

		cerr << __FUNCTION__ << " argument not a valid keyword" << endl;
		assert(false);

		return SliceReference<MSReg, MSReg::value_type>( *this, vector<size_type>());
	}
#endif

//    unsigned long long MSReg::operator[](const string& name) {
//        unsigned long long value = 0;
//
//        return value;
//    }

#if 0	
    MSReg::value_type MSReg::operator[](const string& name) const {
        integer_type value = 0;

        if(nameToSlice.find(name) != nameToSlice.end()) {
            SliceReference<MSReg, MSReg::value_type> slice = nameToSlice.find(name)->second;
            size_type sliceSize = slice.size();

            vector<MSReg::size_type> indices = slice.getIndices();
            for(size_type i=0; i < indices.size(); i++) {
                integer_type bitValue = bits[indices[i]].state == true ? 1 : 0;
                value += bitValue << i;
            }
        }
        else if(bitNameToIndex.find(name) != bitNameToIndex.end()) {
            integer_type bitValue = bits[bitNameToIndex.find(name)->second].state == true ? 1 : 0;
        }

        return value;
	}
#endif	
    MSBitInfo MSReg::operator[](const string& name) const {
        MSBitInfo value;
/*
        if(nameToSlice.find(name) != nameToSlice.end()) {
            SliceReference<MSReg, MSReg::value_type> slice = nameToSlice.find(name)->second;
            size_type sliceSize = slice.size();

            vector<MSReg::size_type> indices = slice.getIndices();
            for(size_type i=0; i < indices.size(); i++) {
				for(unsigned int j=0; j < bits[indices[i]].size(); j++) {
					integer_type bitValue = bits[indices[i]][j].state == true ? 1 : 0;
					value[j] += bitValue << i;
				}
            }
        }
        else 
		*/
			
		if(bitNameToIndex.find(name) != bitNameToIndex.end()) {
            //integer_type bitValue = bits[bitNameToIndex.find(name)->second].state == true ? 1 : 0;
			value = bits[bitNameToIndex.find(name)->second];
        }

        return value;
	}

	ValueReference<MSReg, MSReg::value_type> MSReg::operator[](size_type index) {
		assert(index < getSize());

		return ValueReference<MSReg, MSReg::value_type>( *this, (unsigned int) index);
	}

    /*
    tribool& MSReg::operator[](size_type index) {
        return bits[index].state;
    }
    */

	MSReg& MSReg::operator=(const MSReg& reg) {

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
   const string&   MSReg::operator=(const string& str) {
       setState(str);
       return str;
   }

   const MSReg::integer_type&   MSReg::operator=(const integer_type& val) {
       setState(val);
       return val;
   }
    bool MSReg::nameExists(string name) {
        bool exists = false;

        if(nameToSlice.find(name) != nameToSlice.end())
            exists = true;

        if(bitNameToIndex.find(name) != bitNameToIndex.end())
            exists = true;

        return exists;
    }

    bool MSReg::setName( const string& name, vector<size_type> indices) {
        bool result = true;

        for(size_type i=0; i < indices.size(); i++) {
            if(indices[i] > size())
                result = false;
        }

        if(nameExists(name))
            result = false;

        if(result == true) {
            map< string, SliceReference<MSReg, MSReg::value_type> >::iterator iter;
            SliceReference<MSReg, MSReg::value_type> ref( *this, indices);
            nameToSlice[name] = ref;
        }

        return result;
    }

	void MSReg::print(ostream& os, string prefix) {
		string sep = "\t";
		//ios::fmtflags flags = os.flags();

		os << prefix << "MSReg " << name << sep << getSize() << sep << address << sep;

		/* TODO Fix this
		if(printBase != binary) {
			unsigned long int valueHolder = 0;
			for(size_type i=getSize()-1; i>=0; i--)
				valueHolder = valueHolder + ((bits[i].state == 1 ? 1 : 0) <<i);
				//valueHolder = valueHolder + ((if((bool) bits[i].state) ? 1 : 0) <<i);
			os << prefix << valueHolder;
		}
		else {
			// binary
			for(size_type i=getSize()-1; i >= 0; i--)
				os << prefix << bits[i].state;
		}
		*/

		os << prefix << endl;
	}



	void MSReg::printDetailed(ostream& os, string prefix) {
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

        vector<size_t> maxSizes;
        for(size_t i=0; i < header.size(); i++) {
            size_t maxSize = 0;
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
            //<< sep << concOrPad(getState(), std::max( 6, (int) getSize() + 1))
            //<< sep << getDefaultState()
            << endl;


        //
        // Now print the individual bit information
        //
        for(size_type i=0; i < getSize(); i++) {
            os << prefix << sep << i << " | " 
                << "\"" << getBitName(i) << "\" : "
                //<< bits[i].state 
                << endl;
        }

        //
        // Now print the Grouped bits information
        //
        map< string, SliceReference<MSReg, MSReg::value_type> >::iterator iter;
        for(iter = nameToSlice.begin(); iter != nameToSlice.end(); iter++) {
            os << prefix << sep << dq << iter->first << dq << " | [";
            vector<size_type> indices = iter->second.getIndices();
            for(unsigned int i=0; i < indices.size(); i++) {
                os << indices[i]; if (i < (indices.size() - 1)) os << ",";
            }
			// TODO fix this below
            //os << prefix << "]" << " : " << get(iter->first) << endl;
        }
	}

    ostream& operator<<(ostream& os, MSReg& reg) {
        reg.printDetailed(os);
    	return os;
    }

int toInt(string str) {
    int value = 0;

    stringstream sstr;
    sstr << str;
    sstr >> value;

    return value;
}

MSReg MSReg::createMSRegHelper( string str) {
    MSReg reg;

    unsigned int size = 0;
    string   name;
    string   address;
    string   defValue;
    string   slice;
    string   names;
    vector< vector<MSReg::size_type> > sliceIndices;
    vector<string>                 sliceNames;

    stringstream sstr;

    vector<string> fields = split( str, ";");
    if(fields.size() > 0) {
        size = toInt(fields[0]);
    }
    if(fields.size() > 1)
        name = fields[1];
    if(fields.size() > 2)
        address = fields[2];
    if(fields.size() > 3)
        defValue = fields[3];

    if(fields.size() > 1)
        reg = MSReg( size, name, address, defValue);

    if( fields.size() > 5) {
        slice = fields[4];
        names = fields[5];
        sliceNames = split( names, ",");
        vector<string> sliceVec = split( slice, ",");
        if(sliceNames.size() == sliceVec.size()) {
            for(unsigned int i=0; i < sliceVec.size(); i++) {
                vector<unsigned int> indices;
                vector<string>       digitVec = split( sliceVec[i], ":");
                unsigned int first = 0, second = 0;
                first = toInt(digitVec[0]);
                if(digitVec.size() > 1)
                    second = toInt(digitVec[1]);
               else
                   second = first;
                unsigned int start = std::min( first, second);
                unsigned int stop  = std::max( first, second);
                for(unsigned int i = start; i <= stop; i++)
                    indices.push_back(i);

                sliceIndices.push_back(indices);
            }
        }
        else {
            std::cerr << "slice names to slice vec mismatch." << endl;
            std::cerr  << slice << endl << names << endl;
        }
        for(unsigned int i=0; i < sliceNames.size(); i++) {
            reg.setName( sliceNames[i], sliceIndices[i]);
        }
    }

    return reg;
}


} // end namespace TestLib

