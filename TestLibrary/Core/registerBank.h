
/*
 * registerBank.h
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */


#ifndef __TESTLIB_REGISTERBANK_H__
#define __TESTLIB_REGISTERBANK_H__

#include <string>
#include <vector>
#include <map>
#include <boost/logic/tribool.hpp>
#include <iostream>
#include <cassert>

#include "register.h"

namespace TestLib {

	//
	// \brief Encapsulates an entire Register Mapping worth of data
	//
	class RegisterBank : public AbstractRegisterInterface
	{
	public:
		RegisterBank(const string _name);

		virtual size_type getSize(void)
		{
			return regs.size();
		}

		// These two member functions are so that we can use the Reference template class
		Register get(unsigned int index)
		{
			assert(index < getSize());
			return regs[index];
		}
		void    set(unsigned int index, Register value)
		{
			assert(index < getSize());
			regs[index] = value;
		}

		virtual void print( ostream& os);
		virtual void printDetailed( ostream& os);

		// \brief Add a register to the register map
		// \parm[in] reg The register to be added
		// \parm[in] index The index to which to add.
		// 			 If this value is < 0 then the register will be appended to the RegisterMap,
		//           otherwise the Register at index will be replaced.
		virtual bool addRegister(const Register& reg);

		virtual Register& getRegister(const unsigned int index);
		virtual Register& getRegister(const string regName);

		// see http://www.parashift.com/c++-faq-lite/const-correctness.html
		Register operator[]( unsigned int index) const;
		Register& operator[]( unsigned int index);
		//ContainerReference<RegisterBank, Register> operator[]( unsigned int index);
		Register& operator[](const string &regName);
	protected:
		vector<Register> regs;
		map<string, unsigned int> regNameToIndex;
		string name;
	};

	/*
		class RegisterMap : public AbstractRegisterInterface {
			public:
				RegisterMap(const string parmName);
				bool setBits(unsigned int start, unsigned int stop, const Register& reg, unsigned int regStart, unsigned int regStop);
				bool addBits( const Register& reg, unsigned int regStart, unsigned int regStop)
			private:
				unsigned int size;
		};
	*/

}



#endif

