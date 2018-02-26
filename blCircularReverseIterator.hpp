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
template<typename blBufferType,
         typename blBufferPtr = blBufferType*>

class blCircularReverseIterator : public blCircularIterator<blBufferType,blBufferPtr>
{
public: // Constructors and destructors



    // Default constructor

    blCircularReverseIterator(const blBufferPtr& bufferPtr = blBufferPtr(nullptr),
                              const std::ptrdiff_t& dataIndex = std::ptrdiff_t(0),
                              const std::ptrdiff_t& maxNumberOfCirculations = std::ptrdiff_t(1));



    // Copy constructor

    blCircularReverseIterator(const blCircularReverseIterator<blBufferType,blBufferPtr>& reverseIterator);



    // Destructor

    ~blCircularReverseIterator();



public: // Public functions



    // Function returning the
    // iterator's base

    blCircularReverseIterator<blBufferType,blBufferPtr>     base();



public: // Overloaded public functions



    // Arithmetic operators

    blCircularReverseIterator<blBufferType,blBufferPtr>&    operator+=(const int& movement);
    blCircularReverseIterator<blBufferType,blBufferPtr>&    operator-=(const int& movement);
    blCircularReverseIterator<blBufferType,blBufferPtr>&    operator++();
    blCircularReverseIterator<blBufferType,blBufferPtr>&    operator--();
    blCircularReverseIterator<blBufferType,blBufferPtr>     operator++(int);
    blCircularReverseIterator<blBufferType,blBufferPtr>     operator--(int);
    blCircularReverseIterator<blBufferType,blBufferPtr>     operator+(const int& movement)const;
    blCircularReverseIterator<blBufferType,blBufferPtr>     operator-(const int& movement)const;

    std::ptrdiff_t                                          operator-(const blCircularReverseIterator<blBufferType,blBufferPtr>& circularReverseIterator)const;



    // Function used to get the actual
    // distance in the buffer between
    // this iterator and another one

    std::ptrdiff_t                                          actualDistanceInTheBufferFromAnotherIterator(const blCircularReverseIterator<blBufferType,blBufferPtr>& iterator);



    // Function used to advance the
    // iterator if the user doesn't
    // want to use the the overload
    // arithmetic operators

    blCircularReverseIterator<blBufferType,blBufferPtr>&    advance(const std::ptrdiff_t& movement);



    // Function used to advance
    // the iterator by number of
    // circulations
    // For example if advancing
    // circulations by 1, the iterator
    // is advanced by m_bufferPtr->size()
    // of if advancing by -2, the
    // iterator is advanced by
    // -2*m_bufferPtr->size()

    blCircularReverseIterator<blBufferType,blBufferPtr>&    advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy);



    // Function used to return the
    // total amount of iterated length
    // including circulations

    std::ptrdiff_t                                          getTotalIteratedLength()const;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr>::blCircularReverseIterator(const blBufferPtr& bufferPtr,
                                                                                      const std::ptrdiff_t& dataIndex,
                                                                                      const std::ptrdiff_t& maxNumberOfCirculations)
                                                                                      : blCircularIterator<blBufferType,blBufferPtr>(bufferPtr,
                                                                                                                                     dataIndex,
                                                                                                                                     maxNumberOfCirculations)
{
    if(bufferPtr)
    {
        this->setDataIndex(bufferPtr->size() - 1 - dataIndex);
    }
}



template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr>::blCircularReverseIterator(const blCircularReverseIterator<blBufferType,blBufferPtr>& reverseIterator)
                                                                                      : blCircularIterator<blBufferType,blBufferPtr>(reverseIterator)
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr>::~blCircularReverseIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function returning the iterator's base
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr> blCircularReverseIterator<blBufferType,blBufferPtr>::base()
{
    auto baseIterator = (*this);

    ++baseIterator;

    return baseIterator;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr>& blCircularReverseIterator<blBufferType,blBufferPtr>::operator+=(const int& movement)
{
    this->m_dataIndex -= movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr>& blCircularReverseIterator<blBufferType,blBufferPtr>::operator-=(const int& movement)
{
    this->m_dataIndex += movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr>& blCircularReverseIterator<blBufferType,blBufferPtr>::operator++()
{
    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr>& blCircularReverseIterator<blBufferType,blBufferPtr>::operator--()
{
    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr> blCircularReverseIterator<blBufferType,blBufferPtr>::operator++(int)
{
    auto temp(*this);

    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr> blCircularReverseIterator<blBufferType,blBufferPtr>::operator--(int)
{
    auto temp(*this);

    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr> blCircularReverseIterator<blBufferType,blBufferPtr>::operator+(const int& movement)const
{
    auto temp(*this);

    temp -= movement;

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr> blCircularReverseIterator<blBufferType,blBufferPtr>::operator-(const int& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline std::ptrdiff_t blCircularReverseIterator<blBufferType,blBufferPtr>::operator-(const blCircularReverseIterator<blBufferType,blBufferPtr>& circularReverseIterator)const
{
    return ( circularReverseIterator.getDataIndex() - this->m_dataIndex);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator if the user doesn't
// want to use the the overload arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr>& blCircularReverseIterator<blBufferType,blBufferPtr>::advance(const std::ptrdiff_t& movement)
{
    this->m_dataIndex -= movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator by number of
// circulations.  For example if advancing circulations
// by 1, the iterator is advanced by m_bufferPtr->size(), or
// if advancing by -2, the iterator is advanced by
// -2*m_bufferPtr->size()
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blCircularReverseIterator<blBufferType,blBufferPtr>& blCircularReverseIterator<blBufferType,blBufferPtr>::advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy)
{
    this->m_dataIndex -= numberOfCirculationsToAdvanceTheIteratorBy * this->m_bufferPtr->size();

    this->updateCurrentNumberOfCirculations();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the actual
// distance in the buffer between
// this iterator and another one
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline std::ptrdiff_t blCircularReverseIterator<blBufferType,blBufferPtr>::actualDistanceInTheBufferFromAnotherIterator(const blCircularReverseIterator<blBufferType,blBufferPtr>& iterator)
{
    return (
            static_cast<std::ptrdiff_t>( circ_index(iterator.getDataIndex(),iterator.getBufferReference().size()) ) -
            static_cast<std::ptrdiff_t>( circ_index(this->m_dataIndex,this->m_bufferPtr->size()) )
           );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to return the
// total amount of iterated length
// including circulations
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline std::ptrdiff_t blCircularReverseIterator<blBufferType,blBufferPtr>::getTotalIteratedLength()const
{
    return this->m_startIndex - this->m_dataIndex;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_CIRCULARREVERSEITERATOR_HPP
