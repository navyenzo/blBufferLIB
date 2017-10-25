#ifndef BL_BUFFER_4_HPP
#define BL_BUFFER_4_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer_4.hpp
// CLASS:           blBuffer_4
// BASE CLASS:      blBuffer_3
//
//
//
// PURPOSE:         -- This class is based on blBuffer_3 and adds
//                     a Region Of Interest (m_roi)
//
//                  -- For a ROI that does not span the entire buffer
//                     with coordinates (row1,col1,page1) to (row2,col2,page2)
//                     also known as (y1,x1,z1) to (y2,x2,z2)
//                     -- For a 1d-buffer the ROI is contiguous
//                     -- For 2d-buffer the ROI is made of (row2 - row1) separate
//                        contiguous pieces
//                     -- For 3d-buffer the ROI is made of (row2 - row1)*(page2 - page1)
//                        separate contiguous pieces
//                     -- And so on for higher nd-buffers
//
//                  -- This class is defined within the blBufferLIB
//                     namespace
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

#include "blBuffer_3.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blBuffer_4 declaration
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

class blBuffer_4 : public blBuffer_3<blDataType,blDataPtr,blBufferPtr>
{
public: // Constructors and destructors



    // Default constructor

    blBuffer_4();



    // Copy constructor

    blBuffer_4(const blBuffer_4<blDataType,blDataPtr,blBufferPtr>& buffer0) = default;



    // Destructor

    ~blBuffer_4();



public: // Overloaded operators



    // Assignment operator

    blBuffer_4<blDataType,blDataPtr,blBufferPtr>&           operator=(const blBuffer_4<blDataType,blDataPtr,blBufferPtr>& buffer0) = default;



public: // Public functions



    // The get/set functions for the ROI

    blDimensionalProperties&                                roi();
    const blDimensionalProperties&                          roi()const;



    // Function used to reset the
    // ROI so that it points to
    // the entire buffer

    void                                                    resetROI();



    // "at" functions which do the same
    // thing as the operator(), they still
    // do not check for out of bound indexes

    template<typename blIntegerType>
    blDataType&                                             roi_at(const blIntegerType& dataIndex);

    template<typename blIntegerType>
    const blDataType&                                       roi_at(const blIntegerType& dataIndex)const;

    template<typename blIntegerType>
    blDataType&                                             roi_at(const blIntegerType& rowIndex,
                                                                   const blIntegerType& colIndex);

    template<typename blIntegerType>
    const blDataType&                                       roi_at(const blIntegerType& rowIndex,
                                                                   const blIntegerType& colIndex)const;

    template<typename blIntegerType>
    blDataType&                                             roi_at(const blIntegerType& rowIndex,
                                                                   const blIntegerType& colIndex,
                                                                   const blIntegerType& pageIndex);

    template<typename blIntegerType>
    const blDataType&                                       roi_at(const blIntegerType& rowIndex,
                                                                   const blIntegerType& colIndex,
                                                                   const blIntegerType& pageIndex)const;



    // Generic version of
    // at functions

    template<typename...Indexes>
    blDataType&                                             roi_at(const Indexes&...dataIndexes);

