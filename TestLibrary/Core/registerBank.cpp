	
#include "registerBank.h"

namespace TestLib {

	RegisterBank::RegisterBank(const string _name) {
		name = _name;
	}

	void RegisterBank::print( ostream& os) {
		string sep = "\t";

		os << "RegisterMap" << sep << name << sep << getSize() << endl;
		os << "Type" << sep << "Name" << sep << "Size" << sep << "Address" << sep << "Value" << endl;
		os << "----" << sep << "----" << sep << "----" << sep << "-------" << sep << "-----" << endl;
		for(unsigned int index=0; index < getSize(); index++) {
			regs[index].print(cout);
		}
	}
	void RegisterBank::printDetailed( ostream& os) {
		string sep = "\t";

		os << "RegisterMap" << sep << name << sep << getSize() << endl;
		os << "Type" << sep << "Name" << sep << "Size" << sep << "Address" << sep << "Value" << endl;
		os << "----" << sep << "----" << sep << "----" << sep << "-------" << sep << "-----" << endl;
		for(unsigned int index=0; index < getSize(); index++) {
			regs[index].printDetailed(cout);
		}
	}

	bool RegisterBank::addRegister(const Register& reg) {

		map<string, unsigned int>::iterator iter = regNameToIndex.find(reg.name);

		if(iter != regNameToIndex.end()) {
			std::cerr << "Register of name " << reg.name << " already exists" << endl;
			return false;
		}

		regNameToIndex[reg.name] = regs.size();

		regs.push_back(reg);

		return true;
	}

	Register& RegisterBank::getRegister(const unsigned int index){
		//if(index < 0 || index >= getSize())
			//return Register(0);

		assert( index >= 0 && index < getSize());
		return regs[index];
	}

	Register& RegisterBank::getRegister(const string regName){
		Register reg(0);
		for(unsigned int index=0; index < getSize(); index++)
			if(regs[index].name == regName)
				reg = regs[index];

		return reg;
	}


	Register RegisterBank::operator[](unsigned int index) const{
		//return getRegister(index);
		assert(index >= 0 && index < regs.size());
		return regs[index];
	}

	Register& RegisterBank::operator[](unsigned int index) {
		//return getRegister(index);
		assert(index >= 0 && index < regs.size());
		return regs[index];
	}

/*
	ContainerReference<RegisterBank, Register> RegisterBank::operator[](unsigned int index) {
			assert(index < getSize());

			return ContainerReference<RegisterBank, Register>( *this, index);
	}
*/

	Register& RegisterBank::operator[](const string &regName) {
		return getRegister(regName);
	}

	}