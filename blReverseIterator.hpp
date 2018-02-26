#ifndef BL_REVERSEITERATOR_HPP
#define BL_REVERSEITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blReverseIterator.hpp
// CLASS:           blReverseIterator
//
//
//
// PURPOSE:         -- A simple reverse iterator that moves backwards
//                     in a contiguous space when "advanced forward" and
//                     moves forward in a contiguous space when
//                     "advanced backwards", which also works with
//                     stl-algorthms
//
//                  -- This reverse iterator allows the user to choose
//                     the type of pointer to be used, which is defaulted
//                     to a raw pointer.
//                     The user could instead opt to choose an offset_ptr
//                     from the boost interprocess library to allow the
//                     use of this reverse iterator in shared memory for
//                     multi-process applications
//
//
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
//
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
//
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
template<typename blDataType,
         typename blDataPtr = blDataType*>

class blReverseIterator
{
public: // Iterator traits



    using iterator_category = std::random_access_iterator_tag;
    using value_type = blDataType;
    using difference_type = std::ptrdiff_t;
    using pointer = blDataPtr;
    using reference = blDataType&;



public: // Constructors and destructors



    // Default constructor

    blReverseIterator(const blDataPtr& ptr = blDataPtr(nullptr));



    // Constructor from a value

    blReverseIterator(blDataType& value);



    // Copy constructor

    blReverseIterator(const blReverseIterator<blDataType,blDataPtr>& reverseIterator);



    // Destructor

    ~blReverseIterator();



public: // Public functions



    // Overloaded assignment operators

    blReverseIterator<blDataType,blDataPtr>&    operator=(const blReverseIterator<blDataType,blDataPtr>& reverseIterator);
    blReverseIterator<blDataType,blDataPtr>&    operator=(const blDataPtr& ptr);



    // Comparison operators

    bool                                        operator==(const blReverseIterator<blDataType,blDataPtr>& reverseIterator)const;
    bool                                        operator!=(const blReverseIterator<blDataType,blDataPtr>& reverseIterator)const;



    // Overloaded assignment operators

    blReverseIterator<blDataType,blDataPtr>&    operator+=(const ptrdiff_t& movement);
    blReverseIterator<blDataType,blDataPtr>&    operator-=(const ptrdiff_t& movement);
    blReverseIterator<blDataType,blDataPtr>&    operator++();
    blReverseIterator<blDataType,blDataPtr>&    operator--();
    blReverseIterator<blDataType,blDataPtr>     operator++(int);
    blReverseIterator<blDataType,blDataPtr>     operator--(int);
    blReverseIterator<blDataType,blDataPtr>     operator+(const int& movement)const;
    blReverseIterator<blDataType,blDataPtr>     operator-(const int& movement)const;



    // Operator used to "subtract"
    // two pointers (it gives the
    // distance)

    std::ptrdiff_t                              operator-(const blReverseIterator<blDataType,blDataPtr>& reverseIterator)const;



    // Base operator

    blReverseIterator<blDataType,blDataPtr>     base();



    // Overloaded referencing/dereferencing
    // operators

    blDataType&                                 operator*();
    const blDataType&                           operator*()const;
    blDataPtr                                   operator->();



    // Functions to get the
    // raw pointer

    const blDataPtr&                            getPtr()const;



private: // Private variables



    // The actual raw pointer

    blDataPtr                                   m_ptr;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>::blReverseIterator(const blDataPtr& ptr)
{
    m_ptr = blDataPtr(ptr);
}



template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>::blReverseIterator(blDataType& value)
{
    m_ptr = blDataPtr(&value);
}



template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>::blReverseIterator(const blReverseIterator<blDataType,blDataPtr>& reverseIterator)
{
    this->m_ptr = reverseIterator.getPtr();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>::~blReverseIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Assignment operators
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>& blReverseIterator<blDataType,blDataPtr>::operator=(const blReverseIterator<blDataType,blDataPtr>& reverseIterator)
{
    this->m_ptr = reverseIterator.getPtr();

    return (*this);
}



template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>& blReverseIterator<blDataType,blDataPtr>::operator=(const blDataPtr& ptr)
{
    this->m_ptr = blDataPtr(ptr);

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Comparison operators
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline bool blReverseIterator<blDataType,blDataPtr>::operator==(const blReverseIterator<blDataType,blDataPtr>& reverseIterator)const
{
    return this->m_ptr == reverseIterator.getPtr();
}



template<typename blDataType,
         typename blDataPtr>

inline bool blReverseIterator<blDataType,blDataPtr>::operator!=(const blReverseIterator<blDataType,blDataPtr>& reverseIterator)const
{
    return this->m_ptr != reverseIterator.getPtr();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>& blReverseIterator<blDataType,blDataPtr>::operator+=(const ptrdiff_t& movement)
{
    this->m_ptr -= movement;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>& blReverseIterator<blDataType,blDataPtr>::operator-=(const ptrdiff_t& movement)
{
    this->m_ptr += movement;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>& blReverseIterator<blDataType,blDataPtr>::operator++()
{
    --this->m_ptr;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr>& blReverseIterator<blDataType,blDataPtr>::operator--()
{
    ++this->m_ptr;

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr> blReverseIterator<blDataType,blDataPtr>::operator++(int)
{
    auto temp(*this);

    --this->m_ptr;

    return temp;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr> blReverseIterator<blDataType,blDataPtr>::operator--(int)
{
    auto temp(*this);

    ++this->m_ptr;

    return temp;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr> blReverseIterator<blDataType,blDataPtr>::operator+(const int& movement)const
{
    auto advancedIterator = (*this);

    advancedIterator += movement;

    return advancedIterator;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr> blReverseIterator<blDataType,blDataPtr>::operator-(const int& movement)const
{
    auto advancedIterator = (*this);

    advancedIterator -= movement;

    return advancedIterator;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline ptrdiff_t blReverseIterator<blDataType,blDataPtr>::operator-(const blReverseIterator<blDataType,blDataPtr>& reverseIterator)const
{
    return std::distance(reverseIterator.getPtr(),m_ptr);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blReverseIterator<blDataType,blDataPtr> blReverseIterator<blDataType,blDataPtr>::base()
{
    auto basePtr = m_ptr;

    --basePtr;

    return blReverseIterator<blDataType,blDataPtr>(basePtr);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blDataType& blReverseIterator<blDataType,blDataPtr>::operator*()
{
    return *m_ptr;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline const blDataType& blReverseIterator<blDataType,blDataPtr>::operator*()const
{
    return *m_ptr;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blDataPtr blReverseIterator<blDataType,blDataPtr>::operator->()
{
    return m_ptr;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline const blDataPtr& blReverseIterator<blDataType,blDataPtr>::getPtr()const
{
    return m_ptr;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Output reverse iterator address to output stream
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline std::ostream& operator<<(std::ostream& os,const blReverseIterator<blDataType,blDataPtr>& reverseIterator)
{
    os << reverseIterator.getPtr();

    return os;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_REVERSEITERATOR_HPP
