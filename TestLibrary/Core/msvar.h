/*
 * msvar.h
 *
 *  Created on: Sep 4, 2009
 *      Author: x0105974
 */

#ifndef __MSVAR_H__
#define __MSVAR_H__

// MS compatible compilers support #pragma once
#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <vector>
#include <cassert>

//#include <boost/array.hpp>
#include "array1d.h"
#include "array2d.h"

namespace TestLib
{


///
///	\brief MultiSiteVariable class
///
///	This is a templated class that provides a common way of instantiating multi-site variables.
///	* It is similar to std::vector but hides some of the std::vector member functions such as resize, front, at etc...
///    For this reason it encapsulates std::vector instead of deriving from it, so that this class can control some of the
///	  behaviour of functions that would modify the size of the vector
///	* It provides a consistent way to control the depth(or number of sites) of all multi-site variable via conveneint
///	  static function calls or variable access.
///
///	For each type of data object that is templated using this template class the user should execute the following code
///	\code
///		template <typename T> int MSVar<T>::numSites(8);
///      template <typename T> int MSVar<T>::numSites = 8;
///	\endcode
/// TODO : Use indexOffset
///
template <typename T>
class MSVar
{
public:
    MSVar()
    {
        if(numSites > 0)
            vars.resize(numSites);
    }
    MSVar(const T& obj)
    {
        if(numSites > 0)
            vars.resize(numSites, obj);
    }

    // For RValue
    T     operator[] (unsigned int index) const
    {
        assert(index < vars.size());
        return vars[index];
    }
    // For LValue
    T&     operator[] (unsigned int index)
    {
        assert(index < vars.size());
        return vars[index];
    }
    T&     operator=  (const T& obj)
    {
        *this = obj;
    }
    //Reference<T>    operator[] (unsigned int index);

    size_t size(void)
    {
        return vars.size();
    }
    void   clear(void)
    {  }

    T&     get        (unsigned int index)
    {
        if(index < vars.size())
            return vars[index];
    }
    void   set        (unsigned int index, T& val)
    {
        if(index < vars.size())
            vars[index] = val;
    }
    void   set        (unsigned int index, const T& val)
    {
        if(index < vars.size())
            vars[index] = val;
    }

protected:
    std::vector<T> vars;

public:
    static void setNumSites    (int nSites) { numSites = nSites; }
    static int  getNumSites    (void)       { return numSites; }
    static void setIndexOffset (int offset) { indexOffset = offset; }
    static int  getIndexOffset (void)       { return indexOffset; }
public:
    static int numSites;
    static int indexOffset;
};

// This should be done first
template <typename T>
    int MSVar<T>::numSites(8);
template <typename T>
    int MSVar<T>::indexOffset(0);

///
///	\brief MultiSiteVariable class
///
///	This is a templated class that provides a common way of instantiating multi-site variables.
///	* It derives from std::vector to provide the same interface that std::vector does but tries to either hide
///    or alter the behavious of certain member functions and operations that have an impact on the vector size, since
///    we want the vector sites ie: NumSites to be a constant during the lifetime of the variable
///	* It provides a consistent way to control the depth(or number of sites) of all multi-site variable via conveneint
///	  static templated function calls or variable access.
/// * When given an index that is greater than the number of elements, this object should gracefully notify via assert
///
///	For at least one type of data object that is templated using this template class the user should execute the following code
///	\code
///		template <typename T> int MSVarVec<T>::numSites(8);
///      template <typename T> int MSVarVec<T>::numSites = 8;
///	\endcode
///
template <typename T>
class MSVarVec : public std::vector<T>
{
public:
    typedef std::size_t size_type;
    typedef T           value_type;
    typedef T*          iterator;
    typedef const T*    const_iterator;
    typedef T&          reference;
    typedef const T&    const_reference;

    /// \brief Default constructor
    /// Will create an array with numSites objects
    MSVarVec(const_reference value=T())
    {
        if(numSites > 0)
            resize(numSites, value);
    }

    ///////////////////////////////////////////////////////////////////////////////
    //
    // Modified features
    //

    /// This member function is overriden to always return numSites
    static size_type max_size()
    {
        return numSites;
    }
    static bool      empty()
    {
        return false;
    }
    static size_type size()
    {
        return numSites;
    }

    /// This member function is overridden to reset values to default instead of clearing the std::vector
    /// \param[in] value The value used to set the internal array
    void clear(const_reference value=T())
    {
        std::fill_n(this->begin(), this->size(), value);
    }



    //////////////////////////////////////////////////////////////////////////////
    //
    // Added features
    //
    T& operator= (reference value)
    {
        std::fill_n(this->begin(), this->size(), value);
        return *this;
    }
    //T& operator= (const_reference value) { std::fill_n(this->begin(), this->size(), value); return *this; }

private:
    void resize(size_type sz)
    {
        std::vector<T>::resize( sz, value_type());
    }
    void resize(size_type sz, const_reference value)
    {
        std::vector<T>::resize( sz, value);
    }

public:
    static void setNumSites (int nSites)
    {
        numSites = nSites;
    }
    static int  getNumSites (void)
    {
        return numSites;
    }
public:
    static size_type numSites;
    static int       indexOffset;
};
// This should be done first
//template <typename T> int MSVarVec<T>::numSites(8);
//template <typename T> int MSVarVec<T>::indexOffset(0);


///
/// \brief MultiSite Array class
///
/// Based on boost::array
///
template <typename T>
class MSArray : public TestLib::array1d<T,8>
{
public:
    MSArray()
    {
        assign(T());
    }
};


///
///
///
template <typename T, std::size_t V>
class MSArray2D : public TestLib::array2D< T, 8, V>
{
public:
    MSArray2D()
    {
        assign(T());
    }
};

} // end namespace TestLib

#endif /* MSVAR_H_ */
