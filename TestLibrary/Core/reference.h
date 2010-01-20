/*
 * reference.h
 *
 *  Created on: Aug 15, 2009
 *      Author: tusharjog
 */


#ifndef REFERENCE_H_
#define REFERENCE_H_

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

} // end namespace TestLib

#endif /* REFERENCE_H_ */

