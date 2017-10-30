#ifndef BL_BUFFER_8_HPP
#define BL_BUFFER_8_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer_8.hpp
// CLASS:           blBuffer_8
// BASE CLASS:      blBuffer_7
//
// PURPOSE:         -- This class is based on blBuffer_7 and adds
//                     multiple "read" iterators to the buffer, where
//                     each "read" iterator can be used by a separate
//                     thread that wants to read from this buffer
//
//                     -- This allows multiple threads to read from
//                        this buffer simultaneously
//
//                     -- The different "read" iterators are accessed
//                        by using the appropriate "read(id)" function
//
//                        -- For example if a thread uses the function
//                           read(0), then it makes use of the readIterator0,
//                           or if another thread uses the function
//                           read(13), then it makes use of the readIterator13,
//                           or read(-5) uses readIterator-5 and so on
//
//                       -- All read iterators are stored in an unordered_map
//                          and are created the instant a thread uses
//                          the corresponding read(id) function for the
//                          first time
//
//                       -- Each read iterator is advanced every time
//                          the read(id) function is called by a thread
//                          and is advanced by the actual number of
//                          elements read by that function
//
//                       -- Each read iterator cannot go past the current
//                          write iterator of this buffer, so the reading
//                          stops as soon as the read iterator reaches
//                          the write iterator
//
//                       -- NOTE: Each thread is responsible of using a different
//                                read<id> function to not cause multiple
//                                threads fighting each other
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
// DEPENDENCIES:    -- blBuffer_7 and all its dependencies
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

#include "blBuffer_7.hpp"



// Used to store read iterators

#include <unordered_map>

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blBuffer_8 declaration
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

class blBuffer_8 : public blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>
{
public: // Public type aliases



    using circular_iterator = typename blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::circular_iterator;
    using circular_const_iterator = typename blBuffer_7<blDataType,const blDataPtr,const blBufferPtr,const blBufferRoiPtr,blMaxNumOfDimensions>::circular_const_iterator;

    using read_iterators_container = std::unordered_map<int,circular_iterator>;



public: // Constructors and destructors



    // Default constructor

    blBuffer_8();



    // Copy constructor

    blBuffer_8(const blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>& buffer8) = default;



    // Destructor

    ~blBuffer_8();



public: // Overloaded operators



    // Assignment operator

    blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>&   operator=(const blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>& buffer8) = default;



public: // Public functions



    // This function returns a reference
    // to the read(id) iterator.
    // If that read iterator does not
    // exist yet, this function creates
    // and initializes it to start at
    // the beginning of the buffer

    circular_iterator&                                                      readIterator(const int& id);



    // This function reads data from
    // this buffer into an output
    // buffer

    template<typename blAnotherDataType,
             typename blAnotherDataPtr,
             typename blAnotherBufferPtr,
             typename blAnotherBufferRoiPtr,
             std::size_t blDifferentMaxNumOfDimensions>

    std::size_t                                                             read(const int& id,
                                                                                 blBuffer_8<blAnotherDataType,blAnotherDataPtr,blAnotherBufferPtr,blAnotherBufferRoiPtr,blDifferentMaxNumOfDimensions>& outputBuffer);



    // This function reads data from
    // this buffer into an output
    // buffer given by output iterators

    template<typename blOutputIteratorType>
    std::size_t                                                             read(const int& id,
                                                                                 const blOutputIteratorType& begin,
                                                                                 const blOutputIteratorType& end);



    // This function reads unformattedreadIteratorsContainerType
    // raw data from this buffer and
    // copies it into the specified buffer
    // The specified "id" invokes the
    // corresponding read(id) iterator

    std::size_t                                                             read(const int& id,
                                                                                 char* outputBuffer,
                                                                                 const std::size_t& outputBufferLength);



    // This function takes a specified
    // read iterator and advances it in
    // case that it has been lapped by
    // the current write iterator, so that
    // it won't mistakingly read the same
    // data over and over

    void                                                                    adjustReadIterator(circular_iterator& readIter);



private: // Private variables



    // Write iterator used to keep
    // track of the current writing
    // spot

