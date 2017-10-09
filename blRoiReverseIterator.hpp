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
template<typename blBufferType,
         typename blBufferPtr = blBufferType*>

class blRoiReverseIterator : public blRoiIterator<blBufferType,blBufferPtr>
{
public: // Public typedefs



    using blDataType = typename blRoiIterator<blBufferType,blBufferPtr>::blDataType;
    using blDataPtr = typename blRoiIterator<blBufferType,blBufferPtr>::blDataPtr;



public: // Constructors and destructors



    // Default constructor

    blRoiReverseIterator(const blBufferPtr& bufferPtr = blBufferPtr(nullptr),
                         const std::ptrdiff_t& dataIndex = std::ptrdiff_t(0),
                         const std::ptrdiff_t& maxNumberOfCirculations = std::ptrdiff_t(1));



    // Copy constructor

    blRoiReverseIterator(const blRoiReverseIterator<blBufferType,blBufferPtr>& roiReverseIterator);



    // Destructor

    ~blRoiReverseIterator();



public: // Public functions



    // Function returning the
    // iterator's base

    blRoiReverseIterator<blBufferType,blBufferPtr>          base();



public: // Overloaded public functions



    // Arithmetic operators

    blRoiReverseIterator<blBufferType,blBufferPtr>&         operator+=(const int& movement);
    blRoiReverseIterator<blBufferType,blBufferPtr>&         operator-=(const int& movement);
    blRoiReverseIterator<blBufferType,blBufferPtr>&         operator++();
    blRoiReverseIterator<blBufferType,blBufferPtr>&         operator--();
    blRoiReverseIterator<blBufferType,blBufferPtr>          operator++(int);
    blRoiReverseIterator<blBufferType,blBufferPtr>          operator--(int);
    blRoiReverseIterator<blBufferType,blBufferPtr>          operator+(const int& movement)const;
    blRoiReverseIterator<blBufferType,blBufferPtr>          operator-(const int& movement)const;

    std::ptrdiff_t                                          operator-(const blRoiReverseIterator<blBufferType,blBufferPtr>& roiReverseIterator)const;



    // Function used to get the actual
    // distance in the buffer between
    // this iterator and another one

    std::ptrdiff_t                                          actualDistanceInTheBufferFromAnotherIterator(const blRoiReverseIterator<blBufferType,blBufferPtr>& iterator);



    // Function used to advance the
    // iterator if the user doesn't
    // want to use the the overload
    // arithmetic operators

    blRoiReverseIterator<blBufferType,blBufferPtr>&         advance(const std::ptrdiff_t& movement);



    // Function used to advance
    // the iterator by number of
    // circulations
    // For example if advancing
    // circulations by 1, the iterator
    // is advanced by m_bufferPtr->size()
    // of if advancing by -2, the
    // iterator is advanced by
    // -2*m_bufferPtr->size()

    blRoiReverseIterator<blBufferType,blBufferPtr>&         advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy);



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

inline blRoiReverseIterator<blBufferType,blBufferPtr>::blRoiReverseIterator(const blBufferPtr& bufferPtr,
                                                                            const std::ptrdiff_t& dataIndex,
                                                                            const std::ptrdiff_t& maxNumberOfCirculations)
                                                                            : blRoiIterator<blBufferType,blBufferPtr>(bufferPtr,
                                                                                                                      dataIndex,
                                                                                                                      maxNumberOfCirculations)
{
    if(bufferPtr)
    {
        this->setDataIndex(bufferPtr->roi().size() - 1 - dataIndex);
    }
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr>::blRoiReverseIterator(const blRoiReverseIterator<blBufferType,blBufferPtr>& roiIterator)
                                                                            : blRoiIterator<blBufferType,blBufferPtr>(roiIterator)
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr>::~blRoiReverseIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function returning the iterator's base
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr> blRoiReverseIterator<blBufferType,blBufferPtr>::base()
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

inline blRoiReverseIterator<blBufferType,blBufferPtr>& blRoiReverseIterator<blBufferType,blBufferPtr>::operator+=(const int& movement)
{
    this->m_dataIndex -= movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr>& blRoiReverseIterator<blBufferType,blBufferPtr>::operator-=(const int& movement)
{
    this->m_dataIndex += movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr>& blRoiReverseIterator<blBufferType,blBufferPtr>::operator++()
{
    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr>& blRoiReverseIterator<blBufferType,blBufferPtr>::operator--()
{
    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr> blRoiReverseIterator<blBufferType,blBufferPtr>::operator++(int)
{
    auto temp(*this);

    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr> blRoiReverseIterator<blBufferType,blBufferPtr>::operator--(int)
{
    auto temp(*this);

    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr> blRoiReverseIterator<blBufferType,blBufferPtr>::operator+(const int& movement)const
{
    auto temp(*this);

    temp -= movement;

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr> blRoiReverseIterator<blBufferType,blBufferPtr>::operator-(const int& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline std::ptrdiff_t blRoiReverseIterator<blBufferType,blBufferPtr>::operator-(const blRoiReverseIterator<blBufferType,blBufferPtr>& roiReverseIterator)const
{
    return ( roiReverseIterator.getDataIndex() - this->m_dataIndex);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator if the user doesn't
// want to use the the overload arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blRoiReverseIterator<blBufferType,blBufferPtr>& blRoiReverseIterator<blBufferType,blBufferPtr>::advance(const std::ptrdiff_t& movement)
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

inline blRoiReverseIterator<blBufferType,blBufferPtr>& blRoiReverseIterator<blBufferType,blBufferPtr>::advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy)
{
    this->m_dataIndex -= numberOfCirculationsToAdvanceTheIteratorBy * this->m_bufferPtr->roi().size();

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

inline std::ptrdiff_t blRoiReverseIterator<blBufferType,blBufferPtr>::actualDistanceInTheBufferFromAnotherIterator(const blRoiReverseIterator<blBufferType,blBufferPtr>& iterator)
{
    return (
            static_cast<std::ptrdiff_t>( circ_index(iterator.getDataIndex(),iterator.getBufferReference().roi().size()) ) -
            static_cast<std::ptrdiff_t>( circ_index(this->m_dataIndex,this->m_bufferPtr->roi().size()) )
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

inline std::ptrdiff_t blRoiReverseIterator<blBufferType,blBufferPtr>::getTotalIteratedLength()const
{
    return this->m_startIndex - this->m_dataIndex;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_ROIREVERSEITERATOR_HPP
