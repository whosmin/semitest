/*
 * MSArray2D.h
 *
 *  Created on: Oct 1, 2009
 *      Author: tusharjog
 */

#ifndef __ARRAY2D_H__
#define __ARRAY2D_H__

#include <cstddef>
#include <stdexcept>
//#include <boost/assert.hpp>
#include <cassert>

// Handles broken standard libraries better than <iterator>
//#include <boost/detail/iterator.hpp>
//#include <boost/throw_exception.hpp>
#include <algorithm>

// FIXES for broken compilers
//#include <boost/config.hpp>

#include "reference.h"

namespace TestLib
{

/// N = Num Sites
/// V = Num Variables
template<class T, std::size_t N, std::size_t V>
class array2D
{
public:
    T elems[N*V];    // fixed-size array of elements of type T

public:
    // type definitions
    typedef T              value_type;
    typedef T*             iterator;
    typedef const T*       const_iterator;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

    // iterator support
    iterator 		begin()
    {
        return elems;
    }
    const_iterator 	begin() const
    {
        return elems;
    }
    iterator 		end()
    {
        return elems+N*V;
    }
    const_iterator 	end() const
    {
        return elems+N*V;
    }

    reference get(unsigned int i)
    {
        assert(i < size());
        return elems[i];
    }

    const_reference get(unsigned int i) const
    {
        assert(i < size());
        return elems[i];
    }

    void set(unsigned int i, T& value) {
    	assert(i < size());
    	elems[i] = value;
    }


    IndexedReference<array2D<T,N,V>, T> operator[](size_type i) const
    {
        assert( i < size());
        return IndexedReference<array2D<T,N,V>, T>( (array2D<T,N,V>&) *this, i);
    }

    // size is constant
    static size_type size()
    {
        return N*V;
    }
    static bool empty()
    {
        return false;
    }
    static size_type max_size()
    {
        return N*V;
    }
    enum { static_size = N*V };

    // direct access to data (read-only)
    const T* data() const
    {
        return elems;
    }
    T* data()
    {
        return elems;
    }

    // use array as C array (direct read/write access to data)
    T* c_array()
    {
        return elems;
    }

    // assign one value to all elements
    void assign (const T& value)
    {
        std::fill_n(begin(),size(),value);
    }

};

} // end namespace TestLib

#endif /* __ARRAY2D_H__ */
