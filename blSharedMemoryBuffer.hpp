#ifndef BL_SHAREDMEMORYBUFFER_HPP
#define BL_SHAREDMEMORYBUFFER_HPP


//-------------------------------------------------------------------
// FILE:            blSharedMemoryBuffer.hpp
// CLASS:           blSharedMemoryBuffer
//
//
//
// PURPOSE:         -- Specialized template of blBuffer that works
//                     with boost::interprocess library for using
//                     smart buffers in shared memory
//
//                  -- This specialized template of blBuffer also
//                     overloads the "create" functions so that it
//                     can create the data on a user specified shared
//                     memory location
//
//                  -- The specialized template and all its type
//                     alieases are defined within the blBufferLIB
//                     namespace
//
//
//
// AUTHOR:          Vincenzo Barbato
//                  navyenzo@gmail.com
//
//
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
//
//
// DEPENDENCIES:    -- blBuffer4 and all its dependencies
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

// Include the buffer class

#include "blBuffer.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This specialized template is defined within
//       the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Useful type aliases to use buffer in shared memory
// with boost::interprocess library
//-------------------------------------------------------------------

#ifdef BOOST_INTERPROCESS_OFFSET_PTR_HPP



// Let's abbreviate the
// boost::interprocess
// namespace

namespace bsip = boost::interprocess;



// Allocator alias type that will
// allow placing data in user
// specified shared memory segments

template<typename blDataType>

using sharedMemoryAllocatorType = bsip::allocator<blDataType,bsip::managed_shared_memory::segment_manager>;



// Vector alias type that uses the
// above defined allocator type to
// allocate its data values in user
// specified shared memory segments

template<typename blDataType>

using sharedMemoryVectorType = bsip::vector< blDataType,sharedMemoryAllocatorType<blDataType> >;



// Buffer pointer type for shared memory

template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr = bsip::offset_ptr<blDataType> >

using blSharedBufferPtrType = bsip::offset_ptr< blBuffer_2<blDataType,blDataPtr,blMaxNumOfDimensions> >;



// Buffer roi pointer type for shared memory

template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr = bsip::offset_ptr<blDataType>,
         typename blBufferPtr = blSharedBufferPtrType<blDataType,blMaxNumOfDimensions,blDataPtr> >

using blSharedBufferRoiPtrType = bsip::offset_ptr< blBuffer_4<blDataType,blDataPtr,blBufferPtr,blMaxNumOfDimensions> >;



//-------------------------------------------------------------------
// Specialized template of buffer
// that works with shared memory
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr = bsip::offset_ptr<blDataType>,
         typename blBufferPtr = blSharedBufferPtrType<blDataType,blMaxNumOfDimensions,blDataPtr>,
         typename blBufferRoiPtr = blSharedBufferRoiPtrType<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr> >

class blSharedMemoryBuffer : public blBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>
{
public:



    // Default constructor

    blSharedMemoryBuffer();



    // Copy constructor

    blSharedMemoryBuffer(const blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>& sharedMemoryBuffer) = default;



    // Destructor

    ~blSharedMemoryBuffer();



public: // Assignment operators



    blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>& operator=(const blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>& sharedMemoryBuffer) = default;



public: // Overloaded Create functions used to
        // allocate the buffer memory in a shared
        // memory segment



    // -- The following Functions are used to
    //    create/risize the buffer space and to
    //    intialize it
    //
    // -- These functions allocate contiguous
    //    space interpreting it as an n-dimensional
    //    buffer with the user specified sizeN
    //    for each N-dimension
    //
    // -- The number of dimensions is determined
    //    by the passed number of arguments using
    //    variadic templates or initializer list
    //    in the second version of the function
    //    or a vector of sizes in the third version
    //    of the function
    //
    // -- These function overload the base functions
    //    allocating memory in a shared memory segment
    //    as opposed to its own internal memory

