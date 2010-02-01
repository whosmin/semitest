	
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
		for(unsigned int index=0; index < getSize(); index++) {
			regs[index].print(cout);
		}
	}
	void RegisterMap::printDetailed( ostream& os) {
		string sep = "\t";

		os << "RegisterMap" << sep << name << sep << getSize() << endl;
		os << "Type" << sep << "Name" << sep << "Size" << sep << "Address" << sep << "Value" << endl;
		os << "----" << sep << "----" << sep << "----" << sep << "-------" << sep << "-----" << endl;
		for(unsigned int index=0; index < getSize(); index++) {
			regs[index].printDetailed(cout);
		}
	}

	bool RegisterMap::addRegister(const Register& reg) {

		map<string, unsigned int>::iterator iter = regNameToIndex.find(reg.name);

		if(iter != regNameToIndex.end()) {
			std::cerr << "Register of name " << reg.name << " already exists" << endl;
			return false;
		}

		regNameToIndex[reg.name] = regs.size();

		regs.push_back(reg);

		return true;
	}

	Register& RegisterMap::getRegister(const unsigned int index){
		//if(index < 0 || index >= getSize())
			//return Register(0);

        //assert( index >= 0 && index < getSize());
        assert(index < getSize());
		return regs[index];
	}

	Register& RegisterMap::getRegister(const string regName){
		Register reg(0);
		for(unsigned int index=0; index < getSize(); index++)
			if(regs[index].name == regName)
				reg = regs[index];

		return reg;
	}


	Register RegisterMap::operator[](unsigned int index) const{
		//return getRegister(index);
		assert(index >= 0 && index < regs.size());
		return regs[index];
	}

	Register& RegisterMap::operator[](unsigned int index) {
		//return getRegister(index);
		assert(index >= 0 && index < regs.size());
		return regs[index];
	}

/*
	ContainerReference<RegisterMap, Register> RegisterMap::operator[](unsigned int index) {
			assert(index < getSize());

			return ContainerReference<RegisterMap, Register>( *this, index);
	}
*/

	Register& RegisterMap::operator[](const string &regName) {
		return getRegister(regName);
	}

	}

