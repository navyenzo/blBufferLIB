#ifndef BL_ROIITERATOR_HPP
#define BL_ROIITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blRoiIterator.hpp
// CLASS:           blRoiIterator
// BASE CLASS:      blCircularIterator
//
//
//
// PURPOSE:         -- Based on blCircularIterator, this iterator is
//                     for buffers that define a Region Of Interest (ROI)
//                     with the following members defined in the buffer:
//
//                     -- member variables:
//
//                        -- "roi" which is of type: blDimensionalProperties
//
//                     -- member functions:
//
//                        -- blDataType& roi_at(const blIntegerType& dataIndex)
//
//                        -- const blDataType& roi_at(const blIntegerType& dataIndex)const
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
//
//                  -- The buffer type has to define the above
//                     mentioned "roi_at" functions
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

// Based on blCircularIterator

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
class blRoiIterator : public blCircularIterator<blBufferType>
{
public: // Public typedefs



    typedef typename blCircularIterator<blBufferType>::blDataType       blDataType;
    typedef typename blCircularIterator<blBufferType>::blDataTypePtr    blDataTypePtr;



public: // Constructors and destructors



    // No default constructor

    blRoiIterator() = delete;



    // Constructor from a buffer reference

    blRoiIterator(blBufferType& buffer,
                  const std::ptrdiff_t& dataIndex,
                  const std::ptrdiff_t& maxNumberOfCirculations);



    // Copy constructor

    blRoiIterator(const blRoiIterator<blBufferType>& roiIterator);



    // Destructor

    ~blRoiIterator();



public: // Overloaded public functions



    // Function returning the
    // iterator's base

    blRoiIterator<blBufferType>                 base();



    // Functions used to know how many
    // contiguous spots (in terms of
    // number of data points and in terms
    // of bytes) are left before
    // reaching the end of the buffer if
    // one were to write contiguous data
    // from the current buffer index without
    // circling back around

    std::size_t                                 remainingContiguousSpots()const;
    std::size_t                                 remainingContiguousBytes()const;



    // Arithmetic operators

    blRoiIterator<blBufferType>&                operator+=(const int& movement);
    blRoiIterator<blBufferType>&                operator-=(const int& movement);
    blRoiIterator<blBufferType>&                operator++();
    blRoiIterator<blBufferType>&                operator--();
    blRoiIterator<blBufferType>                 operator++(int);
    blRoiIterator<blBufferType>                 operator--(int);
    blRoiIterator<blBufferType>                 operator+(const int& movement)const;
    blRoiIterator<blBufferType>                 operator-(const int& movement)const;



    // Function used to get the actual
    // distance in the buffer between
    // this iterator and another one

    std::ptrdiff_t                              actualDistanceInTheBufferFromAnotherIterator(const blRoiIterator<blBufferType>& iterator);



    // Function used to advance the
    // iterator if the user doesn't
    // want to use the the overload
    // arithmetic operators

    blRoiIterator<blBufferType>&                advance(const std::ptrdiff_t& movement);



    // Function used to advance
    // the iterator by number of
    // circulations
    // For example if advancing
    // circulations by 1, the iterator
    // is advanced by m_buffer.size()
    // of if advancing by -2, the
    // iterator is advanced by
    // -2*m_buffer.size()

    blRoiIterator<blBufferType>&                advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy);



    // Functions used to get a pointer
    // or reference to the indexed data
    // point in the buffer

    blDataTypePtr                               getPointerToIndexedDataPoint();
    const blDataTypePtr                         getPointerToIndexedDataPoint()const;

    blDataType&                                 getReferenceToIndexedDataPoint();
    const blDataType&                           getReferenceToIndexedDataPoint()const;



    // Overloaded referencing/dereferencing
    // operators

    // Dereferencing operators

    blDataType&                                 operator*();
    const blDataType&                           operator*()const;
    blDataTypePtr                               operator->();
    const blDataTypePtr                         operator->()const;



protected: // Protected functions



    // This function updates the current
    // number of circulations/cycles that
    // the iterator has gone through up
    // to this instant

    void                                        updateCurrentNumberOfCirculations();
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------
template<typename blBufferType>
inline blRoiIterator<blBufferType>::blRoiIterator(blBufferType& buffer,
                                                  const std::ptrdiff_t& dataIndex,
                                                  const std::ptrdiff_t& maxNumberOfCirculations)
                                                  : blCircularIterator<blBufferType>(buffer,
                                                                                     dataIndex,
                                                                                     maxNumberOfCirculations)
{
}



