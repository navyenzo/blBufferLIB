#ifndef BL_CIRCULARITERATOR_HPP
#define BL_CIRCULARITERATOR_HPP



//-------------------------------------------------------------------
// FILE:            blCircularIterator.hpp
// CLASS:           blCircularIterator
// BASE CLASS:      None
//
//
//
// PURPOSE:         -- A circular iterator used to iterate over a buffer
//
//                  -- This iterator assumes that the buffer in question
//                     defines the following functions:
//
//                     -- "at" function for random access
//
//                     -- "size" function for getting the total size
//                        of the buffer
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
// DEPENDENCIES:    -- <iterator>
//
//                  -- <utility>
//
//                  -- The buffer type has to define the above
//                     mentioned functions
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

// Used to define iterator category

#include <iterator>



// Used to derive the type of data
// stored in the buffer

#include <utility>

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blBufferType>
class blCircularIterator
{
public: // Iterator traits



    using iterator_category = std::random_access_iterator_tag;
    using value_type = blBufferType;
    using difference_type = ptrdiff_t;
    using pointer = blBufferType*;
    using reference = blBufferType&;



public: // Public typedefs



    typedef decltype( std::declval<blBufferType>().at() )           blDataType;
    typedef decltype( &std::declval<blBufferType>().at() )          blDataTypePtr;



public: // Constructors and destructors



    // No default constructor

    blCircularIterator() = delete;



    // Constructor from a buffer reference

    blCircularIterator(blBufferType& buffer,
                       const std::ptrdiff_t& dataIndex,
                       const std::ptrdiff_t& maxNumberOfCirculations);



    // Copy constructor

    blCircularIterator(const blCircularIterator<blBufferType>& circularIterator);



    // Destructor

    ~blCircularIterator();



public: // Public static functions



    // Function used to get a circularly
    // wrapped buffer index for a specified
    // non-wrapped buffer index and a
    // buffer size

    template<typename blIntegerType>
    static std::size_t                          circ_index(const blIntegerType& index,
                                                           const std::size_t& totalLength)
    {
        return static_cast<std::size_t>( (index % static_cast<blIntegerType>(totalLength) + static_cast<blIntegerType>(totalLength)) ) % totalLength;
    }



public: // Public functions



    // Boolean operator to check
    // the validity of the iterator
    // just like a standard pointer

    operator                                    bool()const
    {
        if(m_buffer.size() > 0)
            return true;
        else
            return false;
    }



    // Comparator operators

    bool                                        operator==(const blCircularIterator<blBufferType>& imageCircularIterator)const;
    bool                                        operator!=(const blCircularIterator<blBufferType>& imageCircularIterator)const;



    // Function returning the
    // iterator's base

    blCircularIterator<blBufferType>            base();



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



    // Function used to know whether
    // the iterator has terminated
    // circulating

    bool                                        hasReachedEndOfBuffer()const;



    // Arithmetic operators

    blCircularIterator<blBufferType>&           operator+=(const int& movement);
    blCircularIterator<blBufferType>&           operator-=(const int& movement);
    blCircularIterator<blBufferType>&           operator++();
    blCircularIterator<blBufferType>&           operator--();
    blCircularIterator<blBufferType>            operator++(int);
    blCircularIterator<blBufferType>            operator--(int);
    blCircularIterator<blBufferType>            operator+(const int& movement)const;
    blCircularIterator<blBufferType>            operator-(const int& movement)const;

    std::ptrdiff_t                              operator-(const blCircularIterator<blBufferType>& circularIterator)const;



    // Function used to get the actual
    // distance in the buffer between
    // this iterator and another one

    std::ptrdiff_t                              actualDistanceInTheBufferFromAnotherIterator(const blCircularIterator<blBufferType>& iterator);



    // Function  used to reset the
    // iterator so that it points
    // to the location it started
    // counting from

    void                                        reset();



    // Function used to advance the
    // iterator if the user doesn't
    // want to use the the overload
    // arithmetic operators

    blCircularIterator<blBufferType>&           advance(const std::ptrdiff_t& movement);



