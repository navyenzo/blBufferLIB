#ifndef BL_DIMENSIONALPROPERTIES_HPP
#define BL_DIMENSIONALPROPERTIES_HPP


//-------------------------------------------------------------------
// FILE:            blDimensionalProperties.hpp
// CLASS:           blDimensionalProperties
// BASE CLASS:      None
//
//
//
// PURPOSE:         -- This class defines multi-dimensional sizes/lengths
//                     that can be used to define an n-dimensional
//                     contiguous buffer
//
//                  -- The dimensional lengths are stored in a vector
//                     and the vector length determines the number
//                     of dimensions of the space that is being represented
//
//                  -- For example a 2d image has 2 dimensions and thus the
//                     vector "m_sizes" would have components m_sizes[0] for
//                     the length of the 1st dimension and component m_sizes[1]
//                     for the length of the 2nd dimension
//
//                  -- This class defines multiple redundant functions
//                     with common names for the first 3 dimensions
//                     such as (rows,cols,pages), (size1,size2,size3),
//                     (length1,length2,length3), (height,width,depth)
//
//                  -- The functions used to get the length of a dimension
//                     do not check whether the length for that dimension
//                     has been specified, thus use with care
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
// LISENSE:         MIT-LICENCE
//                  http://www.opensource.org/licenses/mit-license.php
//
//
//
// DEPENDENCIES:    -- C++17 -- This class and derived classes will
//                              make heavy use of C++11 structures
//                              and algorithms and some C++17 features
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Includes and libs needed for this file
//-------------------------------------------------------------------

// Used as the maindynamic
// array for the buffer

#include <vector>

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blDimensionalProperties declaration
//-------------------------------------------------------------------
class blDimensionalProperties
{
public: // Constructors and destructors



    // Default constructor

    blDimensionalProperties();



    // Copy constructor

    blDimensionalProperties(const blDimensionalProperties& bufferSizes) = default;



    // Destructor

    ~blDimensionalProperties();



public: // Overloaded operators



    // Assignment operator

    blDimensionalProperties&                operator=(const blDimensionalProperties& bufferSizes) = default;



public: // Sizes/Lengths functions



    // Functions used to get the
    // current total size/length
    // of the buffer

    const std::size_t&                      size()const;
    const std::size_t&                      length()const;



    // Function used to get the
    // size of a subdimension
    // For example if we are
    // talking about a 3d space
    // (rows x cols x pages)
    // then the size of a single
    // page is rows x cols, the
    // size of a col is rows and
    // the size of a row is 1

    std::size_t                             sizeOfSingleUnitInSpecificDimension(const std::size_t& whichDimension)const;



    // Function used to get the
    // sizes/lengths vector

    const std::vector<std::size_t>&         sizes()const;
    const std::vector<std::size_t>&         lengths()const;



    // Functions used to get the
    // number of dimensions that
    // this buffer's data lives in

    const std::size_t&                      dimensions()const;



    // Function used to get a length
    // for a specific dimension, we
    // also define special functions
    // used to get the lengths of the
    // first 3 dimensions

    const std::size_t&                      size(const std::size_t& dimension)const;
    const std::size_t&                      length(const std::size_t& dimension)const;

    const std::size_t&                      height()const;
    const std::size_t&                      width()const;
    const std::size_t&                      depth()const;

    const std::size_t&                      rows()const;
    const std::size_t&                      cols()const;
    const std::size_t&                      pages()const;



    // These functions are used to
    // manually set the dimensional
    // sizes of the data, useful when
    // wrapping data from an external
    // source

    template<typename...Lengths>
    void                                    setDimensionalSizes(const Lengths&...bufferLengths);
    void                                    setDimensionalSizes(const std::initializer_list<std::size_t>& bufferLengths);
    void                                    setDimensionalSizes(const std::vector<std::size_t>& bufferLengths);



    // These functions are used to
    // manually set the offsets for
    // a Region Of Interest (ROI)

