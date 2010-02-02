
/*
 * registerMap.h
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */


#ifndef __TESTLIB_REGISTERMAP_H__
#define __TESTLIB_REGISTERMAP_H__

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
	class RegisterMap : public AbstractRegisterInterface
	{
	public:
        typedef Register     value_type;
        typedef Register&    reference;
        typedef vector< pair< size_type, Register::size_type > > keywordVec;

    public:
		RegisterMap(const string _name);

    /////////////////////////////////////////////////////////////////////////////////
    //
    // These member functions are so that we conform to AbstractRegisterInterface
    //
    /////////////////////////////////////////////////////////////////////////////////
		virtual size_type getSize(void)
		{
			return regs.size();
		}
		virtual void print         ( ostream& os);
		virtual void printDetailed ( ostream& os);

    /////////////////////////////////////////////////////////////////////////////////
    //
    // These two member functions are so that we can use the Reference template class
    //
    /////////////////////////////////////////////////////////////////////////////////
		Register get(size_type index)
		{
			assert(index < getSize());
			return regs[index];
		}
		void    set(size_type index, Register value)
		{
			assert(index < getSize());
			regs[index] = value;
		}
    /////////////////////////////////////////////////////////////////////////////////


		// \brief Add a register to the register map
		// \parm[in] reg The register to be added
		// \parm[in] index The index to which to add.
		// 			 If this value is < 0 then the register will be appended to the RegisterMap,
		//           otherwise the Register at index will be replaced.
		virtual bool      addRegister(const Register& reg);
        virtual bool      addKeyword( const string& keyword, keywordVec& vec);

		virtual Register& getRegister(size_type index);
		virtual Register& getRegister(const string regName);

		// see http://www.parashift.com/c++-faq-lite/const-correctness.html
		Register  operator[] ( size_type index) const;
		Register& operator[] ( size_type index);
		//ContainerReference<RegisterMap, Register> operator[]( size_type index);
		Register& operator[] (const string &regName);


	protected:
		string                 name;
		vector<Register>       regs;
		map<string, size_type> regNameToIndex;
        map<string, keywordVec > keywordToIndices;
	};


}



#endif

