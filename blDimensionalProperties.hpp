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
//                  -- The dimensional lengths are stored in an array
//                     where the array length (which is a template parameter)
//                     determines the number of dimensions of the space
//                     that is being represented
//
//                  -- For example a 2d image has 2 dimensions and thus the
//                     vector "m_sizes" would have components m_sizes[0] for
//                     the length of the 1st dimension and component m_sizes[1]
//                     for the length of the 2nd dimension
//
//                  -- The class also defines multi-dimensional offsets that
//                     can be used to represent "Regions Of Interest" (ROIs)
//                     for a buffer so that functions can work on user specified
//                     parts of the buffer and not the entire data
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
template<std::size_t blNumberOfDimensions>

class blDimensionalProperties
{
public: // Constructors and destructors



    // Default constructor

    blDimensionalProperties();



    // Copy constructor

    blDimensionalProperties(const blDimensionalProperties<blNumberOfDimensions>& bufferSizes) = default;



    // Destructor

    ~blDimensionalProperties();



public: // Overloaded operators



    // Assignment operator

    blDimensionalProperties<blNumberOfDimensions>&          operator=(const blDimensionalProperties<blNumberOfDimensions>& bufferSizes) = default;



public: // Sizes/Lengths functions



    // Functions used to get the
    // current total size/length
    // of the buffer
    // size0 * size1 * size2 * ... * sizeN

    const std::size_t&                                      size()const;
    const std::size_t&                                      length()const;



    // Function used to get the
    // size of a subdimension
    // For example if we are
    // talking about a 3d space
    // (rows x cols x pages)
    // then the size of a single
    // page is rows x cols, the
    // size of a col is rows and
    // the size of a row is 1

    std::size_t                                             sizeOfSingleUnitInSpecificDimension(const std::size_t& whichDimension)const;



    // Function used to get the
    // sizes/lengths vector

    const std::array<std::size_t,blNumberOfDimensions>&     sizes()const;
    const std::array<std::size_t,blNumberOfDimensions>&     lengths()const;



    // Function used to get a length
    // for a specific dimension, we
    // also define special functions
    // used to get the lengths of the
    // first 3 dimensions

    const std::size_t&                                      size(const std::size_t& dimension)const;
    const std::size_t&                                      length(const std::size_t& dimension)const;

    const std::size_t&                                      height()const;
    const std::size_t&                                      width()const;
    const std::size_t&                                      depth()const;

    const std::size_t&                                      rows()const;
    const std::size_t&                                      cols()const;
    const std::size_t&                                      pages()const;



    // These functions are used to
    // manually set the dimensional
    // sizes of the data, useful when
    // wrapping data from an external
    // source

    void                                                    setDimensionalSizes();

    template<typename...Lengths>
    void                                                    setDimensionalSizes(const Lengths&...bufferLengths);

    template<typename blIntegerType>
    void                                                    setDimensionalSizes(const std::initializer_list<blIntegerType>& bufferLengths);

    template<typename blIntegerType>
    void                                                    setDimensionalSizes(const std::vector<blIntegerType>& bufferLengths);

    template<typename blIntegerType,
             std::size_t blDifferentNumberOfDimensions>
    void                                                    setDimensionalSizes(const std::array<blIntegerType,blDifferentNumberOfDimensions>& bufferLengths);

    void                                                    setDimensionalSize(const std::size_t& whichDimensionalSize,
                                                                               const std::size_t& dimensionalSize);



    // These functions are used to
    // manually set the offsets for
    // a Region Of Interest (ROI)

    void                                                    setOffsets();

    template<typename...Offsets>
    void                                                    setOffsets(const Offsets&...bufferOffsets);

    template<typename blIntegerType>
    void                                                    setOffsets(const std::initializer_list<blIntegerType>& bufferOffsets);

    template<typename blIntegerType>
    void                                                    setOffsets(const std::vector<blIntegerType>& bufferOffsets);

    template<typename blIntegerType,
             std::size_t blDifferentNumberOfDimensions>
    void                                                    setOffsets(const std::array<blIntegerType,blDifferentNumberOfDimensions>& bufferOffsets);

    void                                                    setOffset(const std::size_t& whichOffset,
                                                                      const std::size_t& offset);



    // Functions used to get
    // the ROI offsets

