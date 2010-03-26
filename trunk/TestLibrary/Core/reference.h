//
// This file is part of SemiTest
//
// Copyright (c) 2009 - 2010 Tushar Jog
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
 * reference.h
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */


#ifndef __CORE_REFERENCE_H__
#define __CORE_REFERENCE_H__

#include <vector>
using namespace std;

namespace TestLib {

	//  TODO: Add a get and set function argument to the template parameter list
	template<class T>
	class Reference
	{
	public:
		Reference(T& t, unsigned int position)
				: objRef(t), index(position)
		{}
		Reference( const Reference& ref)
				: objRef(ref.objRef), index(ref.index)
		{
			objRef.set( index, ref.objRef.get(index));
		}

		operator bool() const
		{
			return objRef.get(index);
		}

		// bool get() { return objRef.get(index); }

		const Reference& operator=(const Reference& ref) const
		{
			objRef.set(index, bool(ref));
			return *this;
		}

		const Reference& operator=(bool value) const
		{
			objRef.set( index, value);
			return *this;
		}

		bool operator==(const Reference& ref) const
		{
			return objRef.get(index) == bool(ref);
		}

		const Reference& operator&=(bool value) const
		{
			objRef.set( index, objRef.get(index) & value);
			return *this;
		}

	private:
		T& objRef;
		unsigned int index;
	};

	/// \brief Indexed Reference template class
	///
	/// This class is meant to be an intermediate class created on the fly
	/// It will allow only indexing operations and no assignment operations
	///
	/// Requirement from class T is that it should have a get( unsigned int i) & set(unsigned int i)
	///
	template<class Collection, class T>
	class IndexedReference
	{
	public:
		IndexedReference(Collection& t, std::size_t position)
				: objRef(t), index(position)
		{}

	#if 0

		IndexedReference(const Collection& t, std::size_t position)
				: index(position)
		{}
	#endif

		IndexedReference( const IndexedReference& ref)
				: objRef(ref.objRef), index(ref.index)
		{
			objRef.set( index, ref.objRef.get(index));
		}

		T& operator[](std::size_t minorIndex) const
		{
			return objRef.get(index + minorIndex);
		}

	private:
		Collection&  objRef;
		unsigned int index;
	};


	template<class Collection, class Type>
	class ContainerReference
	{
	public:
		ContainerReference(Collection& t, unsigned int position)
				: objRef(t), index(position)
		{}
		ContainerReference( const ContainerReference& ref)
				: objRef(ref.objRef), index(ref.index)
		{
			objRef.set( index, ref.objRef.get(index));
		}

		operator bool() const
		{
			return objRef.get(index);
		}

		// bool get() { return objRef.get(index); }

		const ContainerReference& operator=(const ContainerReference& ref) const
		{
			objRef.set(index, bool(ref));
			return *this;
		}

		const ContainerReference& operator=(Type value) const
		{
			objRef.set( index, value);
			return *this;
		}

		bool operator==(const ContainerReference& ref) const
		{
			return objRef.get(index) == bool(ref);
		}

		const ContainerReference& operator&=(Type value) const
		{
			objRef.set( index, objRef.get(index) & value);
			return *this;
		}

	private:
		Collection& objRef;
		unsigned int index;
	};

	template<class Collection, class Type>
        class SliceReference
        {
        public:
            SliceReference() : pObj(NULL) {}
            SliceReference(Collection& t, vector<typename Collection::size_type> positions)
                    : pObj(&t), indices(positions)
            {}
            SliceReference( const SliceReference& rhs)
                    : pObj(rhs.pObj), indices(rhs.indices)
            {
               
            }
            ~SliceReference() {}

            ///
            /// cast to bool
            /// 
            //operator bool() const
            //{
            //    return pObj.get(indices);
            //}

            // bool get() { return pObj.get(indices); }
            //

            Type get(typename Collection::size_type i) { 
                if(i < size())
                    return pObj->get(indices[i]);
                else 
                    return Type();
            }

            size_t size() { return indices.size(); }

            vector<typename Collection::size_type> getIndices() const { return indices; }

            // This is very unlikely to occur and access to it should be removed
            const SliceReference& operator=( const SliceReference& ref) 
            {
                if(pObj != ref.pObj) {
                    pObj = ref.pObj;
                    indices = ref.getIndices();
                }
                return *this;
            }
            SliceReference& operator=( SliceReference& ref) 
            {
                if(pObj != ref.pObj) {
                    pObj = ref.pObj;
                    indices = ref.getIndices();
                }
                return *this;
            }

            //const SliceReference& operator=(Type value) const
            //{
            //    pObj.set( indices, value);
            //    return *this;
            //}
            const SliceReference& operator=(typename Collection::integer_type value)
            {
                for(unsigned int i=0; i < indices.size(); i++) {
                    if(value % 2)
                        pObj->set( indices[i], true);
                    else
                        pObj->set( indices[i], false);
                    value = value >> 1;
                }

                return *this;
            }

/*
            bool operator==(const SliceReference& ref) const
            {
            }

            const SliceReference& operator&=(Type value) const
            {
                pObj.set( indices, pObj.get(indices) & value);
                return *this;
            }
*/

        private:
            Collection* pObj;
            vector<typename Collection::size_type> indices;
        };

	template<class Collection, class Type>
	class ValueReference
	{
	public:
        ValueReference() : pObj(NULL) {}
		ValueReference(Collection& t, unsigned int position)
				: pObj(&t), index(position)
		{}
		ValueReference( const ValueReference& ref)
				: pObj(ref.pObj), index(ref.index)
		{
			pObj->set( index, ref.pObj->get(index));
		}

		operator bool() const
		{
			return (bool) pObj->get(index);
		}

		Type get() { return pObj->get(index); }

		const ValueReference& operator=(const ValueReference& ref) const
		{
			//pObj->set(index, bool(ref));
			pObj->set(index, ref->get());
			return *this;
		}

		const ValueReference& operator=(Type value) const
		{
			pObj->set( index, value);
			return *this;
		}

		bool operator==(const ValueReference& ref) const
		{
			return pObj->get() == ref.pObj->get();
		}

		const ValueReference& operator&=(Type value) const
		{
			pObj->set( index, pObj->get(index) & value);
			return *this;
		}

	private:
		Collection* pObj;
		unsigned int index;
	};

} // end namespace TestLib

#endif /* REFERENCE_H_ */

