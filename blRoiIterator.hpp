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
template<typename blBufferType,
         typename blBufferPtr = blBufferType*>

class blRoiIterator : public blCircularIterator<blBufferType,blBufferPtr>
{
public: // Public typedefs



    using blDataType = typename blCircularIterator<blBufferType,blBufferPtr>::blDataType;
    using blDataPtr = typename blCircularIterator<blBufferType,blBufferPtr>::blDataPtr;



public: // Constructors and destructors



    // Default constructor

    blRoiIterator(const blBufferPtr& bufferPtr = blBufferPtr(nullptr),
                  const std::ptrdiff_t& dataIndex = std::ptrdiff_t(0),
                  const std::ptrdiff_t& maxNumberOfCirculations = std::ptrdiff_t(1));



    // Copy constructor

    blRoiIterator(const blRoiIterator<blBufferType,blBufferPtr>& roiIterator);



    // Destructor

    ~blRoiIterator();



public: // Overloaded public functions



    // Function returning the
    // iterator's base

    blRoiIterator<blBufferType,blBufferPtr>                 base();



    // Comparator operators

    bool                                                    operator==(const blRoiIterator<blBufferType,blBufferPtr>& roiIterator)const;
    bool                                                    operator!=(const blRoiIterator<blBufferType,blBufferPtr>& roiIterator)const;



    // Functions used to know how many
    // contiguous spots (in terms of
    // number of data points and in terms
    // of bytes) are left before
    // reaching the end of the buffer if
    // one were to write contiguous data
    // from the current buffer index without
    // circling back around

    std::size_t                                             remainingContiguousSpots()const;
    std::size_t                                             remainingContiguousBytes()const;



    // Arithmetic operators

    blRoiIterator<blBufferType,blBufferPtr>&                operator+=(const int& movement);
    blRoiIterator<blBufferType,blBufferPtr>&                operator-=(const int& movement);
    blRoiIterator<blBufferType,blBufferPtr>&                operator++();
    blRoiIterator<blBufferType,blBufferPtr>&                operator--();
    blRoiIterator<blBufferType,blBufferPtr>                 operator++(int);
    blRoiIterator<blBufferType,blBufferPtr>                 operator--(int);
    blRoiIterator<blBufferType,blBufferPtr>                 operator+(const int& movement)const;
    blRoiIterator<blBufferType,blBufferPtr>                 operator-(const int& movement)const;



    // Function used to get the actual
    // distance in the buffer between
    // this iterator and another one

    std::ptrdiff_t                                          actualDistanceInTheBufferFromAnotherIterator(const blRoiIterator<blBufferType,blBufferPtr>& iterator);



    // Function used to advance the
    // iterator if the user doesn't
    // want to use the the overload
    // arithmetic operators

    blRoiIterator<blBufferType,blBufferPtr>&                advance(const std::ptrdiff_t& movement);



    // Function used to advance
    // the iterator by number of
    // circulations
    // For example if advancing
    // circulations by 1, the iterator
    // is advanced by m_bufferPtr->size()
    // of if advancing by -2, the
    // iterator is advanced by
    // -2*m_bufferPtr->size()

    blRoiIterator<blBufferType,blBufferPtr>&                advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy);



    // Functions used to get a pointer
    // or reference to the indexed data
    // point in the buffer

    blDataPtr                                               getPointerToIndexedDataPoint();
    const blDataPtr                                         getPointerToIndexedDataPoint()const;

    blDataType&                                             getReferenceToIndexedDataPoint();
    const blDataType&                                       getReferenceToIndexedDataPoint()const;



    // Overloaded referencing/dereferencing
    // operators

    // Dereferencing operators

    blDataType&                                             operator*();
    const blDataType&                                       operator*()const;
    blDataPtr                                               operator->();
    const blDataPtr                                         operator->()const;