    const std::array<std::size_t,blNumberOfDimensions>&     offsets()const;
    const std::size_t&                                      offset(const std::size_t& whichOffset)const;


    // Functions used to get
    // the offsets in specific
    // dimensions

    const std::size_t&                                      rowOffset()const;
    const std::size_t&                                      colOffset()const;
    const std::size_t&                                      pageOffset()const;



private: // Private function used to
         // calculate the total size
         // of the buffer

    void                                                    calculateTotalSizeOfBuffer();




protected: // Protected variables



    // Vector holding the lengths of
    // the buffer in each dimension

    std::array<std::size_t,blNumberOfDimensions>            m_sizes;



    // Total length of the buffer
    // size0 * size1 * size2 * ... * sizeN

    std::size_t                                             m_size;



    // Total length of a single
    // unit for each dimension

    std::array<std::size_t,blNumberOfDimensions>            m_sizesOfSingleUnitsInEachDimenion;



    // Offsets that could be used to represent
    // a Region Of Interest (ROI) of a buffer,
    // where these offsets would be the starting
    // coordinates of the ROI

    std::array<std::size_t,blNumberOfDimensions>            m_offsets;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<std::size_t blNumberOfDimensions>

inline blDimensionalProperties<blNumberOfDimensions>::blDimensionalProperties()
{
    // We default all sizes/offsets to zero

    m_size = 0;

    for(auto& i : m_sizes)
        i = 0;

    for(auto& i: m_sizesOfSingleUnitsInEachDimenion)
        i = 0;

    for(auto& i : m_offsets)
        i = 0;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<std::size_t blNumberOfDimensions>

inline blDimensionalProperties<blNumberOfDimensions>::~blDimensionalProperties()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to manually set the
// dimensional sizes of the buffer, useful
// when wrapping data from an external
// source
//-------------------------------------------------------------------
template<std::size_t blNumberOfDimensions>

inline void blDimensionalProperties<blNumberOfDimensions>::setDimensionalSizes()
{
    // Since the user did not specify
    // any dimensional sizes, we default
    // them all to zero

    for(auto& i : m_sizes)
        i = static_cast<std::size_t>(0);



    // Finally we calculate the total
    // length of the buffer

    calculateTotalSizeOfBuffer();
}



template<std::size_t blNumberOfDimensions>

template<typename...Lengths>

inline void blDimensionalProperties<blNumberOfDimensions>::setDimensionalSizes(const Lengths&...bufferLengths)
{
    setDimensionalSizes({bufferLengths...});
}



template<std::size_t blNumberOfDimensions>

template<typename blIntegerType>

inline void blDimensionalProperties<blNumberOfDimensions>::setDimensionalSizes(const std::initializer_list<blIntegerType>& bufferLengths)
{
    // Because more sizes could have been
    // specified than the allowed number of
    // sizes, we loop through the first
    // sizes

    auto sizesSourceIter = bufferLengths.begin();
    auto sizesDestIter = m_sizes.begin();



    for(int i = 0;
        sizesSourceIter != bufferLengths.end() && sizesDestIter != m_sizes.end();
        ++sizesSourceIter,++sizesDestIter,++i)
    {
        *sizesDestIter = static_cast<std::size_t>(*sizesSourceIter);
    }



    // We default the remaining sizes
    // to one if they were not specified
    // here

    for(;
        sizesDestIter != m_sizes.end();
        ++sizesDestIter)
    {
        *sizesDestIter = static_cast<std::size_t>(1);
    }



    // Finally we calculate the total
    // length of the buffer

    calculateTotalSizeOfBuffer();
}



template<std::size_t blNumberOfDimensions>

template<typename blIntegerType>

inline void blDimensionalProperties<blNumberOfDimensions>::setDimensionalSizes(const std::vector<blIntegerType>& bufferLengths)
{
    // Because more sizes could have been
    // specified than the allowed number of
    // sizes, we loop through the first
    // sizes

    auto sizesSourceIter = bufferLengths.begin();
    auto sizesDestIter = m_sizes.begin();



    for(int i = 0;
        sizesSourceIter != bufferLengths.end() && sizesDestIter != m_sizes.end();
        ++sizesSourceIter,++sizesDestIter,++i)
    {
        *sizesDestIter = static_cast<std::size_t>(*sizesSourceIter);
    }



    // We default the remaining sizes
    // to one if they were not specified
    // here

    for(;
        sizesDestIter != m_sizes.end();
        ++sizesDestIter)
    {
        *sizesDestIter = static_cast<std::size_t>(1);
    }



    // Finally we calculate the total
    // length of the buffer

    calculateTotalSizeOfBuffer();
}



template<std::size_t blNumberOfDimensions>

template<typename blIntegerType,
         std::size_t blDifferentNumberOfDimensions>

inline void blDimensionalProperties<blNumberOfDimensions>::setDimensionalSizes(const std::array<blIntegerType,blDifferentNumberOfDimensions>& bufferLengths)
{
    // Because more sizes could have been
    // specified than the allowed number of
    // sizes, we loop through the first
    // sizes

    auto sizesSourceIter = bufferLengths.begin();
    auto sizesDestIter = m_sizes.begin();



    for(int i = 0;
        sizesSourceIter != bufferLengths.end() && sizesDestIter != m_sizes.end();
        ++sizesSourceIter,++sizesDestIter,++i)
    {
        *sizesDestIter = static_cast<std::size_t>(*sizesSourceIter);
    }



    // We default the remaining sizes
    // to one if they were not specified
    // here

    for(;
        sizesDestIter != m_sizes.end();
        ++sizesDestIter)
    {
        *sizesDestIter = static_cast<std::size_t>(1);
    }



    // Finally we calculate the total
    // length of the buffer

    calculateTotalSizeOfBuffer();
}



template<std::size_t blNumberOfDimensions>

inline void blDimensionalProperties<blNumberOfDimensions>::setDimensionalSize(const std::size_t& whichDimensionalSize,
                                                                              const std::size_t& dimensionalSize)
{
    // First we set the
    // dimenaional size

    m_sizes[whichDimensionalSize] = dimensionalSize;



    // Then we calculate the
    // total size of the buffer

    calculateTotalSizeOfBuffer();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
//These functions are used to
// manually set the offsets for
// a Region Of Interest (ROI)
//-------------------------------------------------------------------
template<std::size_t blNumberOfDimensions>

inline void blDimensionalProperties<blNumberOfDimensions>::setOffsets()
{
    // Since the user did not specify
    // any offsets, we default
    // them all to zero

    for(auto& i : m_offsets)
        i = static_cast<std::size_t>(0);



    // Finally we calculate the total
    // length of the buffer

    calculateTotalSizeOfBuffer();
}



template<std::size_t blNumberOfDimensions>

template<typename...Offsets>

inline void blDimensionalProperties<blNumberOfDimensions>::setOffsets(const Offsets&...bufferOffsets)
{
    setOffsets({bufferOffsets...});
}



template<std::size_t blNumberOfDimensions>

template<typename blIntegerType>

inline void blDimensionalProperties<blNumberOfDimensions>::setOffsets(const std::initializer_list<blIntegerType>& bufferOffsets)
{
    // Because more offsets could have been
    // specified than the allowed number of
    // offsets, we loop through the first
    // offsets

    auto offsetsSourceIter = bufferOffsets.begin();
    auto offsetsDestIter = m_offsets.begin();



    for(int i = 0;
        offsetsSourceIter != bufferOffsets.end() && offsetsDestIter != m_offsets.end();
        ++offsetsSourceIter,++offsetsDestIter,++i)
    {
        *offsetsDestIter = static_cast<std::size_t>(*offsetsSourceIter);
    }



    // We default the remaining offsets
    // to zero if they were not specified
    // here

    for(;
        offsetsDestIter != m_offsets.end();
        ++offsetsDestIter)
    {
        *offsetsDestIter = static_cast<std::size_t>(0);
    }



    // Finally we calculate the total
    // length of the buffer

    calculateTotalSizeOfBuffer();
}



template<std::size_t blNumberOfDimensions>

template<typename blIntegerType>

inline void blDimensionalProperties<blNumberOfDimensions>::setOffsets(const std::vector<blIntegerType>& bufferOffsets)
{
    // Because more offsets could have been
    // specified than the allowed number of
    // offsets, we loop through the first
    // offsets

    auto offsetsSourceIter = bufferOffsets.begin();
    auto offsetsDestIter = m_offsets.begin();



    for(int i = 0;
        offsetsSourceIter != bufferOffsets.end() && offsetsDestIter != m_offsets.end();
        ++offsetsSourceIter,++offsetsDestIter,++i)
    {
        *offsetsDestIter = static_cast<std::size_t>(*offsetsSourceIter);
    }



    // We default the remaining offsets
    // to zero if they were not specified
    // here

    for(;
        offsetsDestIter != m_offsets.end();
        ++offsetsDestIter)
    {
        *offsetsDestIter = static_cast<std::size_t>(0);
    }



    // Finally we calculate the total
    // length of the buffer

    calculateTotalSizeOfBuffer();
}



template<std::size_t blNumberOfDimensions>

template<typename blIntegerType,
         std::size_t blDifferentNumberOfDimensions>

inline void blDimensionalProperties<blNumberOfDimensions>::setOffsets(const std::array<blIntegerType,blDifferentNumberOfDimensions>& bufferOffsets)
{
    // Because more offsets could have been
    // specified than the allowed number of
    // offsets, we loop through the first
    // offsets

    auto offsetsSourceIter = bufferOffsets.begin();
    auto offsetsDestIter = m_offsets.begin();



    for(int i = 0;
        offsetsSourceIter != bufferOffsets.end() && offsetsDestIter != m_offsets.end();
        ++offsetsSourceIter,++offsetsDestIter,++i)
    {
        *offsetsDestIter = static_cast<std::size_t>(*offsetsSourceIter);
    }



    // We default the remaining offsets
    // to zero if they were not specified
    // here

    for(;
        offsetsDestIter != m_offsets.end();
        ++offsetsDestIter)
    {
        *offsetsDestIter = static_cast<std::size_t>(0);
    }



    // Finally we calculate the total
    // length of the buffer

    calculateTotalSizeOfBuffer();
}



template<std::size_t blNumberOfDimensions>

inline void blDimensionalProperties<blNumberOfDimensions>::setOffset(const std::size_t& whichOffset,
                                                                     const std::size_t& offset)
{
    m_offsets[whichOffset] = offset;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function use to get the ROI offsets
//-------------------------------------------------------------------
template<std::size_t blNumberOfDimensions>

inline const std::array<std::size_t,blNumberOfDimensions>& blDimensionalProperties<blNumberOfDimensions>::offsets()const
{
    return m_offsets;
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::offset(const std::size_t& whichOffset)const
{
    return m_offsets[whichOffset];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::rowOffset()const
{
    return m_offsets[0];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::colOffset()const
{
    return m_offsets[1];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::pageOffset()const
{
    return m_offsets[2];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to return the sizes vector
//-------------------------------------------------------------------
template<std::size_t blNumberOfDimensions>

inline const std::array<std::size_t,blNumberOfDimensions>& blDimensionalProperties<blNumberOfDimensions>::sizes()const
{
    return m_sizes;
}



template<std::size_t blNumberOfDimensions>

inline const std::array<std::size_t,blNumberOfDimensions>& blDimensionalProperties<blNumberOfDimensions>::lengths()const
{
    return m_sizes;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to get the size of
// an individual dimension
//-------------------------------------------------------------------
template<std::size_t blNumberOfDimensions>

inline std::size_t blDimensionalProperties<blNumberOfDimensions>::sizeOfSingleUnitInSpecificDimension(const std::size_t& whichDimension)const
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
template<std::size_t blNumberOfDimensions>

inline void blDimensionalProperties<blNumberOfDimensions>::calculateTotalSizeOfBuffer()
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



    // Finally, we calculate the size
    // of a single unit in each dimension
    // For example if we are talking about
    // a 3d space (rows x cols x pages), then
    // the size of a single page unit  is rows x cols,
    // the size of a single column unit is rows
    // the size of single a row unit is 1

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
template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::size()const
{
    return m_size;
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::length()const
{
    return m_size;
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::size(const std::size_t& dimension)const
{
    return m_sizes[dimension];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::length(const std::size_t& dimension)const
{
    return m_sizes[dimension];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::height()const
{
    return m_sizes[0];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::width()const
{
    return m_sizes[1];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::depth()const
{
    return m_sizes[2];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::rows()const
{
    return m_sizes[0];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::cols()const
{
    return m_sizes[1];
}



template<std::size_t blNumberOfDimensions>

inline const std::size_t& blDimensionalProperties<blNumberOfDimensions>::pages()const
{
    return m_sizes[2];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_DIMENSIONALPROPERTIES_HPP
