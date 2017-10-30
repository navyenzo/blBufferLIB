#ifndef BL_BUFFER_0_HPP
#define BL_BUFFER_0_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer_0.hpp
// CLASS:           blBuffer_0
// BASE CLASS:      None
//
//
//
// PURPOSE:         -- Base class used to define a generic contiguous
//                     buffer with the additional concept of "sizes/lengths"
//
//                  -- The additional concept of "lengths", as in length0,
//                     length1, length2...lengthN-1 gives the user of
//                     this buffer the ability to see it as an N-dimensional
//                     buffer
//
//                  -- The dimensional lengths are stored in a
//                     blDimensionalProperties<blMaxNumOfDimensions> structure
//
//                  -- This class is defined within the namespace "blBufferLIB"
//
//
//
// AUTHOR:          Vincenzo Barbato
//                  navyenzo@gmail.com
//
//
//
// LISENSE:         MIT-LICENSE
//                  http://www.opensource.org/licenses/mit-license.php
//
//
//
// DEPENDENCIES:    -- blBuffer_2 and all its dependencies
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

// Used to define dimensional
// buffer sizes

#include "blDimensionalProperties.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blBuffer_0 declaration
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions>

class blBuffer_0
{
public: // Constructors and destructors



    // Default constructor

    blBuffer_0();



    // Copy constructor

    blBuffer_0(const blBuffer_0<blDataType,blMaxNumOfDimensions>& buffer0) = default;



    // Destructor

    ~blBuffer_0();



public: // Overloaded operators



    // Assignment operator

    blBuffer_0<blDataType,blMaxNumOfDimensions>&                operator=(const blBuffer_0<blDataType,blMaxNumOfDimensions>& buffer0) = default;



public: // Public functions



    // Functions used to get the
    // buffer's dimensional properties

    const blDimensionalProperties<blMaxNumOfDimensions>&        properties()const;

    const std::size_t&                                          size()const;
    const std::size_t&                                          size(const std::size_t& dimension)const;

    const std::size_t&                                          length()const;
    const std::size_t&                                          length(const std::size_t& dimension)const;




protected: // Protected variables



    // The main dynamic array
    // holding the buffer data
    // if the buffer owns the
    // data

    std::vector<blDataType>                                     m_data;



    // The dimensional properties
    // of this buffer

    blDimensionalProperties<blMaxNumOfDimensions>               m_properties;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions>

inline blBuffer_0<blDataType,blMaxNumOfDimensions>::blBuffer_0()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions>

inline blBuffer_0<blDataType,blMaxNumOfDimensions>::~blBuffer_0()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the buffer's properties
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions>

inline const blDimensionalProperties<blMaxNumOfDimensions>& blBuffer_0<blDataType,blMaxNumOfDimensions>::properties()const
{
    return m_properties;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get the total size
// of the buffer without having to first
// get the buffer's properties
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions>

inline const std::size_t& blBuffer_0<blDataType,blMaxNumOfDimensions>::size()const
{
    return m_properties.size();
}



template<typename blDataType,
         std::size_t blMaxNumOfDimensions>

inline const std::size_t& blBuffer_0<blDataType,blMaxNumOfDimensions>::length()const
{
    return m_properties.size();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the size of
// a specified buffer dimension without
// having to first get the buffer's properties
//-------------------------------------------------------------------
template<typename blDataType,
         std::size_t blMaxNumOfDimensions>

inline const std::size_t& blBuffer_0<blDataType,blMaxNumOfDimensions>::size(const std::size_t&  dimension)const
{
    return m_properties.size(dimension);
}



template<typename blDataType,
         std::size_t blMaxNumOfDimensions>

inline const std::size_t& blBuffer_0<blDataType,blMaxNumOfDimensions>::length(const std::size_t&  dimension)const
{
    return m_properties.size(dimension);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_0_HPP
