/* The following code declares class array,
 * an STL container (as wrapper) for arrays of constant size.
 *
 * See
 *      http://www.boost.org/libs/array/
 * for documentation.
 *
 * The original author site is at: http://www.josuttis.com/
 *
 * (C) Copyright Nicolai M. Josuttis 2001.
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * 29 Jan 2004 - c_array() added, BOOST_NO_PRIVATE_IN_AGGREGATE removed (Nico Josuttis)
 * 23 Aug 2002 - fix for Non-MSVC compilers combined with MSVC libraries.
 * 05 Aug 2001 - minor update (Nico Josuttis)
 * 20 Jan 2001 - STLport fix (Beman Dawes)
 * 29 Sep 2000 - Initial Revision (Nico Josuttis)
 *
 * Jan 29, 2004
 */
#ifndef __MSARRAY_H__
#define __MSARRAY_H__

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


namespace TestLib
{

template<class T, std::size_t N=1>
class array1d
{
public:
    T elems[N];    // fixed-size array of elements of type T

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
    iterator begin()
    {
        return elems;
    }
    const_iterator begin() const
    {
        return elems;
    }
    iterator end()
    {
        return elems+N;
    }
    const_iterator end() const
    {
        return elems+N;
    }

    // reverse iterator support
#if !defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) && !defined(BOOST_MSVC_STD_ITERATOR) && !defined(BOOST_NO_STD_ITERATOR_TRAITS)
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
#elif defined(_MSC_VER) && (_MSC_VER == 1300) && defined(BOOST_DINKUMWARE_STDLIB) && (BOOST_DINKUMWARE_STDLIB == 310)
    // workaround for broken reverse_iterator in VC7
    typedef std::reverse_iterator<std::_Ptrit<value_type, difference_type, iterator,
    reference, iterator, reference> > reverse_iterator;
    typedef std::reverse_iterator<std::_Ptrit<value_type, difference_type, const_iterator,
    const_reference, iterator, reference> > const_reverse_iterator;
#else
    // workaround for broken reverse_iterator implementations
    typedef std::reverse_iterator<iterator,T> reverse_iterator;
    typedef std::reverse_iterator<const_iterator,T> const_reverse_iterator;
#endif

    reverse_iterator rbegin()
    {
        return reverse_iterator(end());
    }
    const_reverse_iterator rbegin() const
    {
        return const_reverse_iterator(end());
    }
    reverse_iterator rend()
    {
        return reverse_iterator(begin());
    }
    const_reverse_iterator rend() const
    {
        return const_reverse_iterator(begin());
    }

    // operator[]
    reference operator[](size_type i)
    {
        assert( i < N);
        return elems[i];
    }

    const_reference operator[](size_type i) const
    {
        assert( i< N);
        return elems[i];
    }

    // at() with range check
    reference at(size_type i)
    {
        rangecheck(i);
        return elems[i];
    }
    const_reference at(size_type i) const
    {
        rangecheck(i);
        return elems[i];
    }

    // front() and back()
    reference front()
    {
        return elems[0];
    }

    const_reference front() const
    {
        return elems[0];
    }

    reference back()
    {
        return elems[N-1];
    }

    const_reference back() const
    {
        return elems[N-1];
    }

    // size is constant
    static size_type size()
    {
        return N;
    }
    static bool empty()
    {
        return false;
    }
    static size_type max_size()
    {
        return N;
    }
    enum { static_size = N };

    // swap (note: linear complexity)
    void swap (array1d<T,N>& y)
    {
        std::swap_ranges(begin(),end(),y.begin());
    }

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

    // assignment with type conversion
    template <typename T2>
    array1d<T,N>& operator= (const array1d<T2,N>& rhs)
    {
        std::copy(rhs.begin(),rhs.end(), begin());
        return *this;
    }

    // assign one value to all elements
    void assign (const T& value)
    {
        std::fill_n(begin(),size(),value);
    }

    // check range (may be private because it is static)
    static void rangecheck (size_type i)
    {
        if (i >= size())
        {
            throw std::out_of_range("array<>: index out of range");
        }
    }

};



// comparisons
template<class T, std::size_t N>
bool operator== (const array1d<T,N>& x, const array1d<T,N>& y)
{
    return std::equal(x.begin(), x.end(), y.begin());
}
template<class T, std::size_t N>
bool operator< (const array1d<T,N>& x, const array1d<T,N>& y)
{
    return std::lexicographical_compare(x.begin(),x.end(),y.begin(),y.end());
}
template<class T, std::size_t N>
bool operator!= (const array1d<T,N>& x, const array1d<T,N>& y)
{
    return !(x==y);
}
template<class T, std::size_t N>
bool operator> (const array1d<T,N>& x, const array1d<T,N>& y)
{
    return y<x;
}
template<class T, std::size_t N>
bool operator<= (const array1d<T,N>& x, const array1d<T,N>& y)
{
    return !(y<x);
}
template<class T, std::size_t N>
bool operator>= (const array1d<T,N>& x, const array1d<T,N>& y)
{
    return !(x<y);
}

// global swap()
template<class T, std::size_t N>
inline void swap (array1d<T,N>& x, array1d<T,N>& y)
{
    x.swap(y);
}

} // end namespace TestLib

#endif
