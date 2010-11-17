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
	
#include "registerMap.h"

namespace TestLib {

	RegisterMap::RegisterMap(const string _name) {
		name = _name;
	}

    RegisterMap::RegisterMap(const RegisterMap& regMap) {
        name           = regMap.name;
        regs           = regMap.regs;
        regNameToIndex = regMap.regNameToIndex;
        nameToSlice    = regMap.nameToSlice;
    }

	void RegisterMap::print( ostream& os, string prefix) {
		string sep = "\t";

		os << "RegisterMap" << sep << name << sep << getSize() << endl;
		//os << "Type" << sep << "Name" << sep << "Size" << sep << "Address" << sep << "Value" << endl;
		//os << "----" << sep << "----" << sep << "----" << sep << "-------" << sep << "-----" << endl;
		//for(size_type index=0; index < getSize(); index++) {
			//regs[index].print(os, sep);
		//}
	}
	void RegisterMap::printDetailed( ostream& os, string prefix) {
		string sep = "\t";

		os << prefix << "RegisterMap" << sep << name << sep << getSize() << endl;
		//os << "Type" << sep << "Name" << sep << "Size" << sep << "Address" << sep << "Value" << endl;
		//os << "----" << sep << "----" << sep << "----" << sep << "-------" << sep << "-----" << endl;
        os << prefix << sep << "Registers" << endl;
		for(size_type index=0; index < getSize(); index++) {
			//regs[index].printDetailed(os, prefix + sep);
            regs[index].printDetailed( os, prefix);
            os << endl;
		}
	}

    bool RegisterMap::nameExists( string name) {
        bool exists = false;

        if(regNameToIndex.find(name) != regNameToIndex.end())
            exists = true;

        if(nameToSlice.find(name) != nameToSlice.end())
            exists = true;

        return exists;
    }

	bool RegisterMap::addRegister(const RegisterMap::value_type& reg) {
        // 
        // Check if register fo the same name exists
        // 
        if(nameExists(reg.name)) {
			std::cerr << "Register or Slice of name " << reg.name << " already exists" << endl;
			return false;
		}

		regNameToIndex[reg.name] = regs.size();

		regs.push_back(reg);

		return true;
	}

    bool RegisterMap::setName( string name, vector< pair<string, RegisterMap::value_type::size_type> >& values) {
        if(nameExists( name) ) {
			std::cerr << "Register or Slice of name " << name << " already exists" << endl;
            return false;
        }

        RegisterSlice slice;
        for(unsigned int i=0; i < values.size(); i++) {
            string              regName = values[i].first;
            RegisterMap::value_type::size_type index   = values[i].second;
            slice.addBit( getRegister(regName), index);
        }
        nameToSlice[name] = slice;

        return true;
    }

#if 0
    bool RegisterMap::addKeyword( const string& keyword, KeywordVec& vec) {
        bool result = true;

        // 
        // Check if register fo the same name exists
        // 
		map<string, size_type>::iterator iter = regNameToIndex.find(keyword);
		if(iter != regNameToIndex.end()) {
			std::cerr << "Keyword exists : Register of name " << keyword << " already exists" << endl;
			return false;
		}

        // 
        // Check if keyword of the same name exists
        // 
        map<string, KeywordVec>::iterator kiter = keywordToIndices.find(keyword);
		if(kiter != keywordToIndices.end()) {
			std::cerr << "Keyword of name " << keyword << " already exists" << endl;
			return false;
		}
        
        // 
        // Check if vec has all valid entries
        // 
        bool valid = true;
        for(unsigned int i=0; i < vec.size(); i++) {
            size_type           regIndex = vec[i].first;
            RegisterMap::value_type::size_type bitIndex = vec[i].second;
            if(regIndex > getSize())
                valid = false;
            if(bitIndex > regs[i].getSize())
                valid = false;
        }

        if(valid == false) {
            std::cerr << "Invalid arguments given" << endl;
            return false;
        }

        keywordToIndices[keyword] = vec;

        return result;
    }
#endif

    RegisterMap::value_type& RegisterMap::getRegister(size_type index){
		//if(index < 0 || index >= getSize())
			//return Register(0);

        //assert( index >= 0 && index < getSize());
        if(index >= getSize()) {
            std::cerr << "index : " << index << " getSize() : " << getSize() << endl;
            assert(index < getSize());
        }
		return regs[index];
	}

    RegisterMap::value_type& RegisterMap::getRegister(const string regName){
        map<string, size_type>::const_iterator iter = regNameToIndex.find(regName);
        assert( iter != regNameToIndex.end());

        size_type regIndex = regNameToIndex[regName];

        return regs[regIndex];
	}


    RegisterMap::value_type RegisterMap::operator[](size_type index) const{
		//return getRegister(index);
		assert(index < regs.size());
        value_type reg = regs[index];
		return reg;
	}
#if 1
	RegisterMap::value_type& RegisterMap::operator[](size_type index) {
		if(index >= getSize()) {
            std::cerr << "index : " << index << " getSize() : " << getSize() << endl;
            assert(index < getSize());
        }

		return regs[index];
	}
#endif
#if 0
	boost::reference_wrapper<Register> RegisterMap::operator[] (size_type index) {
		if(index >= getSize()) {
            std::cerr << "index : " << index << " getSize() : " << getSize() << endl;
            assert(index < getSize());
        }
		return boost::ref(regs[index]);
	}
#endif
#if 0
    ContainerReference<RegisterMap, RegisterMap::value_type> RegisterMap::operator[](size_type index) {
		//return getRegister(index);

		//assert(index < regs.size());
		//return regs[index];

		if(index >= getSize()) {
            std::cerr << "index : " << index << " getSize() : " << getSize() << endl;
            assert(index < getSize());
        }
		//return regs[index];
		return ContainerReference<RegisterMap, RegisterMap::value_type>( *this, index);
	}
#endif

/*
	ContainerReference<RegisterMap, RegisterMap::value_type> RegisterMap::operator[](size_type index) {
			assert(index < getSize());

			return ContainerReference<RegisterMap, RegisterMap::value_type>( *this, index);
	}
*/

    RegisterMap::value_type RegisterMap::operator[](const string &regName) const {
		//return getRegister(regName);

		map<string, size_type>::const_iterator iter = regNameToIndex.find(regName);
        assert( iter != regNameToIndex.end());

        size_type regIndex = regNameToIndex.find(regName)->second;

        return regs[regIndex];
	}
    RegisterMap::value_type& RegisterMap::operator[](const string &regName) {
		//return getRegister(regName);

		map<string, size_type>::const_iterator iter = regNameToIndex.find(regName);
        assert( iter != regNameToIndex.end());

        size_type regIndex = regNameToIndex.find(regName)->second;

        return regs[regIndex];
	}
#if 0
	boost::reference_wrapper<Register> RegisterMap::operator[] (const string& regName) {
		map<string, size_type>::const_iterator iter = regNameToIndex.find(regName);
        assert( iter != regNameToIndex.end());

        size_type regIndex = regNameToIndex.find(regName)->second;

		return boost::ref(regs[regIndex]);
	}
#endif
    RegisterMap::integer_type RegisterMap::get(string name) {
        integer_type value = 0;

        if(nameToSlice.find(name) == nameToSlice.end())
            return value;

        return nameToSlice[name].get();
    }

    ostream& operator<<(ostream& os, RegisterMap& reg) {
        reg.printDetailed(os);
        return os;
    }

}