    read_iterators_container                                                m_readIterators;
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

inline blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::blBuffer_8() : blBuffer_7<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>()
{
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

inline blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::~blBuffer_8()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// The buffer calls this private function because a thread
// calls the read(id) function which works with the read(id)
// iterator.
// If that iterator does not exist yet, this function creates
// and initializes the iterator to point at the beginning of
// the buffer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline typename blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::circular_iterator& blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::readIterator(const int& id)
{
    // First we have to check if
    // the specified read(id) iterator
    // exists

    auto iter = m_readIterators.find(id);



    // If the requested read iterator
    // exists, we're done and we
    // return it

    if(iter != m_readIterators.end())
        return (iter->second);



    // If we made it here, that means the
    // iterator does not exist yet, so we
    // create it and initialize it

    // NOTE:  The newly created read iterator
    //        is defaulted to never stop, meaning
    //        indefinite number of maximum circulations
    //        This is because we only want the
    //        read iterator to stop once it reaches
    //        the current write iterator

    circular_iterator newReadIterator((*this),0,-1);



    // Let's adjust the newly created
    // read iterator in case the current
    // write iterator has lapped the buffer
    // multiple times over

    adjustReadIterator(newReadIterator);



    // Here we insert the newly created
    // read(id) iterator into the unorderd_map

    m_readIterators.insert( {id,newReadIterator} );



    // We just inserted the newly created
    // and initialized read iterator into
    // the unordered_map, so now we grab
    // a hold of it and return it as a
    // reference

    iter = m_readIterators.find(id);

    return iter->second;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function takes a specified
// read iterator and advances it in
// case that it has been lapped by
// the current write iterator, so that
// it won't mistakingly read the same
// data over and over
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline void blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::adjustReadIterator(circular_iterator& readIter)
{
    // We compare the current number
    // of circulations of the write
    // iterator with the specified
    // read iterator

    if(this->m_writeIterator.getCurrentNumberOfCirculations() > readIter.getCurrentNumberOfCirculations())
    {
        // This means that the current write
        // terator has lapped the specified
        // read iterator, maybe even multiple
        // times over

        // We advance the read iterator so
        // that its current number of circulations
        // is 1 less than the write iterator

        readIter.advanceCirculations(this->m_writeIterator.getCurrentNumberOfCirculations() -
                                     readIter.getCurrentNumberOfCirculations() - 1);



        // Next we need to know if the write
        // iterator is pointing somewhere in
        // the buffer that's ahead of where
        // the read iterator is pointing in the
        // buffer

        // In this case we need the read iterator
        // to be pointing to a place in the buffer
        // ahead of where the write iterator
        // is pointing, since the read iterator
        // is one circulation behind the write
        // iterator

        auto actualDistanceInTheBufferFromReadIterToWriteIter = this->m_writeIterator.actualDistanceInTheBufferFromAnotherIterator(readIter);

        if(actualDistanceInTheBufferFromReadIterToWriteIter > 0)
        {
            // The means the write iterator
            // is ahead in the buffer, so
            // we advance the read iterator
            // to make it point to the spot
            // where the write iterator is
            // about to write

            readIter += actualDistanceInTheBufferFromReadIterToWriteIter;
        }
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function reads data from
// this buffer into an output
// buffer given by output iterators
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blAnotherDataType,
         typename blAnotherDataPtr,
         typename blAnotherBufferPtr,
         typename blAnotherBufferRoiPtr,
         std::size_t blDifferentMaxNumOfDimensions>

inline std::size_t blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::read(const int& id,
                                                                                                          blBuffer_8<blAnotherDataType,blAnotherDataPtr,blAnotherBufferPtr,blAnotherBufferRoiPtr,blDifferentMaxNumOfDimensions>& outputBuffer)
{
    // First we grab a hold of
    // the corresponding read(id)
    // iterator

    auto& iter = readIterator(id);



    // Find the amount of
    // data to copy

    auto amountOfDataToCopy = this->m_writeIterator - iter;



    // Now we copy from this
    // buffer into the supplied
    // output buffer

    std::copy(iter,this->m_writeIterator,outputBuffer.writeIterator());



    // Finally we advance both the
    // write iterator of the output
    // buffer as well as the read iterator
    // of this buffer by the amount of data
    // we just copied

    outputBuffer.advance_writeIterator(amountOfDataToCopy);
    iter.advance(amountOfDataToCopy);



    // Return the amount of data
    // we copied

    return amountOfDataToCopy;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function reads data from
// this buffer into an output
// buffer given by output iterators
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blOutputIteratorType>

inline std::size_t blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::read(const int& id,
                                                                                                          const blOutputIteratorType& beginOutput,
                                                                                                          const blOutputIteratorType& endOutput)
{
    // First we grab a hold of
    // the corresponding read(id)
    // iterator

    auto& iter = readIterator(id);



    // Iterator used to iterate
    // over output buffer

    blOutputIteratorType outputIter = beginOutput;



    // Number of elements read from
    // this buffer into the specified
    // buffer

    std::size_t numberOfElementsRead = std::size_t(0);



    // Let's copy the data elements
    // one element at a time

    while((iter != this->m_writeIterator) && (outputIter != endOutput))
    {
        (*outputIter) = (*iter);

        ++iter;
        ++outputIter;

        ++numberOfElementsRead;
    }



    // We're done, we return
    // the number of elements
    // that were read from this
    // buffer into the output
    // buffer

    return numberOfElementsRead;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// This function reads unformatted
// raw data from this buffer and
// copies it into the specified buffer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline std::size_t blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::read(const int& id,
                                                                                                          char* outputBuffer,
                                                                                                          const std::size_t& outputBufferLength)
{
    // First we grab a hold of
    // the corresponding read(id)
    // iterator

    auto& iter = readIterator(id);



    // We then calculate how many
    // data points are available
    // to us that haven't been read
    // yet by this read(id) iterator

    std::size_t howManyPointsAreAvailableToRead = this->m_writeIterator - iter;



    // We then read the data points
    // remembering that we cannot
    // read more than the specified
    // buffer length

    if(howManyPointsAreAvailableToRead * sizeof(blDataType) < outputBufferLength)
    {
        // In this case, we can straight
        // out copy all the available
        // data points without worrying
        // about overstepping our boundaries
        // in the user specified buffer

        std::copy(iter,this->m_writeIterator,reinterpret_cast<blDataType*>(outputBuffer));



        // Advance the read iterator

        iter += howManyPointsAreAvailableToRead;



        // Return the number of bytes read

        return howManyPointsAreAvailableToRead * sizeof(blDataType);
    }
    else
    {
        // This means that the buffer we
        // need to copy the read data into
        // is smaller than the amount of
        // available data to read from this
        // buffer

        std::copy(iter,iter + (outputBufferLength / sizeof(blDataType)),reinterpret_cast<blDataType*>(outputBuffer));



        // Advance the read iterator

        iter += (outputBufferLength / sizeof(blDataType));



        // Return the number of bytes read

        return outputBufferLength;
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_8_HPP
