#ifndef BL_ROIREVERSEITERATOR_HPP
#define BL_ROIREVERSEITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blRoiReverseIterator.hpp
// CLASS:           blRoiReverseIterator
// BASE CLASS:      blRoiIterator
//
//
//
// PURPOSE:         -- Based on blRoiIterator, this iterator moves
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
// DEPENDENCIES:    -- blRoiIterator
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

// Based on blRoiIterator

#include "blRoiIterator.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blBufferType>
class blRoiReverseIterator : public blRoiIterator<blBufferType>
{
public: // Public typedefs



    typedef typename blRoiIterator<blBufferType>::blDataType        blDataType;
    typedef typename blRoiIterator<blBufferType>::blDataTypePtr     blDataTypePtr;



public: // Constructors and destructors



    // No default constructor

    blRoiReverseIterator() = delete;



    // Constructor from a buffer reference

    blRoiReverseIterator(blBufferType& buffer,
                         const std::ptrdiff_t& dataIndex,
                         const std::ptrdiff_t& maxNumberOfCirculations);



    // Copy constructor

    blRoiReverseIterator(const blRoiReverseIterator<blBufferType>& roiIterator);



    // Destructor

    ~blRoiReverseIterator();



public: // Public functions



    // Function returning the
    // iterator's base

    blRoiReverseIterator<blBufferType>          base();



public: // Overloaded public functions



    // Arithmetic operators

    blRoiReverseIterator<blBufferType>&         operator+=(const int& movement);
    blRoiReverseIterator<blBufferType>&         operator-=(const int& movement);
    blRoiReverseIterator<blBufferType>&         operator++();
    blRoiReverseIterator<blBufferType>&         operator--();
    blRoiReverseIterator<blBufferType>          operator++(int);
    blRoiReverseIterator<blBufferType>          operator--(int);
    blRoiReverseIterator<blBufferType>          operator+(const int& movement)const;
    blRoiReverseIterator<blBufferType>          operator-(const int& movement)const;

    std::ptrdiff_t                              operator-(const blRoiReverseIterator<blBufferType>& roiReverseIterator)const;



    // Function used to get the actual
    // distance in the buffer between
    // this iterator and another one

    std::ptrdiff_t                              actualDistanceInTheBufferFromAnotherIterator(const blRoiReverseIterator<blBufferType>& iterator);



    // Function used to advance the
    // iterator if the user doesn't
    // want to use the the overload
    // arithmetic operators

    blRoiReverseIterator<blBufferType>&         advance(const std::ptrdiff_t& movement);



    // Function used to advance
    // the iterator by number of
    // circulations
    // For example if advancing
    // circulations by 1, the iterator
    // is advanced by m_buffer.size()
    // of if advancing by -2, the
    // iterator is advanced by
    // -2*m_buffer.size()

    blRoiReverseIterator<blBufferType>&         advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy);



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
inline blRoiReverseIterator<blBufferType>::blRoiReverseIterator(blBufferType& buffer,
                                                                const std::ptrdiff_t& dataIndex,
                                                                const std::ptrdiff_t& maxNumberOfCirculations)
                                                                : blRoiIterator<blBufferType>(buffer,
                                                                                              buffer.roi().size() - 1 - dataIndex,
                                                                                              maxNumberOfCirculations)
{
}



template<typename blBufferType>
inline blRoiReverseIterator<blBufferType>::blRoiReverseIterator(const blRoiReverseIterator<blBufferType>& roiIterator)
                                                                : blRoiIterator<blBufferType>(roiIterator)
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blBufferType>
inline blRoiReverseIterator<blBufferType>::~blRoiReverseIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function returning the iterator's base
//-------------------------------------------------------------------
template<typename blBufferType>
inline blRoiReverseIterator<blBufferType> blRoiReverseIterator<blBufferType>::base()
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
inline blRoiReverseIterator<blBufferType>& blRoiReverseIterator<blBufferType>::operator+=(const int& movement)
{
    this->m_dataIndex -= movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blRoiReverseIterator<blBufferType>& blRoiReverseIterator<blBufferType>::operator-=(const int& movement)
{
    this->m_dataIndex += movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blRoiReverseIterator<blBufferType>& blRoiReverseIterator<blBufferType>::operator++()
{
    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blRoiReverseIterator<blBufferType>& blRoiReverseIterator<blBufferType>::operator--()
{
    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blRoiReverseIterator<blBufferType> blRoiReverseIterator<blBufferType>::operator++(int)
{
    auto temp(*this);

    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType>
inline blRoiReverseIterator<blBufferType> blRoiReverseIterator<blBufferType>::operator--(int)
{
    auto temp(*this);

    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType>
inline blRoiReverseIterator<blBufferType> blRoiReverseIterator<blBufferType>::operator+(const int& movement)const
{
    auto temp(*this);

    temp -= movement;

    return temp;
}



template<typename blBufferType>
inline blRoiReverseIterator<blBufferType> blRoiReverseIterator<blBufferType>::operator-(const int& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blBufferType>
inline std::ptrdiff_t blRoiReverseIterator<blBufferType>::operator-(const blRoiReverseIterator<blBufferType>& roiReverseIterator)const
{
    return ( roiReverseIterator.getDataIndex() - this->m_dataIndex);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator if the user doesn't
// want to use the the overload arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType>
inline blRoiReverseIterator<blBufferType>& blRoiReverseIterator<blBufferType>::advance(const std::ptrdiff_t& movement)
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
inline blRoiReverseIterator<blBufferType>& blRoiReverseIterator<blBufferType>::advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy)
{
    this->m_dataIndex -= numberOfCirculationsToAdvanceTheIteratorBy * this->m_buffer.roi().size();

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
inline std::ptrdiff_t blRoiReverseIterator<blBufferType>::actualDistanceInTheBufferFromAnotherIterator(const blRoiReverseIterator<blBufferType>& iterator)
{
    return (
            static_cast<std::ptrdiff_t>( circ_index(iterator.getDataIndex(),iterator.getBufferReference().roi().size()) ) -
            static_cast<std::ptrdiff_t>( circ_index(this->m_dataIndex,this->m_buffer.roi().size()) )
           );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to return the
// total amount of iterated length
// including circulations
//-------------------------------------------------------------------
template<typename blBufferType>
inline std::ptrdiff_t blRoiReverseIterator<blBufferType>::getTotalIteratedLength()const
{
    return this->m_startIndex - this->m_dataIndex;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_ROIREVERSEITERATOR_HPP