    template<typename...Offsets>
    void                                    setOffsets(const Offsets&...bufferOffsets);
    void                                    setOffsets(const std::initializer_list<std::size_t>& bufferOffsets);
    void                                    setOffsets(const std::vector<std::size_t>& bufferOffsets);

    void                                    setOffset(const std::size_t& whichOffset,
                                                      const std::size_t& offset);



    // Functions used to get
    // the ROI offsets

    const std::vector<std::size_t>&         offsets()const;
    const std::size_t&                      offset(const std::size_t& whichOffset)const;


    // Functions used to get
    // the offsets in specific
    // dimensions

    const std::size_t&                      rowOffset()const;
    const std::size_t&                      colOffset()const;
    const std::size_t&                      pageOffset()const;



private: // Private function used to
         // calculate the total size
         // of the buffer

    void                                    calculateTotalSizeOfBufferAndDefaultMissingOffsets();




protected: // Protected variables



    // Vector holding the lengths of
    // the buffer in each dimension

    std::vector<std::size_t>                m_sizes;



    // Total length of the buffer

    std::size_t                             m_size;



    // Number of dimensions of
    // the space represented by
    // these properties

    std::size_t                             m_dimensions;



    // Total length of a single
    // unit for each dimension

    std::vector<std::size_t>                m_sizesOfSingleUnitsInEachDimenion;



    // Offsets that could be used to represent
    // a Region Of Interest (ROI) of a buffer,
    // where these offsets would be the starting
    // coordinates of the ROI