protected: // Protected functions



    // This function updates the current
    // number of circulations/cycles that
    // the iterator has gone through up
    // to this instant

    void                                                    updateCurrentNumberOfCirculations();
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr>::blRoiIterator(const blBufferPtr& bufferPtr,
                                                              const std::ptrdiff_t& dataIndex,
                                                              const std::ptrdiff_t& maxNumberOfCirculations)
                                                              : blCircularIterator<blBufferType,blBufferPtr>(bufferPtr,
                                                                                                             dataIndex,
                                                                                                             maxNumberOfCirculations)
{
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr>::blRoiIterator(const blRoiIterator<blBufferType,blBufferPtr>& roiIterator)
                                                              : blCircularIterator<blBufferType,blBufferPtr>(roiIterator)
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr>::~blRoiIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Comparator operators
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline bool blRoiIterator<blBufferType,blBufferPtr>::operator==(const blRoiIterator<blBufferType,blBufferPtr>& roiIterator)const
{
    return ( this->getPointerToIndexedDataPoint() == roiIterator.getPointerToIndexedDataPoint() );
}



template<typename blBufferType,
         typename blBufferPtr>

inline bool blRoiIterator<blBufferType,blBufferPtr>::operator!=(const blRoiIterator<blBufferType,blBufferPtr>& roiIterator)const
{
    return ( this->getPointerToIndexedDataPoint() != roiIterator.getPointerToIndexedDataPoint() );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to update the current
// number of circulations/cycles that the
// iterator has gone through up to now
//------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline void blRoiIterator<blBufferType,blBufferPtr>::updateCurrentNumberOfCirculations()
{
    this->m_currentNumberOfCirculations = (this->m_dataIndex - this->m_startIndex) / std::ptrdiff_t(this->m_bufferPtr->roi().size());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function returning the iterator's base
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr> blRoiIterator<blBufferType,blBufferPtr>::base()
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
template<typename blBufferType,
         typename blBufferPtr>

inline std::size_t blRoiIterator<blBufferType,blBufferPtr>::remainingContiguousSpots()const
{
    return this->m_bufferPtr->roi().size() - this->circ_index(this->m_dataIndex,this->m_bufferPtr->roi().size());
}



template<typename blBufferType,
         typename blBufferPtr>

inline std::size_t blRoiIterator<blBufferType,blBufferPtr>::remainingContiguousBytes()const
{
    return sizeof(blDataType) * (this->m_bufferPtr->roi().size() - circ_index(this->m_dataIndex,this->m_bufferPtr->roi().size()));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Overloaded Operators that let us use this class as
// a normal iterator in stl-like algorithms
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline typename blRoiIterator<blBufferType,blBufferPtr>::blDataType& blRoiIterator<blBufferType,blBufferPtr>::operator*()
{
    return this->getReferenceToIndexedDataPoint();
}



template<typename blBufferType,
         typename blBufferPtr>

inline const typename blRoiIterator<blBufferType,blBufferPtr>::blDataType& blRoiIterator<blBufferType,blBufferPtr>::operator*()const
{
    return this->getReferenceToIndexedDataPoint();
}



template<typename blBufferType,
         typename blBufferPtr>

inline typename blRoiIterator<blBufferType,blBufferPtr>::blDataPtr blRoiIterator<blBufferType,blBufferPtr>::operator->()
{
    return this->getPointerToIndexedDataPoint();
}



template<typename blBufferType,
         typename blBufferPtr>

inline const typename blRoiIterator<blBufferType,blBufferPtr>::blDataPtr blRoiIterator<blBufferType,blBufferPtr>::operator->()const
{
    return this->getPointerToIndexedDataPoint();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator if the user doesn't
// want to use the the overload arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr>& blRoiIterator<blBufferType,blBufferPtr>::advance(const std::ptrdiff_t& movement)
{
    this->m_dataIndex += movement;

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

inline blRoiIterator<blBufferType,blBufferPtr>& blRoiIterator<blBufferType,blBufferPtr>::advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy)
{
    this->m_dataIndex += numberOfCirculationsToAdvanceTheIteratorBy * this->m_bufferPtr->roi().size();

    this->updateCurrentNumberOfCirculations();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get a reference or a
// pointer to the indexed data point in the
// buffer
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline typename blRoiIterator<blBufferType,blBufferPtr>::blDataType& blRoiIterator<blBufferType,blBufferPtr>::getReferenceToIndexedDataPoint()
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
        return this->m_bufferPtr->roi_at(this->m_bufferPtr->roi().size());

    return this->m_bufferPtr->roi_at(this->circ_index(this->m_dataIndex,this->m_bufferPtr->roi().size()));
}



template<typename blBufferType,
         typename blBufferPtr>

inline const typename blRoiIterator<blBufferType,blBufferPtr>::blDataType& blRoiIterator<blBufferType,blBufferPtr>::getReferenceToIndexedDataPoint()const
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
        return this->m_bufferPtr->roi_at(this->m_bufferPtr->roi().size());

    return this->m_bufferPtr->roi_at(this->circ_index(this->m_dataIndex,this->m_bufferPtr->roi().size()));
}



template<typename blBufferType,
         typename blBufferPtr>

inline typename blRoiIterator<blBufferType,blBufferPtr>::blDataPtr blRoiIterator<blBufferType,blBufferPtr>::getPointerToIndexedDataPoint()
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(!this->m_bufferPtr)
        return blDataPtr(nullptr);

    if(this->hasReachedEndOfBuffer())
        return blDataPtr(&this->m_bufferPtr->roi_at(this->m_bufferPtr->roi().size()));

    return blDataPtr(&this->m_bufferPtr->roi_at(this->circ_index(this->m_dataIndex,this->m_bufferPtr->roi().size())));
}



template<typename blBufferType,
         typename blBufferPtr>

inline const typename blRoiIterator<blBufferType,blBufferPtr>::blDataPtr blRoiIterator<blBufferType,blBufferPtr>::getPointerToIndexedDataPoint()const
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(!this->m_bufferPtr)
        return blDataPtr(nullptr);

    if(this->hasReachedEndOfBuffer())
        return blDataPtr(&this->m_bufferPtr->roi_at(this->m_bufferPtr->roi().size()));

    return blDataPtr(&this->m_bufferPtr->roi_at(this->circ_index(this->m_dataIndex,this->m_bufferPtr->roi().size())));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr>& blRoiIterator<blBufferType,blBufferPtr>::operator+=(const int& movement)
{
    this->m_dataIndex += movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr>& blRoiIterator<blBufferType,blBufferPtr>::operator-=(const int& movement)
{
    this->m_dataIndex -= movement;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr>& blRoiIterator<blBufferType,blBufferPtr>::operator++()
{
    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr>& blRoiIterator<blBufferType,blBufferPtr>::operator--()
{
    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr> blRoiIterator<blBufferType,blBufferPtr>::operator++(int)
{
    auto temp(*this);

    ++this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr> blRoiIterator<blBufferType,blBufferPtr>::operator--(int)
{
    auto temp(*this);

    --this->m_dataIndex;

    this->updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr> blRoiIterator<blBufferType,blBufferPtr>::operator+(const int& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blBufferType,
         typename blBufferPtr>

inline blRoiIterator<blBufferType,blBufferPtr> blRoiIterator<blBufferType,blBufferPtr>::operator-(const int& movement)const
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
template<typename blBufferType,
         typename blBufferPtr>

inline std::ptrdiff_t blRoiIterator<blBufferType,blBufferPtr>::actualDistanceInTheBufferFromAnotherIterator(const blRoiIterator<blBufferType,blBufferPtr>& iterator)
{
    return (
            static_cast<std::ptrdiff_t>( circ_index(this->m_dataIndex,this->m_bufferPtr->roi().size()) ) -
            static_cast<std::ptrdiff_t>( circ_index(iterator.getDataIndex(),iterator.getBufferReference().roi().size()) )
           );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Output circular iterator address to output stream
//-------------------------------------------------------------------
template<typename blBufferType,
         typename blBufferPtr>

inline std::ostream& operator<<(std::ostream& os,const blRoiIterator<blBufferType,blBufferPtr>& roiIterator)
{
    os << roiIterator.getPointerToIndexedDataPoint();

    return os;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_ROIITERATOR_HPP
