#ifndef BL_BUFFER_7_HPP
#define BL_BUFFER_7_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer_7.hpp
// CLASS:           blBuffer_7
// BASE CLASS:      blBuffer_6
//
// PURPOSE:         -- This class is based on blBuffer_6 and adds
//                     a single "write" iterator to the buffer with
//                     an atomic boolean used to know whether the
//                     buffer is currently being written to
//
//                     -- This allows multiple threads to write to
//                        this buffer
//
//                     -- This class offers 2 basic "write" functions:
//
//                        -- "write" -- writes to this buffer but
//                                      waits in case another thread
//                                      is currently writing to the
//                                      buffer
//
//                        -- "write_no_wait" -- writes to this buffer but
//                                              quits if another thread
//                                              is currently writing to
//                                              this buffer without waiting
//                                              around until it's ok to write
//
//                     -- This class also has some specialize "write"
//                        functions that make it easy to write single
//                        values or buffers that define the functions
//                        "size()" and "data()" such as std::vector or
//                        this very buffer, again with the option to
//                        wait or to not wait
//
//                  -- This class is defined within the blBufferLIB
//                     namespace
//
// AUTHOR:          Vincenzo Barbato
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    -- blBuffer_6 and all its dependencies
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

#include "blBuffer_6.hpp"

// Used to check whether the
// buffer is being written to
// by another thread

#include <atomic>

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blBuffer_7 declaration
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

class blBuffer_7 : public blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>
{
public: // Public type aliases



    using circular_iterator = typename blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::circular_iterator;
    using circular_const_iterator = typename blBuffer_6<blDataType,const blDataPtr,const blBufferPtr,const blBufferRoiPtr,blMaxNumOfDimensions>::circular_const_iterator;



public: // Constructors and destructors



    // Default constructor

    blBuffer_7();



    // Copy constructor

    blBuffer_7(const blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>& buffer7) = default;



    // Destructor

    ~blBuffer_7();



public: // Overloaded operators



    // Assignment operator

    blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>&    operator=(const blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>& buffer7) = default;



public: // Public functions



    // This function lets a user know
    // whether this buffer is currently
    // being written to by another thread

    bool                                                                    isBufferBeingCurrentlyWrittenTo()const;



    // The following functions can be used to
    // write from a specified variable or buffer
    // into this buffer
    //
    // When using the "write_buffer" function, we
    // assume that the user specified buffer defines
    // the functions "data()" and "size()"

    template <typename blValueType>
    std::size_t                                                             write_value(const blValueType& value);

    template <typename blValueType>
    std::size_t                                                             write_value(const blValueType* value);

    template <typename blBufferType>
    std::size_t                                                             write_buffer(const blBufferType& buffer);

    template <typename blBufferType>
    std::size_t                                                             write_buffer(const blBufferType* buffer,
                                                                                         const std::size_t& bufferLength);



    // The following functions are the
    // same as the above functions but
    // with the difference that they
    // DO NOT wait in case another thread
    // is currently writing to the buffer

    template <typename blValueType>
    std::size_t                                                             write_value_no_wait(const blValueType& value);

    template <typename blValueType>
    std::size_t                                                             write_value_no_wait(const blValueType* value);

    template <typename blBufferType>
    std::size_t                                                             write_buffer_no_wait(const blBufferType& buffer);

    template <typename blBufferType>
    std::size_t                                                             write_buffer_no_wait(const blBufferType* buffer,
                                                                                                 const std::size_t& bufferLength);



    // These functions do low-level
    // writing to the buffer, but
    // one of them waits in case another
    // thread is currently writing to
    // this buffer, while the other
    // function just quits in that case

    std::size_t                                                             write(const char* buffer,
                                                                                  const std::size_t& bufferLength);

    std::size_t                                                             write_no_wait(const char* buffer,
                                                                                          const std::size_t& bufferLength);

    template<typename blInputIteratorType>
    std::size_t                                                             write(const blInputIteratorType& begin,
                                                                                  const blInputIteratorType& end);

    template<typename blInputIteratorType>
    std::size_t                                                             write_no_wait(const blInputIteratorType& begin,
                                                                                          const blInputIteratorType& end);



    // Functions used to manually
    // move the write iterator to
    // the desired place in the buffer

    void                                                                    advance_writeIterator(const std::ptrdiff_t& movement);
    void                                                                    setPosition_writeIterator(const std::ptrdiff_t& positionInTheBuffer);



    // Function used to get the
    // current write iterator

    const circular_iterator&                                                writeIterator()const;



protected: // Protected variables



    // Write iterator used to keep
    // track of the current writing
    // spot

    circular_iterator                                                       m_writeIterator;



    // Atomic boolean used to know whether
    // the buffer is currently being written
    // to by a thread