    std::vector<std::size_t>                m_offsets;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
inline blDimensionalProperties::blDimensionalProperties()
{
    // We default the buffer
    // to an empty buffer that
    // doesn't wrap any external
    // data

    std::vector<std::size_t> emptyVector;

    m_sizes = emptyVector;
    m_sizesOfSingleUnitsInEachDimenion = emptyVector;
    m_offsets = emptyVector;

    m_size = 0;
    m_dimensions = 0;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
inline blDimensionalProperties::~blDimensionalProperties()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to manually set the
// dimensional sizes of the buffer, useful
// when wrapping data from an external
// source
//-------------------------------------------------------------------
template<typename...Lengths>
inline void blDimensionalProperties::setDimensionalSizes(const Lengths&...bufferLengths)
{
    // First we initialize
    // the sizes vector

    m_sizes = {static_cast<std::size_t>(bufferLengths)...};



    // Then we calculate the
    // total size of the buffer

    calculateTotalSizeOfBufferAndDefaultMissingOffsets();
}



inline void blDimensionalProperties::setDimensionalSizes(const std::initializer_list<std::size_t>& bufferLengths)
{
    // First we initialize
    // the sizes vector

    m_sizes = bufferLengths;



    // Then we calculate the
    // total size of the buffer

    calculateTotalSizeOfBufferAndDefaultMissingOffsets();
}



inline void blDimensionalProperties::setDimensionalSizes(const std::vector<std::size_t>& bufferLengths)
{
    // First we copy the
    // sizes vector

    m_sizes = bufferLengths;



    // Then we calculate the
    // total size of the buffer

    calculateTotalSizeOfBufferAndDefaultMissingOffsets();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
//These functions are used to
// manually set the offsets for
// a Region Of Interest (ROI)
//-------------------------------------------------------------------
template<typename...Offsets>
inline void blDimensionalProperties::setOffsets(const Offsets&...bufferOffsets)
{
    // First we set the offsets

    m_offsets = {static_cast<std::size_t>(bufferOffsets)...};

    calculateTotalSizeOfBufferAndDefaultMissingOffsets();
}



inline void blDimensionalProperties::setOffsets(const std::initializer_list<std::size_t>& bufferOffsets)
{
    m_offsets = bufferOffsets;

    calculateTotalSizeOfBufferAndDefaultMissingOffsets();
}



inline void blDimensionalProperties::setOffsets(const std::vector<std::size_t>& bufferOffsets)
{
    m_offsets = bufferOffsets;

    calculateTotalSizeOfBufferAndDefaultMissingOffsets();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function use to get the ROI offsets
//-------------------------------------------------------------------
inline const std::vector<std::size_t>& blDimensionalProperties::offsets()const
{
    return m_offsets;
}



inline const std::size_t& blDimensionalProperties::offset(const std::size_t& whichOffset)const
{
    return m_offsets[whichOffset];
}



inline const std::size_t& blDimensionalProperties::rowOffset()const
{
    return m_offsets[0];
}



inline const std::size_t& blDimensionalProperties::colOffset()const
{
    return m_offsets[1];
}



inline const std::size_t& blDimensionalProperties::pageOffset()const
{
    return m_offsets[2];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to return the number of
// dimensions that this data lives in
//-------------------------------------------------------------------
inline const std::size_t& blDimensionalProperties::dimensions()const
{
    return m_dimensions;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the size of
// an individual dimension
//-------------------------------------------------------------------
inline std::size_t blDimensionalProperties::sizeOfSingleUnitInSpecificDimension(const std::size_t& whichDimension)const
{
    std::size_t unitSize = 1;

    for(std::size_t i = 0; i < whichDimension; ++i)
        unitSize *= m_sizes[i];

    return unitSize;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to calculate the
// total length of the buffer
//-------------------------------------------------------------------
inline void blDimensionalProperties::calculateTotalSizeOfBufferAndDefaultMissingOffsets()
{
    // First we calculate the
    // overall buffer size
    // depending on the specified
    // buffer lengths

    if(m_sizes.size() == 0)
        m_size = 0;
    else
        m_size = 1;



    for(const std::size_t& dimensionalSize : m_sizes)
        m_size *= dimensionalSize;



    // Store the number of dimensions

    m_dimensions = m_sizes.size();



    // If we have more dimensions than
    // the number of offsets specified,
    // we set those offsets to zero

    if(m_dimensions > m_offsets.size())
        m_offsets.resize(m_dimensions,std::size_t(0));



    // Finally, we calculate the size
    // of a single unit in each dimension
    // For example if we are talking about
    // a 3d space (rows x cols x pages), then
    // the size of a single page unit  is rows x cols,
    // the size of a single column unit is rows
    // the size of single a row unit is 1

    m_sizesOfSingleUnitsInEachDimenion.resize(m_sizes.size());

    for(std::size_t i = 0; i < m_sizes.size(); ++i)
    {
        m_sizesOfSingleUnitsInEachDimenion[i] = 1;

        for(std::size_t j = 0; j < i; ++j)
        {
            m_sizesOfSingleUnitsInEachDimenion[i] *= m_sizes[j];
        }
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Length/Size functions
//-------------------------------------------------------------------
inline const std::size_t& blDimensionalProperties::size()const
{
    return m_size;
}



inline const std::size_t& blDimensionalProperties::length()const
{
    return m_size;
}



inline const std::size_t& blDimensionalProperties::size(const std::size_t& dimension)const
{
    return m_sizes[dimension];
}



inline const std::size_t& blDimensionalProperties::length(const std::size_t& dimension)const
{
    return m_sizes[dimension];
}



inline const std::size_t& blDimensionalProperties::height()const
{
    return m_sizes[0];
}



inline const std::size_t& blDimensionalProperties::width()const
{
    return m_sizes[1];
}



inline const std::size_t& blDimensionalProperties::depth()const
{
    return m_sizes[2];
}



inline const std::size_t& blDimensionalProperties::rows()const
{
    return m_sizes[0];
}



inline const std::size_t& blDimensionalProperties::cols()const
{
    return m_sizes[1];
}



inline const std::size_t& blDimensionalProperties::pages()const
{
    return m_sizes[2];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_DIMENSIONALPROPERTIES_HPP
