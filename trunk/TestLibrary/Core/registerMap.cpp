	
#include "registerMap.h"

namespace TestLib {

	RegisterMap::RegisterMap(const string _name) {
		name = _name;
	}

	void RegisterMap::print( ostream& os) {
		string sep = "\t";

		os << "RegisterMap" << sep << name << sep << getSize() << endl;
		os << "Type" << sep << "Name" << sep << "Size" << sep << "Address" << sep << "Value" << endl;
		os << "----" << sep << "----" << sep << "----" << sep << "-------" << sep << "-----" << endl;
		for(size_type index=0; index < getSize(); index++) {
			regs[index].print(cout);
		}
	}
	void RegisterMap::printDetailed( ostream& os) {
		string sep = "\t";

		os << "RegisterMap" << sep << name << sep << getSize() << endl;
		os << "Type" << sep << "Name" << sep << "Size" << sep << "Address" << sep << "Value" << endl;
		os << "----" << sep << "----" << sep << "----" << sep << "-------" << sep << "-----" << endl;
		for(size_type index=0; index < getSize(); index++) {
			regs[index].printDetailed(cout);
		}
	}

	bool RegisterMap::addRegister(const Register& reg) {
        // 
        // Check if register fo the same name exists
        // 
		map<string, size_type>::iterator iter = regNameToIndex.find(reg.name);
		if(iter != regNameToIndex.end()) {
			std::cerr << "Register of name " << reg.name << " already exists" << endl;
			return false;
		}

		regNameToIndex[reg.name] = regs.size();

		regs.push_back(reg);

		return true;
	}

    bool RegisterMap::addKeyword( const string& keyword, keywordVec& vec) {
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
        map<string, keywordVec>::iterator kiter = keywordToIndices.find(keyword);
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
            Register::size_type bitIndex = vec[i].second;
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

	Register& RegisterMap::getRegister(size_type index){
		//if(index < 0 || index >= getSize())
			//return Register(0);

        //assert( index >= 0 && index < getSize());
        assert(index < getSize());
		return regs[index];
	}

	Register& RegisterMap::getRegister(const string regName){
        map<string, size_type>::const_iterator iter = regNameToIndex.find(regName);
        assert( iter != regNameToIndex.end());

        size_type regIndex = regNameToIndex[regName];

        return regs[regIndex];
	}


	Register RegisterMap::operator[](size_type index) const{
		//return getRegister(index);
		assert(index < regs.size());
		return regs[index];
	}

	Register& RegisterMap::operator[](size_type index) {
		return getRegister(index);
		//assert(index < regs.size());
		//return regs[index];
	}

/*
	ContainerReference<RegisterMap, Register> RegisterMap::operator[](size_type index) {
			assert(index < getSize());

			return ContainerReference<RegisterMap, Register>( *this, index);
	}
*/

	Register& RegisterMap::operator[](const string &regName) {
		return getRegister(regName);
	}

	}