    // Function used to advance
    // the iterator by number of
    // circulations
    // For example if advancing
    // circulations by 1, the iterator
    // is advanced by m_buffer.size()
    // of if advancing by -2, the
    // iterator is advanced by
    // -2*m_buffer.size()

    blCircularIterator<blBufferType>&           advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy);



    // Function used to get the
    // reference to the data buffer

    blBufferType&                               getBufferReference();
    blBufferType&                               getBufferReference()const;



    // Functions used to get a pointer
    // or reference to the indexed data
    // point in the buffer

    blDataTypePtr                               getPointerToIndexedDataPoint();
    const blDataTypePtr                         getPointerToIndexedDataPoint()const;

    blDataType&                                 getReferenceToIndexedDataPoint();
    const blDataType&                           getReferenceToIndexedDataPoint()const;



    // Functions used to get the
    // current data index

    const std::ptrdiff_t&                       getDataIndex()const;
    const std::ptrdiff_t&                       getStartIndex()const;
    const std::ptrdiff_t&                       getCurrentNumberOfCirculations()const;
    const std::ptrdiff_t&                       getMaxNumberOfCirculations()const;



    // Functions used to manually
    // set the current data index
    // essentially resetting the
    // current number of circulations

    void                                        setDataIndex(const int& dataIndex);



    // Function used to return the
    // total amount of iterated length
    // including circulations

    std::ptrdiff_t                              getTotalIteratedLength()const;



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



protected: // Protected variables



    // The reference to the
    // data buffer

    blBufferType&                               m_buffer;



    // Buffer index used to point
    // somewhere inside the buffer

    std::ptrdiff_t                              m_dataIndex;



    // Index where the iterator
    // started iterating from

    std::ptrdiff_t                              m_startIndex;



    // Current number of iteration
    // circulations/cycles that
    // the iterator has gone through
    // up to this instant

    std::ptrdiff_t                              m_currentNumberOfCirculations;



    // Max number of allowed times
    // the iterator can circulate
    // around the buffer before reaching
    // the "end" of the buffer.
    // This is critical for allowing
    // the use of this circular iterator
    // in stl-like algorithms that need
    // to reach the "end" iterator at some
    // point

    std::ptrdiff_t                              m_maxNumberOfCirculations;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularIterator<blBufferType>::blCircularIterator(blBufferType& buffer,
                                                  const std::ptrdiff_t& dataIndex,
                                                  const std::ptrdiff_t& maxNumberOfCirculations)
                                                  : m_buffer(buffer)
{
    setDataIndex(dataIndex);

    m_maxNumberOfCirculations = maxNumberOfCirculations;
}



