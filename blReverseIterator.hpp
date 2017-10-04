#ifndef BL_REVERSEITERATOR_HPP
#define BL_REVERSEITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blReverseIterator.hpp
// CLASS:           blReverseIterator
// BASE CLASS:      None
//
// PURPOSE:         -- A simple reverse iterator that moves backwards
//                     in a contiguous space when "advanced forward" and
//                     moves backward in a contiguous space when
//                     "advanced backwards", which also works with
//                     stl-algorthms
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    <iterator>
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

// Used to define iterator category

#include <iterator>

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
class blReverseIterator
{
public: // Iterator traits



    using iterator_category = std::random_access_iterator_tag;
    using value_type = blDataType;
    using difference_type = ptrdiff_t;
    using pointer = blDataType*;
    using reference = blDataType&;



public: // Constructors and destructors



    // Default constructor

    blReverseIterator(blDataType* ptr = nullptr);



    // Constructor from another
    // type of iterator

    template<typename blAnotherTypeOfIterator>
    blReverseIterator(const blAnotherTypeOfIterator& iter);



    // Copy constructor

    blReverseIterator(const blReverseIterator<blDataType>& reverseIterator);



    // Destructor

    ~blReverseIterator();



public: // Public functions



    // Overloaded assignment operators

    template<typename blAnotherTypeOfIterator>
    blReverseIterator<blDataType>&              operator=(const blAnotherTypeOfIterator& iter);
    blReverseIterator<blDataType>&              operator=(const std::nullptr_t& nullPointer);
    blReverseIterator<blDataType>&              operator=(const blReverseIterator<blDataType>& reverseIterator);
    blReverseIterator<blDataType>&              operator=(blDataType* ptr);



    // Overloaded assignment operators

    blReverseIterator<blDataType>&              operator+=(const ptrdiff_t& movement);
    blReverseIterator<blDataType>&              operator-=(const ptrdiff_t& movement);
    blReverseIterator<blDataType>&              operator++();
    blReverseIterator<blDataType>&              operator--();
    blReverseIterator<blDataType>               operator++(int);
    blReverseIterator<blDataType>               operator--(int);
    blReverseIterator<blDataType>               operator+(const int& movement)const;
    blReverseIterator<blDataType>               operator-(const int& movement)const;



    // Operator used to "subtract"
    // two pointers (it gives the
    // distance)

    ptrdiff_t                                   operator-(const blReverseIterator<blDataType>& reverseIterator)const;



    // Base operator

    blReverseIterator<blDataType>               base();



    // Overloaded referencing/dereferencing
    // operators

    blDataType&                                 operator*();
    const blDataType&                           operator*()const;
    blDataType*                                 operator->();



    // Functions to get the
    // raw pointer

    blDataType*                                 getPtr()const;
    const blDataType*                           getConstPtr()const;



private: // Private variables



    // The actual raw pointer

    blDataType*                                 m_ptr;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType>::blReverseIterator(blDataType* ptr)
{
    m_ptr = ptr;
}



template<typename blDataType>
template<typename blAnotherTypeOfIterator>
inline blReverseIterator<blDataType>::blReverseIterator(const blAnotherTypeOfIterator& iter)
{
    this->m_ptr = &(*iter);
}



template<typename blDataType>
inline blReverseIterator<blDataType>::blReverseIterator(const blReverseIterator<blDataType>& reverseIterator)
{
    this->m_ptr = reverseIterator.getPtr();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType>::~blReverseIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Assignment operators
//-------------------------------------------------------------------
template<typename blDataType>
template<typename blAnotherTypeOfIterator>
inline blReverseIterator<blDataType>& blReverseIterator<blDataType>::operator=(const blAnotherTypeOfIterator& iter)
{
    this->m_ptr = &(*iter);

    return (*this);
}


template<typename blDataType>
inline blReverseIterator<blDataType>& blReverseIterator<blDataType>::operator=(const std::nullptr_t& nullPointer)
{
    this->m_ptr = nullPointer;

    return (*this);
}



template<typename blDataType>
inline blReverseIterator<blDataType>& blReverseIterator<blDataType>::operator=(const blReverseIterator<blDataType>& reverseIterator)
{
    if(this != &reverseIterator)
    {
        this->m_ptr = reverseIterator.getPtr();
    }

    return (*this);
}



template<typename blDataType>
inline blReverseIterator<blDataType>& blReverseIterator<blDataType>::operator=(blDataType* ptr)
{
    this->m_ptr = ptr;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType>& blReverseIterator<blDataType>::operator+=(const ptrdiff_t& movement)
{
    this->m_ptr -= movement;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType>& blReverseIterator<blDataType>::operator-=(const ptrdiff_t& movement)
{
    this->m_ptr += movement;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType>& blReverseIterator<blDataType>::operator++()
{
    --this->m_ptr;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType>& blReverseIterator<blDataType>::operator--()
{
    ++this->m_ptr;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType> blReverseIterator<blDataType>::operator++(int)
{
    auto temp(*this);

    --this->m_ptr;

    return temp;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType> blReverseIterator<blDataType>::operator--(int)
{
    auto temp(*this);

    ++this->m_ptr;

    return temp;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType> blReverseIterator<blDataType>::operator+(const int& movement)const
{
    auto oldPtr = this->m_ptr;

    oldPtr -= movement;

    return blReverseIterator<blDataType>(oldPtr);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType> blReverseIterator<blDataType>::operator-(const int& movement)const
{
    auto oldPtr = this->m_ptr;

    oldPtr += movement;

    return blReverseIterator<blDataType>(oldPtr);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline ptrdiff_t blReverseIterator<blDataType>::operator-(const blReverseIterator<blDataType>& reverseIterator)const
{
    return std::distance(reverseIterator.getPtr(),m_ptr);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blReverseIterator<blDataType> blReverseIterator<blDataType>::base()
{
    auto basePtr = m_ptr;

    --basePtr;

    return blReverseIterator<blDataType>(basePtr);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType& blReverseIterator<blDataType>::operator*()
{
    return *m_ptr;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType& blReverseIterator<blDataType>::operator*()const
{
    return *m_ptr;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType* blReverseIterator<blDataType>::operator->()
{
    return m_ptr;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blDataType* blReverseIterator<blDataType>::getPtr()const
{
    return m_ptr;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline const blDataType* blReverseIterator<blDataType>::getConstPtr()const
{
    return m_ptr;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_REVERSEITERATOR_HPP
