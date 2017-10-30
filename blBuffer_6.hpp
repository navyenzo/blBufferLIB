#ifndef BL_BUFFER_6_HPP
#define BL_BUFFER_6_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer_6.hpp
// CLASS:           blBuffer_6
// BASE CLASS:      blBuffer_5
//
// PURPOSE:         -- This class is based on blBuffer_5 and adds
//                     create functions used to create/initialize
//                     the buffer
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
// DEPENDENCIES:    -- blBuffer_5 and all its dependencies
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

#include "blBuffer_5.hpp"

#include "blRoiIterator.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blBuffer_6 declaration
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

class blBuffer_6 : public blBuffer_5<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>
{
public: // Constructors and destructors



    // Default constructor

    blBuffer_6();



    // Copy constructor

    blBuffer_6(const blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>& buffer6) = default;



    // Destructor

    ~blBuffer_6();



public: // Overloaded operators



    // Assignment operator

    blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>&   operator=(const blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>& buffer6) = default;



public: // Create functions used to
        // allocate the buffer memory



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

    template<typename...blIntegerType>
    bool                                                                    create(const blIntegerType&... bufferLengths);

    template<typename blIntegerType>
    bool                                                                    create(const std::initializer_list<blIntegerType>& bufferLengths);

    template<typename blIntegerType>
    bool                                                                    create(const std::vector<blIntegerType>& bufferLengths);

    template<typename blIntegerType,
             std::size_t blNumberOfDimensions>
    bool                                                                    create(const std::array<blIntegerType,blNumberOfDimensions>& bufferLengths);



private: // Create function that does the
         // actual work of allocating memory
         // This function gets called by the
         // other create functions

    bool                                                                    create();
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

inline blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::blBuffer_6() : blBuffer_5<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>()
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

inline blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::~blBuffer_6()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// create functions used to allocate and
// initialize space for the buffer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename...blIntegerType>

inline bool blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::create(const blIntegerType&...bufferLengths)
{
    this->m_properties.setDimensionalSizes({static_cast<std::size_t>(bufferLengths)...});

    return create();
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blIntegerType>

inline bool blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::create(const std::initializer_list<blIntegerType>& bufferLengths)
{
    this->m_properties.setDimensionalSizes(bufferLengths);

    return create();
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blIntegerType>

inline bool blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::create(const std::vector<blIntegerType>& bufferLengths)
{
    this->m_properties.setDimensionalSizes(bufferLengths);

    return create();
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

template<typename blIntegerType,
         std::size_t blNumberOfDimensions>

inline bool blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::create(const std::array<blIntegerType,blNumberOfDimensions>& bufferLengths)
{
    this->m_properties.setDimensionalSizes(bufferLengths);

    return create();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// create function used to allocate space for the buffer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr,
         typename blBufferRoiPtr,
         std::size_t blMaxNumOfDimensions>

inline bool blBuffer_6<blDataType,blDataPtr,blBufferPtr,blBufferRoiPtr,blMaxNumOfDimensions>::create()
{
    // First we try to allocate the
    // requested space

    this->m_data.resize(this->size());



    // Check to make sure we succeded

    bool wasAllocationSuccessful = (this->m_data.size() == this->size());

    if(!wasAllocationSuccessful)
    {
        // This means the allocation failed
        // so we reset the size to equal
        // the actual buffer size and default
        // all dimensional sizes to represent
        // a 1d buffer

        this->m_properties.setDimensionalSizes(this->m_data.size());
    }



    // Let's not forget to set the
    // begin/end iterators to their
    // default values

    this->resetDataPointers();



    // By default we set the ROI
    // to the entire buffer

    this->resetROI();



    // Let's not forget to let
    // the user know whether the
    // create function failed to
    // create the vector they expected

    return wasAllocationSuccessful;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_6_HPP