    template<typename...Indexes>
    const blDataType&                                       roi_at(const Indexes&...dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                                             roi_at(const std::initializer_list<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                                       roi_at(const std::initializer_list<blIntegerType>& dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                                             roi_at(const std::vector<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                                       roi_at(const std::vector<blIntegerType>& dataIndexes)const;




protected: // Protected variables



    // The ROI

    blDimensionalProperties                                 m_roi;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline blBuffer_4<blDataType,blDataPtr,blBufferPtr>::blBuffer_4() : blBuffer_3<blDataType,blDataPtr,blBufferPtr>()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline blBuffer_4<blDataType,blDataPtr,blBufferPtr>::~blBuffer_4()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Get/Set functions for the ROI
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline blDimensionalProperties& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi()
{
    return m_roi;
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline const blDimensionalProperties& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi()const
{
    return m_roi;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to reset the ROI
// so that it points to the entire
// buffer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline void blBuffer_4<blDataType,blDataPtr,blBufferPtr>::resetROI()
{
    m_roi = this->m_properties;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// "at" functions (These function DO NOT check if the indexes
//                 are out of bounds)
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const blIntegerType& dataIndex)
{
    // Vector of indeces used to
    // address the correct data
    // point in the buffer

    std::vector<std::size_t> indexes(m_roi.dimensions(),std::size_t(0));



    // Here we calculate the coordinates
    // of the data point in our nd-buffer

    for(int i = static_cast<int>(indexes.size()) - 1; i >= 0 ; --i)
    {
        if(i == static_cast<int>(indexes.size()) - 1)
        {
            indexes[i] = dataIndex / m_roi.sizeOfSingleUnitInSpecificDimension(i);
        }
        else if(i > 0)
        {
            indexes[i] = (dataIndex - indexes[i + 1] * m_roi.sizeOfSingleUnitInSpecificDimension(i + 1)) / m_roi.sizeOfSingleUnitInSpecificDimension(i);
        }
        else
        {
            indexes[i] = dataIndex % m_roi.size(0);
            indexes[i] += m_roi.offset(0);

            break;
        }

        indexes[i] += m_roi.offset(i);
    }



    // Then we access the data point in the
    // buffer using the newly found ROI coordinates

    return this->at(indexes);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const blIntegerType& dataIndex)const
{
    // Vector of indeces used to
    // address the correct data
    // point in the buffer

    std::vector<std::size_t> indexes(m_roi.dimensions(),std::size_t(0));



    // Here we calculate the coordinates
    // of the data point in our nd-buffer

    for(int i = static_cast<int>(indexes.size()) - 1; i >= 0 ; --i)
    {
        if(i == static_cast<int>(indexes.size()) - 1)
        {
            indexes[i] = dataIndex / m_roi.sizeOfSingleUnitInSpecificDimension(i);
        }
        else if(i > 0)
        {
            indexes[i] = (dataIndex - indexes[i + 1] * m_roi.sizeOfSingleUnitInSpecificDimension(i + 1)) / m_roi.sizeOfSingleUnitInSpecificDimension(i);
        }
        else
        {
            indexes[i] = dataIndex % m_roi.size(0);
            indexes[i] += m_roi.offset(0);

            break;
        }

        indexes[i] += m_roi.offset(i);
    }



    // Then we access the data point in the
    // buffer using the newly found ROI coordinates

    return this->at(indexes);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const blIntegerType& rowIndex,
                                                                        const blIntegerType& colIndex)
{
    return this->at(rowIndex + m_roi.rowOffset(),colIndex + m_roi.colOffset());
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const blIntegerType& rowIndex,
                                                                              const blIntegerType& colIndex)const
{
    return this->at(rowIndex + m_roi.rowOffset(),colIndex + m_roi.colOffset());
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const blIntegerType& rowIndex,
                                                                        const blIntegerType& colIndex,
                                                                        const blIntegerType& pageIndex)
{
    return this->at(rowIndex + m_roi.rowOffset(),colIndex + m_roi.colOffset(),pageIndex + m_roi.pageOffset());
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const blIntegerType& rowIndex,
                                                                              const blIntegerType& colIndex,
                                                                              const blIntegerType& pageIndex)const
{
    return this->at(rowIndex + m_roi.rowOffset(),colIndex + m_roi.colOffset(),pageIndex + m_roi.pageOffset());
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Generic version of roi_at functions
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename...Indexes>

inline blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const Indexes&...dataIndexes)
{
    return this->roi_at({dataIndexes...});
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename...Indexes>

inline const blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const Indexes&...dataIndexes)const
{
    return this->roi_at({dataIndexes...});
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const std::initializer_list<blIntegerType>& dataIndexes)
{
    std::vector<std::size_t> offsettedDataIndexes(dataIndexes.begin(),dataIndexes.end());

    for(std::size_t i = 0; i < offsettedDataIndexes.size(); ++i)
        offsettedDataIndexes[i] += m_roi.offset(i);

    return this->at(offsettedDataIndexes);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const std::initializer_list<blIntegerType>& dataIndexes)const
{
    std::vector<std::size_t> offsettedDataIndexes(dataIndexes.begin(),dataIndexes.end());

    for(std::size_t i = 0; i < offsettedDataIndexes.size(); ++i)
        offsettedDataIndexes[i] += m_roi.offset(i);

    return this->at(offsettedDataIndexes);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const std::vector<blIntegerType>& dataIndexes)
{
    std::vector<std::size_t> offsettedDataIndexes(dataIndexes.begin(),dataIndexes.end());

    for(std::size_t i = 0; i < offsettedDataIndexes.size(); ++i)
        offsettedDataIndexes[i] += m_roi.offset(i);

    return this->at(offsettedDataIndexes);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_4<blDataType,blDataPtr,blBufferPtr>::roi_at(const std::vector<blIntegerType>& dataIndexes)const
{
    std::vector<std::size_t> offsettedDataIndexes(dataIndexes.begin(),dataIndexes.end());

    for(std::size_t i = 0; i < offsettedDataIndexes.size(); ++i)
        offsettedDataIndexes[i] += m_roi.offset(i);

    return this->at(offsettedDataIndexes);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_4_HPP
