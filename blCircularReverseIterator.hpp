#ifndef BL_CIRCULARREVERSEITERATOR_HPP
#define BL_CIRCULARREVERSEITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blCircularReverseIterator.hpp
// CLASS:           blCircularReverseIterator
// BASE CLASS:      blCircularReverseIterator
//
//
//
// PURPOSE:         -- Based on blCircularReverseIterator, this iterator moves
//                     in the opposite direction (backwards)
//
//
//
// AUTHOR:          Vincenzo Barbato
//                  http://www.barbatolabs.com
//                  navyenzo@gmail.com
//
//
//
// LISENSE:         MIT-LICENSE
//                  http://www.opensource.org/licenses/mit-license.php
//
//
//
// DEPENDENCIES:    -- blCircularIterator
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

// Based on blCircularReverseIterator

#include "blCircularIterator.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blBufferType>
class blCircularReverseIterator : public blCircularIterator<blBufferType>
{
public: // Constructors and destructors



    // No default constructor

    blCircularReverseIterator() = delete;



    // Constructor from a buffer reference

    blCircularReverseIterator(blBufferType& buffer,
                              const std::ptrdiff_t& dataIndex,
                              const std::ptrdiff_t& maxNumberOfCirculations);



    // Copy constructor

    blCircularReverseIterator(const blCircularReverseIterator<blBufferType>& roiIterator);



    // Destructor

    ~blCircularReverseIterator();



public: // Public functions



    // Function returning the
    // iterator's base

    blCircularReverseIterator<blBufferType>     base();



public: // Overloaded public functions



    // Arithmetic operators

    blCircularReverseIterator<blBufferType>&    operator+=(const int& movement);
    blCircularReverseIterator<blBufferType>&    operator-=(const int& movement);
    blCircularReverseIterator<blBufferType>&    operator++();
    blCircularReverseIterator<blBufferType>&    operator--();
    blCircularReverseIterator<blBufferType>     operator++(int);
    blCircularReverseIterator<blBufferType>     operator--(int);
    blCircularReverseIterator<blBufferType>     operator+(const int& movement)const;
    blCircularReverseIterator<blBufferType>     operator-(const int& movement)const;

    std::ptrdiff_t                              operator-(const blCircularReverseIterator<blBufferType>& circularReverseIterator)const;



    // Function used to get the actual
    // distance in the buffer between
    // this iterator and another one

    std::ptrdiff_t                              actualDistanceInTheBufferFromAnotherIterator(const blCircularReverseIterator<blBufferType>& iterator);



    // Function used to advance the
    // iterator if the user doesn't
    // want to use the the overload
    // arithmetic operators

    blCircularReverseIterator<blBufferType>&    advance(const std::ptrdiff_t& movement);



    // Function used to advance
    // the iterator by number of
    // circulations
    // For example if advancing
    // circulations by 1, the iterator
    // is advanced by m_buffer.size()
    // of if advancing by -2, the
    // iterator is advanced by
    // -2*m_buffer.size()

    blCircularReverseIterator<blBufferType>&    advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy);



    // Function used to return the
    // total amount of iterated length
    // including circulations

    std::ptrdiff_t                              getTotalIteratedLength()const;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularReverseIterator<blBufferType>::blCircularReverseIterator(blBufferType& buffer,
                                                                          const std::ptrdiff_t& dataIndex,
                                                                          const std::ptrdiff_t& maxNumberOfCirculations)
                                                                          : blCircularIterator<blBufferType>(buffer,
                                                                                                             buffer.size() - 1 - dataIndex,
                                                                                                             maxNumberOfCirculations)
{
}



template<typename blBufferType>
inline blCircularReverseIterator<blBufferType>::blCircularReverseIterator(const blCircularReverseIterator<blBufferType>& roiIterator)
                                                                          : blCircularIterator<blBufferType>(roiIterator)
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularReverseIterator<blBufferType>::~blCircularReverseIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function returning the iterator's base
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularReverseIterator<blBufferType> blCircularReverseIterator<blBufferType>::base()
{
    auto baseIterator = (*this);

    ++baseIterator;

    return baseIterator;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularReverseIterator<blBufferType>& blCircularReverseIterator<blBufferType>::operator+=(const int& movement)
{
    this->m_dataIndex -= movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blCircularReverseIterator<blBufferType>& blCircularReverseIterator<blBufferType>::operator-=(const int& movement)
{
    this->m_dataIndex += movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blCircularReverseIterator<blBufferType>& blCircularReverseIterator<blBufferType>::operator++()
{
    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blCircularReverseIterator<blBufferType>& blCircularReverseIterator<blBufferType>::operator--()
{
    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blCircularReverseIterator<blBufferType> blCircularReverseIterator<blBufferType>::operator++(int)
{
    auto temp(*this);

    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType>
inline blCircularReverseIterator<blBufferType> blCircularReverseIterator<blBufferType>::operator--(int)
{
    auto temp(*this);

    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType>
inline blCircularReverseIterator<blBufferType> blCircularReverseIterator<blBufferType>::operator+(const int& movement)const
{
    auto temp(*this);

    temp -= movement;

    return temp;
}



template<typename blBufferType>
inline blCircularReverseIterator<blBufferType> blCircularReverseIterator<blBufferType>::operator-(const int& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blBufferType>
inline std::ptrdiff_t blCircularReverseIterator<blBufferType>::operator-(const blCircularReverseIterator<blBufferType>& circularReverseIterator)const
{
    return ( circularReverseIterator.getDataIndex() - this->m_dataIndex);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator if the user doesn't
// want to use the the overload arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularReverseIterator<blBufferType>& blCircularReverseIterator<blBufferType>::advance(const std::ptrdiff_t& movement)
{
    this->m_dataIndex -= movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator by number of
// circulations.  For example if advancing circulations
// by 1, the iterator is advanced by m_buffer.size(), or
// if advancing by -2, the iterator is advanced by
// -2*m_buffer.size()
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularReverseIterator<blBufferType>& blCircularReverseIterator<blBufferType>::advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy)
{
    this->m_dataIndex -= numberOfCirculationsToAdvanceTheIteratorBy * this->m_buffer.size();

    this->updateCurrentNumberOfCirculations();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the actual
// distance in the buffer between
// this iterator and another one
//-------------------------------------------------------------------
template<typename blBufferType>
inline std::ptrdiff_t blCircularReverseIterator<blBufferType>::actualDistanceInTheBufferFromAnotherIterator(const blCircularReverseIterator<blBufferType>& iterator)
{
    return (
            static_cast<std::ptrdiff_t>( circ_index(iterator.getDataIndex(),iterator.getBufferReference().size()) ) -
            static_cast<std::ptrdiff_t>( circ_index(this->m_dataIndex,this->m_buffer.size()) )
           );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to return the
// total amount of iterated length
// including circulations
//-------------------------------------------------------------------
template<typename blBufferType>
inline std::ptrdiff_t blCircularReverseIterator<blBufferType>::getTotalIteratedLength()const
{
    return this->m_startIndex - this->m_dataIndex;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_CIRCULARREVERSEITERATOR_HPP
