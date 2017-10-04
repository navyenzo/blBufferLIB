#ifndef BL_BUFFER_HPP
#define BL_BUFFER_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer.hpp
// CLASS:           blBuffer
// BASE CLASS:      blBuffer0
//
// PURPOSE:         -- Based on blBuffer_N, where N is the last of
//                     the following classes:
//
//                     -- blBuffer_0
//                     -- blBuffer_2
//                     -- blBuffer_2
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
//                  -- The buffer and all its functions are defined
//                     within the blBufferLIB namespace.
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
// AUTHOR:          Vincenzo Barbato
//                  navyenzo@gmail.com
//
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
// DEPENDENCIES:    -- blBuffer4 and all its dependencies
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
template<typename blDataType>

class blBuffer : public blBuffer_8<blDataType>
{
public: // Constructors and destructors



    // Default constructor

    blBuffer();



    // Copy constructor

    blBuffer(const blBuffer<blDataType>& buffer);



    // Destructor

    ~blBuffer();
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blBuffer<blDataType>::blBuffer() : blBuffer_8<blDataType>()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blBuffer<blDataType>::blBuffer(const blBuffer<blDataType>& buffer) : blBuffer_8<blDataType>(buffer)
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
template<typename blDataType>
inline blBuffer<blDataType>::~blBuffer()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_HPP
