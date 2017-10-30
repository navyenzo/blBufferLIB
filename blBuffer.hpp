#ifndef BL_BUFFER_HPP
#define BL_BUFFER_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer.hpp
// CLASS:           blBuffer
// BASE CLASS:      blBuffer_N
//
//
//
// PURPOSE:         -- Based on blBuffer_N, where N is the last of
//                     the following classes:
//
//                     -- blBuffer_0
//                     -- blBuffer_2
//                     -- blBuffer_3
//                           .
//                           .
//                           .
//                     -- blBuffer_N
//
//                  -- blBuffer is a generic buffer that can be used as
//                     a generic 1d, 2d or 3d contiguous buffer.  That is
//                     the same contiguous buffer can be seen as a 1d,
//                     2d or 3d dense matrix of any type of data.
//
//                  -- The buffer has conversion operators that allow it
//                     to be used interchangibly with OpenCV's cv::Mat or
//                     IplImage or cvMat structures in OpenCV's algorithms.
//
//                  -- The buffer also has conversions that allow it
//                     to be used as an sfml image from the sfml library.
//
//                  -- The buffer can "copy" or "wrap" data from other types
//                     of buffers, such as OpenCV's image structures, Qt's
//                     QVector, sfml images, std::vector, std::array, raw
//                     dynamic c-arrays, raw static c-arrays and more.
//
//                  -- The buffer also defines a Region Of Interest (ROI) with
//                     appropriate access functions that allow the user to
//                     manipulate sub-parts of the buffer as if they were
//                     their own buffers
//
//                  -- The buffer also defines iterators, ROI-iterators as well
//                     as circular-iterators and circular-ROI-iterators that can
//                     all work with stl-algorithms
//
//                  -- The buffer and all its functions are defined
//                     within the blBufferLIB namespace
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
// DEPENDENCIES:    -- blBuffer_N and all its dependencies
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

// Include the base class

#include "blBuffer_8.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Useful type aliases to simplify the code
//-------------------------------------------------------------------

// Standard buffer pointer type

template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr = blDataType*>

using blBufferPtrType = blBuffer_2<blDataType,blDataPtr,blMaxNumOfDimensions>*;



// Standard buffer roi pointer type

template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr = blDataType*,
         typename blBufferPtr = blBufferPtrType<blDataType,blMaxNumOfDimensions,blDataPtr> >

using blBufferRoiPtrType = blBuffer_4<double,blDataPtr,blBufferPtr,blMaxNumOfDimensions>;

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// blBuffer -- Class definition
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr = blDataType*,
         typename blBufferPtr = blBufferPtrType<blDataType,blMaxNumOfDimensions,blDataPtr>,
         typename blBufferRoiPtr = blBufferRoiPtrType<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr> >

class blBuffer : public blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>
{
public: // Constructors and destructors



    // Default constructor

    blBuffer();



    // Copy constructor

    blBuffer(const blBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>& buffer);



    // Destructor

    ~blBuffer();
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

inline blBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::blBuffer() : blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

inline blBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::blBuffer(const blBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>& buffer)
                                                                                                : blBuffer_8<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>(buffer)
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr>

inline blBuffer<blDataType,blMaxNumOfDimensions,blDataPtr,blBufferPtr,blBufferRoiPtr>::~blBuffer()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_HPP