    template<typename...blIntegerType>
    bool                                                                    create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                   const std::string& nameOfDataVector,
                                                                                   const blIntegerType&... bufferLengths);

    template<typename blIntegerType>
    bool                                                                    create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                   const std::string& nameOfDataVector,
                                                                                   const std::initializer_list<blIntegerType>& bufferLengths);

    template<typename blIntegerType>
    bool                                                                    create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                   const std::string& nameOfDataVector,
                                                                                   const std::vector<blIntegerType>& bufferLengths);

    template<typename blIntegerType,
             std::size_t blNumberOfDimensions>
    bool                                                                    create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                   const std::string& nameOfDataVector,
                                                                                   const std::array<blIntegerType,blNumberOfDimensions>& bufferLengths);



private: // Create function that does the
         // actual work of allocating memory
         // This function gets called by the
         // other create functions

    bool                                                                    create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                   const std::string& nameOfDataVector);
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

inline blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::blSharedMemoryBuffer()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

inline blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::~blSharedMemoryBuffer()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// create functions used to allocate and
// initialize space for the buffer
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

template<typename...blIntegerType>

inline bool blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                                               const std::string& nameOfDataVector,
                                                                                                               const blIntegerType&...bufferLengths)
{
    this->m_properties.setDimensionalSizes(bufferLengths...);

    return create(sharedMemorySegment,
                  nameOfDataVector);
}



template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

template<typename blIntegerType>

inline bool blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                                               const std::string& nameOfDataVector,
                                                                                                               const std::initializer_list<blIntegerType>& bufferLengths)
{
    this->m_properties.setDimensionalSizes(bufferLengths);

    return create(sharedMemorySegment,
                  nameOfDataVector);
}



template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

template<typename blIntegerType>

inline bool blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                                               const std::string& nameOfDataVector,
                                                                                                               const std::vector<blIntegerType>& bufferLengths)
{
    this->m_properties.setDimensionalSizes(bufferLengths);

    return create(sharedMemorySegment,
                  nameOfDataVector);
}



template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

template<typename blIntegerType,
         std::size_t blNumberOfDimensions>

inline bool blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                                               const std::string& nameOfDataVector,
                                                                                                               const std::array<blIntegerType,blNumberOfDimensions>& bufferLengths)
{
    this->m_properties.setDimensionalSizes(bufferLengths);

    return create(sharedMemorySegment,
                  nameOfDataVector);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// create function used to allocate space for the buffer
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

inline bool blSharedMemoryBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::create(bsip::managed_shared_memory& sharedMemorySegment,
                                                                                                               const std::string& nameOfDataVector)
{
    // First we create an instance of
    // the shared memory allocator

    sharedMemoryAllocatorType<blDataType> sharedMemoryAllocator(sharedMemorySegment.get_segment_manager());



    // We then attempt to find or construct
    // the named data vector

    auto newDataVectorPointer = sharedMemorySegment.find_or_construct< sharedMemoryVectorType<blDataType> >(nameOfDataVector.c_str())(sharedMemoryAllocator);



    // If we were successful in finding
    // or constructing the data vector, we
    // wrap it with this buffer

    if(newDataVectorPointer)
    {
        // The first thing we need to do
        // is resize it to match the
        // newly user specified size

        newDataVectorPointer->resize(this->size());



        // We then make sure that the resize
        // was successful

        bool wasResizeSuccessful = newDataVectorPointer->size() == this->size();



        if(!wasResizeSuccessful)
        {
            // This means the allocation failed
            // so we reset the size to equal
            // the actual buffer size and default
            // all dimensional sizes to represent
            // a 1d buffer

            this->m_properties.setDimensionalSizes(newDataVectorPointer->size());
        }



        // Finally we wrap the newly
        // resized data vector with
        // this buffer

        this->wrap((*newDataVectorPointer)[0]);



        // Let's not forget to let
        // the user know whether the
        // resizing was successful

        return wasResizeSuccessful;
    }
    else
    {
        // This means that for some reason
        // we could not find nor construct
        // the named data vector, so we
        // let the user know we failed

        return false;
    }
}
//-------------------------------------------------------------------



#endif



//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_SHAREDMEMORYBUFFER_HPP