    std::atomic_bool                                                        m_isBufferBeingCurrentlyWrittenTo;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::blBuffer_7() : blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>()
{
    // We start by saying that this
    // buffer is not currently being
    // written to as it's just being
    // constructed at this moment

    m_isBufferBeingCurrentlyWrittenTo = false;



    // NOTE:  In this constructor we also
    //        initialize the write iterator
    //        so that it will keep circulating
    //        around the buffer never stopping
    //        which means the user can keep
    //        writing more information to the
    //        buffer

    m_writeIterator = circular_iterator(this,0,-1);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::~blBuffer_7()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// These function are used to manually
// advance the write iterator
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline void blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::advance_writeIterator(const std::ptrdiff_t& movement)
{
    m_writeIterator.advance(movement);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline void blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::setPosition_writeIterator(const std::ptrdiff_t& positionInTheBuffer)
{
    m_writeIterator.setDataIndex(positionInTheBuffer);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the write iterator
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline const typename blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::circular_iterator& blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::writeIterator()const
{
    return m_writeIterator;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to ask whether the buffer is
// being currently written to
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline bool blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::isBufferBeingCurrentlyWrittenTo()const
{
    return bool(m_isBufferBeingCurrentlyWrittenTo);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following functions can be used to
// write from a specified variable or buffer
// into this buffer
//
// When using the "write_buffer" function, we
// assume that the user specified buffer defines
// the functions "data()" and "size()"
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blValueType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_value(const blValueType& value)
{
    return ( this->write(reinterpret_cast<const char*>(&value),sizeof(value)) ) / sizeof(value);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blValueType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_value(const blValueType* value)
{
    if(value)
        return ( this->write(reinterpret_cast<const char*>(value),sizeof(*value)) ) / sizeof(value);
    else
        return std::size_t(0);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blBufferType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_buffer(const blBufferType& buffer)
{
    return ( this->write(reinterpret_cast<const char*>(buffer.data()),sizeof(buffer.data()[0])*(buffer.size())) ) / sizeof(buffer.data()[0]);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blBufferType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_buffer(const blBufferType* buffer,
                                                                                                                  const std::size_t& bufferLength)
{
    return ( this->write(reinterpret_cast<const char*>(buffer),sizeof(buffer[0])*(bufferLength)) ) / sizeof(buffer[0]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The following functions are the
// same as the above functions but
// with the difference that they
// DO NOT wait in case another thread
// is currently writing to the buffer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blValueType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_value_no_wait(const blValueType& value)
{
    return ( this->write_no_wait(reinterpret_cast<const char*>(&value),sizeof(value)) ) / sizeof(value);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blValueType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_value_no_wait(const blValueType* value)
{
    if(value)
        return ( this->write_no_wait(reinterpret_cast<const char*>(value),sizeof(*value)) ) / sizeof(value);
    else
        return std::size_t(0);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blBufferType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_buffer_no_wait(const blBufferType& buffer)
{
    return ( this->write_no_wait(reinterpret_cast<const char*>(buffer.data()),sizeof(buffer.data()[0])*(buffer.size())) ) / sizeof(buffer.data()[0]);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blBufferType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_buffer_no_wait(const blBufferType* buffer,
                                                                                                                          const std::size_t& bufferLength)
{
    return ( this->write_no_wait(reinterpret_cast<const char*>(buffer),sizeof(buffer[0])*(bufferLength)) ) / sizeof(buffer[0]);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function does the actual writing to
// the buffer, but waits in case another
// thread is currently writing to this buffer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write(const char* stuffToWrite,
                                                                                                           const std::size_t& numberOfBytesToWrite)
{
    // First we check to make
    // sure we don't have a
    // zero-sized buffer

    if(this->size() == 0)
    {
        // We have a zero sized
        // buffer, which means
        // we can't write anything
        // to it

        return std::size_t(0);
    }



    // If another thread is currently
    // writing to this buffer, this function
    // waits around pantiently until it's
    // clear to write

    while(m_isBufferBeingCurrentlyWrittenTo)
    {
        // We just wait until it's clear
        // to write to this buffer
    }



    // We now let everyone know we're
    // currently writing to this buffer

    m_isBufferBeingCurrentlyWrittenTo = true;



    std::size_t numberOfBytesWrittenSoFar = 0;
    std::size_t numberOfBytesToWriteRightNow = 0;



    while(numberOfBytesWrittenSoFar < numberOfBytesToWrite &&
          !m_writeIterator.hasReachedEndOfBuffer())
    {
        // First we figure out how
        // many data elements to write
        // this current loop iteration
        // depending on how many contiguous
        // spots are available

        numberOfBytesToWriteRightNow = std::min(numberOfBytesToWrite - numberOfBytesWrittenSoFar,
                                                m_writeIterator.remainingContiguousBytes());



        // Now we actually write the
        // data to the buffer

        std::copy(stuffToWrite + numberOfBytesWrittenSoFar,
                  stuffToWrite + numberOfBytesWrittenSoFar + numberOfBytesToWriteRightNow,
                  reinterpret_cast<char*>(m_writeIterator.getPointerToIndexedDataPoint()));



        // We now advance the write iterator

        m_writeIterator += numberOfBytesToWriteRightNow / sizeof(blDataType);



        // We also keep track of the number
        // of data elements written so far

        numberOfBytesWrittenSoFar += numberOfBytesToWriteRightNow;
    }



    // We're done writing, so we make
    // sure everyone knows that

    m_isBufferBeingCurrentlyWrittenTo = false;



    // We let the user know
    // how many data elements
    // were actually written
    // to the buffer

    return numberOfBytesWrittenSoFar;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function does the actual writing to
// the buffer, but quits if another thread
// is currently writing to this buffer without
// waiting
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_no_wait(const char* stuffToWrite,
                                                                                                                   const std::size_t& numberOfBytesToWrite)
{
    // First we check to make
    // sure we don't have a
    // zero-sized buffer

    if(this->size() == 0)
    {
        // We have a zero sized
        // buffer, which means
        // we can't write anything
        // to it

        return std::size_t(0);
    }



    // If another thread is currently
    // writing to this buffer, this function
    // quits without waiting

    if(m_isBufferBeingCurrentlyWrittenTo)
        return std::size_t(0);



    // We now let everyone know we're
    // currently writing to this buffer

    m_isBufferBeingCurrentlyWrittenTo = true;



    std::size_t numberOfBytesWrittenSoFar = 0;
    std::size_t numberOfBytesToWriteRightNow = 0;



    while(numberOfBytesWrittenSoFar < numberOfBytesToWrite &&
          !m_writeIterator.hasReachedEndOfBuffer())
    {
        // First we figure out how
        // many data elements to write
        // this current loop iteration
        // depending on how many contiguous
        // spots are available

        numberOfBytesToWriteRightNow = std::min(numberOfBytesToWrite - numberOfBytesWrittenSoFar,
                                                m_writeIterator.remainingContiguousBytes());



        // Now we actually write the
        // data to the buffer

        std::copy(stuffToWrite + numberOfBytesWrittenSoFar,
                  stuffToWrite + numberOfBytesWrittenSoFar + numberOfBytesToWriteRightNow,
                  reinterpret_cast<char*>(m_writeIterator.getPointerToIndexedDataPoint()));



        // We now advance the write iterator

        m_writeIterator += numberOfBytesToWriteRightNow / sizeof(blDataType);



        // We also keep track of the number
        // of data elements written so far

        numberOfBytesWrittenSoFar += numberOfBytesToWriteRightNow;
    }



    // We're done writing, so we make
    // sure everyone knows that

    m_isBufferBeingCurrentlyWrittenTo = false;



    // We let the user know
    // how many data elements
    // were actually written
    // to the buffer

    return numberOfBytesWrittenSoFar;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// These functions doe the actual writing to
// the buffer using iterators
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blInputIteratorType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write(const blInputIteratorType& begin,
                                                                                                           const blInputIteratorType& end)
{
    // If another thread is currently
    // writing to this buffer, this function
    // waits around pantiently until it's
    // clear to write

    while(m_isBufferBeingCurrentlyWrittenTo)
    {
        // We just wait until it's clear
        // to write to this buffer
    }



    // We now let everyone know we're
    // currently writing to this buffer

    m_isBufferBeingCurrentlyWrittenTo = true;



    // Finally we copy the data
    // into this buffer

    std::copy(begin,end,this->m_writeIterator);



    // We advance the write iterator

    m_writeIterator += std::distance(begin,end);



    // We're done writing, so we make
    // sure everyone knows that

    m_isBufferBeingCurrentlyWrittenTo = false;



    // We now return the amount
    // of data points written to
    // this buffer

    return std::distance(begin,end);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blInputIteratorType>

inline std::size_t blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::write_no_wait(const blInputIteratorType& begin,
                                                                                                                   const blInputIteratorType& end)
{
    // If another thread is currently
    // writing to this buffer, this function
    // quits without waiting

    if(m_isBufferBeingCurrentlyWrittenTo)
        return std::size_t(0);



    // We now let everyone know we're
    // currently writing to this buffer

    m_isBufferBeingCurrentlyWrittenTo = true;



    // Finally we copy the data
    // into this buffer

    std::copy(begin,end,this->m_writeIterator);



    // We advance the write iterator

    m_writeIterator += std::distance(begin,end);



    // We're done writing, so we make
    // sure everyone knows that

    m_isBufferBeingCurrentlyWrittenTo = false;



    // We now return the amount
    // of data points written to
    // this buffer

    return std::distance(begin,end);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_7_HPP