template<typename blBufferType>
inline blRoiIterator<blBufferType>::blRoiIterator(const blRoiIterator<blBufferType>& roiIterator)
                                                  : blCircularIterator<blBufferType>(roiIterator)
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blBufferType>
inline blRoiIterator<blBufferType>::~blRoiIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to update the current
// number of circulations/cycles that the
// iterator has gone through up to now
//-------------------------------------------------------------------
template<typename blBufferType>
inline void blRoiIterator<blBufferType>::updateCurrentNumberOfCirculations()
{
    this->m_currentNumberOfCirculations = (this->m_dataIndex - this->m_startIndex) / std::ptrdiff_t(this->m_buffer.roi().size());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function returning the iterator's base
//-------------------------------------------------------------------
template<typename blBufferType>
inline blRoiIterator<blBufferType> blRoiIterator<blBufferType>::base()
{
    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to know how many
// contiguous spots (in terms of
// number of data points and in terms
// of bytes) are left before
// reaching the end of the buffer if
// one were to write contiguous data
// from the current buffer index without
// circling back around
//-------------------------------------------------------------------
template<typename blBufferType>
inline std::size_t blRoiIterator<blBufferType>::remainingContiguousSpots()const
{
    return this->m_buffer.roi().size() - this->circ_index(this->m_dataIndex,this->m_buffer.roi().size());
}



template<typename blBufferType>
inline std::size_t blRoiIterator<blBufferType>::remainingContiguousBytes()const
{
    return sizeof(blDataType) * (this->m_buffer.roi().size() - circ_index(this->m_dataIndex,this->m_buffer.roi().size()));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overloaded Operators that let us use this class as
// a normal iterator in stl-like algorithms
//-------------------------------------------------------------------
template<typename blBufferType>
inline typename blRoiIterator<blBufferType>::blDataType& blRoiIterator<blBufferType>::operator*()
{
    return this->getReferenceToIndexedDataPoint();
}



template<typename blBufferType>
inline const typename blRoiIterator<blBufferType>::blDataType& blRoiIterator<blBufferType>::operator*()const
{
    return this->getReferenceToIndexedDataPoint();
}



template<typename blBufferType>
inline typename blRoiIterator<blBufferType>::blDataTypePtr blRoiIterator<blBufferType>::operator->()
{
    return this->getPointerToIndexedDataPoint();
}



template<typename blBufferType>
inline const typename blRoiIterator<blBufferType>::blDataTypePtr blRoiIterator<blBufferType>::operator->()const
{
    return this->getPointerToIndexedDataPoint();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator if the user doesn't
// want to use the the overload arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType>
inline blRoiIterator<blBufferType>& blRoiIterator<blBufferType>::advance(const std::ptrdiff_t& movement)
{
    this->m_dataIndex += movement;

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
inline blRoiIterator<blBufferType>& blRoiIterator<blBufferType>::advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy)
{
    this->m_dataIndex += numberOfCirculationsToAdvanceTheIteratorBy * this->m_buffer.roi().size();

    this->updateCurrentNumberOfCirculations();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get a reference or a
// pointer to the indexed data point in the
// buffer
//-------------------------------------------------------------------
template<typename blBufferType>
inline typename blRoiIterator<blBufferType>::blDataType& blRoiIterator<blBufferType>::getReferenceToIndexedDataPoint()
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
    {
        return this->m_buffer.roi_at(this->m_buffer.roi().size());
    }
    else
    {
        return this->m_buffer.circ_roi_at(this->m_dataIndex);
    }
}



template<typename blBufferType>
inline const typename blRoiIterator<blBufferType>::blDataType& blRoiIterator<blBufferType>::getReferenceToIndexedDataPoint()const
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
    {
        return this->m_buffer.roi_at(this->m_buffer.roi().size());
    }
    else
    {
        return this->m_buffer.circ_roi_at(this->m_dataIndex);
    }
}



template<typename blBufferType>
inline typename blRoiIterator<blBufferType>::blDataTypePtr blRoiIterator<blBufferType>::getPointerToIndexedDataPoint()
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
    {
        return &this->m_buffer.roi_at(this->m_buffer.roi().size());
    }
    else
    {
        return &this->m_buffer.circ_roi_at(this->m_dataIndex);
    }
}



template<typename blBufferType>
inline const typename blRoiIterator<blBufferType>::blDataTypePtr blRoiIterator<blBufferType>::getPointerToIndexedDataPoint()const
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
    {
        return &this->m_buffer.roi_at(this->m_buffer.roi().size());
    }
    else
    {
        return &this->m_buffer.circ_roi_at(this->m_dataIndex);
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType>
inline blRoiIterator<blBufferType>& blRoiIterator<blBufferType>::operator+=(const int& movement)
{
    this->m_dataIndex += movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blRoiIterator<blBufferType>& blRoiIterator<blBufferType>::operator-=(const int& movement)
{
    this->m_dataIndex -= movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blRoiIterator<blBufferType>& blRoiIterator<blBufferType>::operator++()
{
    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blRoiIterator<blBufferType>& blRoiIterator<blBufferType>::operator--()
{
    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blRoiIterator<blBufferType> blRoiIterator<blBufferType>::operator++(int)
{
    auto temp(*this);

    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType>
inline blRoiIterator<blBufferType> blRoiIterator<blBufferType>::operator--(int)
{
    auto temp(*this);

    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType>
inline blRoiIterator<blBufferType> blRoiIterator<blBufferType>::operator+(const int& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blBufferType>
inline blRoiIterator<blBufferType> blRoiIterator<blBufferType>::operator-(const int& movement)const
{
    auto temp(*this);

    temp -= movement;

    return temp;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the actual
// distance in the buffer between
// this iterator and another one
//-------------------------------------------------------------------
template<typename blBufferType>
inline std::ptrdiff_t blRoiIterator<blBufferType>::actualDistanceInTheBufferFromAnotherIterator(const blRoiIterator<blBufferType>& iterator)
{
    return (
            static_cast<std::ptrdiff_t>( circ_index(this->m_dataIndex,this->m_buffer.roi().size()) ) -
            static_cast<std::ptrdiff_t>( circ_index(iterator.getDataIndex(),iterator.getBufferReference().roi().size()) )
           );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_ROIITERATOR_HPP