template<typename blBufferType>
inline blCircularIterator<blBufferType>::blCircularIterator(const blCircularIterator<blBufferType>& circularIterator)
                                                            : m_buffer(circularIterator.getBufferReference())
{
    m_dataIndex = circularIterator.getDataIndex();
    m_startIndex = circularIterator.getStartIndex();
    m_currentNumberOfCirculations = circularIterator.getCurrentNumberOfCirculations();
    m_maxNumberOfCirculations = circularIterator.getMaxNumberOfCirculations();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularIterator<blBufferType>::~blCircularIterator()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Operators that let us use this class as
// a normal iterator in stl-like algorithms
//-------------------------------------------------------------------
template<typename blBufferType>
inline typename blCircularIterator<blBufferType>::blDataType& blCircularIterator<blBufferType>::operator*()
{
    return this->getReferenceToIndexedDataPoint();
}



template<typename blBufferType>
inline const typename blCircularIterator<blBufferType>::blDataType& blCircularIterator<blBufferType>::operator*()const
{
    return this->getReferenceToIndexedDataPoint();
}



template<typename blBufferType>
inline typename blCircularIterator<blBufferType>::blDataTypePtr blCircularIterator<blBufferType>::operator->()
{
    return this->getPointerToIndexedDataPoint();
}



template<typename blBufferType>
inline const typename blCircularIterator<blBufferType>::blDataTypePtr blCircularIterator<blBufferType>::operator->()const
{
    return this->getPointerToIndexedDataPoint();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Comparator operators
//-------------------------------------------------------------------
template<typename blBufferType>
inline bool blCircularIterator<blBufferType>::operator==(const blCircularIterator<blBufferType>& circularIterator)const
{
    return (this->getTotalIteratedLength() == circularIterator.getTotalIteratedLength());
}



template<typename blBufferType>
inline bool blCircularIterator<blBufferType>::operator!=(const blCircularIterator<blBufferType>& circularIterator)const
{
    return (this->getTotalIteratedLength() != circularIterator.getTotalIteratedLength());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function returning the iterator's base
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularIterator<blBufferType> blCircularIterator<blBufferType>::base()
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
inline std::size_t blCircularIterator<blBufferType>::remainingContiguousSpots()const
{
    return this->m_buffer.size() - circ_index(this->m_dataIndex,this->m_buffer.size());
}



template<typename blBufferType>
inline std::size_t blCircularIterator<blBufferType>::remainingContiguousBytes()const
{
    return sizeof(blDataType) * (this->m_buffer.size() - circ_index(this->m_dataIndex,m_buffer.size()));
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to ask whether the iterator
// has reached the buffer's end
//-------------------------------------------------------------------
template<typename blBufferType>
inline bool blCircularIterator<blBufferType>::hasReachedEndOfBuffer()const
{
    return (std::abs(this->m_currentNumberOfCirculations) >= m_maxNumberOfCirculations && m_maxNumberOfCirculations >= 0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularIterator<blBufferType>& blCircularIterator<blBufferType>::operator+=(const int& movement)
{
    m_dataIndex += movement;

    updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blCircularIterator<blBufferType>& blCircularIterator<blBufferType>::operator-=(const int& movement)
{
    m_dataIndex -= movement;

    updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blCircularIterator<blBufferType>& blCircularIterator<blBufferType>::operator++()
{
    ++m_dataIndex;

    updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blCircularIterator<blBufferType>& blCircularIterator<blBufferType>::operator--()
{
    --m_dataIndex;

    updateCurrentNumberOfCirculations();

    return (*this);
}



template<typename blBufferType>
inline blCircularIterator<blBufferType> blCircularIterator<blBufferType>::operator++(int)
{
    auto temp(*this);

    ++m_dataIndex;

    updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType>
inline blCircularIterator<blBufferType> blCircularIterator<blBufferType>::operator--(int)
{
    auto temp(*this);

    --m_dataIndex;

    updateCurrentNumberOfCirculations();

    return temp;
}



template<typename blBufferType>
inline blCircularIterator<blBufferType> blCircularIterator<blBufferType>::operator+(const int& movement)const
{
    auto temp(*this);

    temp += movement;

    return temp;
}



template<typename blBufferType>
inline blCircularIterator<blBufferType> blCircularIterator<blBufferType>::operator-(const int& movement)const
{
    auto temp(*this);

    temp -= movement;

    return temp;
}



template<typename blBufferType>
inline std::ptrdiff_t blCircularIterator<blBufferType>::operator-(const blCircularIterator<blBufferType>& circularIterator)const
{
    return ( m_dataIndex - circularIterator.getDataIndex() );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the actual
// distance in the buffer between
// this iterator and another one
//-------------------------------------------------------------------
template<typename blBufferType>
inline std::ptrdiff_t blCircularIterator<blBufferType>::actualDistanceInTheBufferFromAnotherIterator(const blCircularIterator<blBufferType>& iterator)
{
    return (
            static_cast<std::ptrdiff_t>( circ_index(this->m_dataIndex,this->m_buffer.size()) ) -
            static_cast<std::ptrdiff_t>( circ_index(iterator.getDataIndex(),iterator.getBufferReference().size()) )
           );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function  used to reset the
// iterator so that it points
// to the location it started
// counting from
//-------------------------------------------------------------------
template<typename blBufferType>
inline void blCircularIterator<blBufferType>::reset()
{
    this->setDataIndex(this->m_startIndex);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to advance the iterator if the user doesn't
// want to use the the overload arithmetic operators
//-------------------------------------------------------------------
template<typename blBufferType>
inline blCircularIterator<blBufferType>& blCircularIterator<blBufferType>::advance(const std::ptrdiff_t& movement)
{
    m_dataIndex += movement;

    updateCurrentNumberOfCirculations();

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
inline blCircularIterator<blBufferType>& blCircularIterator<blBufferType>::advanceCirculations(const std::ptrdiff_t& numberOfCirculationsToAdvanceTheIteratorBy)
{
    m_dataIndex += numberOfCirculationsToAdvanceTheIteratorBy * this->m_buffer.size();

    updateCurrentNumberOfCirculations();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get this iterator's members
//-------------------------------------------------------------------
template<typename blBufferType>
inline const std::ptrdiff_t& blCircularIterator<blBufferType>::getDataIndex()const
{
    return m_dataIndex;
}



template<typename blBufferType>
inline const std::ptrdiff_t& blCircularIterator<blBufferType>::getStartIndex()const
{
    return m_startIndex;
}



template<typename blBufferType>
inline const std::ptrdiff_t& blCircularIterator<blBufferType>::getCurrentNumberOfCirculations()const
{
    return m_currentNumberOfCirculations;
}



template<typename blBufferType>
inline const std::ptrdiff_t& blCircularIterator<blBufferType>::getMaxNumberOfCirculations()const
{
    return m_maxNumberOfCirculations;
}



template<typename blBufferType>
inline blBufferType& blCircularIterator<blBufferType>::getBufferReference()
{
    return m_buffer;
}



template<typename blBufferType>
inline blBufferType& blCircularIterator<blBufferType>::getBufferReference()const
{
    return m_buffer;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to update the current
// number of circulations/cycles that the
// iterator has gone through up to now
//-------------------------------------------------------------------
template<typename blBufferType>
inline void blCircularIterator<blBufferType>::updateCurrentNumberOfCirculations()
{
    m_currentNumberOfCirculations = (m_dataIndex - m_startIndex) / std::ptrdiff_t(m_buffer.size());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get a reference or a
// pointer to the indexed data point in the
// buffer
//-------------------------------------------------------------------
template<typename blBufferType>
inline typename blCircularIterator<blBufferType>::blDataType& blCircularIterator<blBufferType>::getReferenceToIndexedDataPoint()
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
    {
        return this->m_buffer[m_buffer.size()];
    }
    else
    {
        return this->m_buffer[this->circ_index(m_dataIndex,this->m_buffer.size())];
    }
}



template<typename blBufferType>
inline const typename blCircularIterator<blBufferType>::blDataType& blCircularIterator<blBufferType>::getReferenceToIndexedDataPoint()const
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
    {
        return this->m_buffer[m_buffer.size()];
    }
    else
    {
        return this->m_buffer[this->circ_index(m_dataIndex,this->m_buffer.size())];
    }
}



template<typename blBufferType>
inline typename blCircularIterator<blBufferType>::blDataTypePtr blCircularIterator<blBufferType>::getPointerToIndexedDataPoint()
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
    {
        return &this->m_buffer[m_buffer.size()];
    }
    else
    {
        return &this->m_buffer[this->circ_index(m_dataIndex,this->m_buffer.size())];
    }
}



template<typename blBufferType>
inline const typename blCircularIterator<blBufferType>::blDataTypePtr blCircularIterator<blBufferType>::getPointerToIndexedDataPoint()const
{
    // If the max number of circulations
    // has been passed, then we return the
    // "end" iterator, otherwise we return
    // the correct iterator

    // If the max number of circulations
    // is negative, we never stop

    if(this->hasReachedEndOfBuffer())
    {
        return &m_buffer[m_buffer.size()];
    }
    else
    {
        return &this->m_buffer[this->circ_index(m_dataIndex,this->m_buffer.size())];
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to manually set the
// data index, essentially resetting
// the current number of circulations
//-------------------------------------------------------------------
template<typename blBufferType>
inline void blCircularIterator<blBufferType>::setDataIndex(const int& dataIndex)
{
    m_dataIndex = dataIndex;

    m_startIndex = dataIndex;

    m_currentNumberOfCirculations = 0;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to return the
// total amount of iterated length
// including circulations
//-------------------------------------------------------------------
template<typename blBufferType>
inline std::ptrdiff_t blCircularIterator<blBufferType>::getTotalIteratedLength()const
{
    return this->m_dataIndex - this->m_startIndex;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_CIRCULARITERATOR_HPP
