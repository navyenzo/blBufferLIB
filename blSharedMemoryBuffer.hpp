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
//
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



// Buffer pointer type for shared memory

template<typename blDataType,
         typename blDataPtr = bsip::offset_ptr<blDataType> >

using blSharedBufferPtrType = bsip::offset_ptr< blBuffer_2<blDataType,blDataPtr> >;



// Buffer roi pointer type for shared memory

template<typename blDataType,
         typename blDataPtr = bsip::offset_ptr<blDataType>,
         typename blBufferPtr = blSharedBufferPtrType<blDataType> >

using blSharedBufferRoiPtrType = bsip::offset_ptr< blBuffer_4<blDataType,blDataPtr,blBufferPtr> >;



// Specialized template of buffer
// that works with shared memory

template<typename blDataType,
         typename blDataPtr = bsip::offset_ptr<blDataType>,
         typename blBufferPtr = blSharedBufferPtrType<blDataType>,
         typename blBufferRoiPtr = blSharedBufferRoiPtrType<blDataType> >

class blSharedMemoryBuffer : public blBuffer<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr>
{
public:



    blSharedMemoryBuffer() : blBuffer<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr>()
    {
    }



    blSharedMemoryBuffer(const blSharedMemoryBuffer<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr>& sharedMemoryBuffer)
                         : blBuffer<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr>(sharedMemoryBuffer)
    {
    }



    ~blSharedMemoryBuffer()
    {
    }
};



#endif



//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_SHAREDMEMORYBUFFER_HPP
