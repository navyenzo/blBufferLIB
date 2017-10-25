#ifndef BL_BUFFER_2_HPP
#define BL_BUFFER_2_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer_2.hpp
// CLASS:           blBuffer_2
// BASE CLASS:      blBuffer_1
//
//
//
// PURPOSE:         -- This class is based on blBuffer_1 and adds
//                     access operators and access functions
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

#include "blBuffer_1.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blBuffer_2 declaration
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

class blBuffer_2 : public blBuffer_1<blDataType,blDataPtr>
{
public: // Constructors and destructors



    // Default constructor

    blBuffer_2();



    // Copy constructor

    blBuffer_2(const blBuffer_2<blDataType,blDataPtr>& buffer2) = default;



    // Destructor

    ~blBuffer_2();



public: // Overloaded operators



    // Assignment operator

    blBuffer_2<blDataType,blDataPtr>&               operator=(const blBuffer_2<blDataType,blDataPtr>& buffer2) = default;



public: // Access operators



    // operator[]

    template<typename blIntegerType>
    blDataType&                                     operator[](const blIntegerType& dataIndex);

    template<typename blIntegerType>
    const blDataType&                               operator[](const blIntegerType& dataIndex)const;



    // operator()

    template<typename blIntegerType>
    blDataType&                                     operator()(const blIntegerType& dataIndex);

    template<typename blIntegerType>
    const blDataType&                               operator()(const blIntegerType& dataIndex)const;

    template<typename blIntegerType>
    blDataType&                                     operator()(const blIntegerType& rowIndex,
                                                               const blIntegerType& colIndex);

    template<typename blIntegerType>
    const blDataType&                               operator()(const blIntegerType& rowIndex,
                                                               const blIntegerType& colIndex)const;

    template<typename blIntegerType>
    blDataType&                                     operator()(const blIntegerType& rowIndex,
                                                               const blIntegerType& colIndex,
                                                               const blIntegerType& pageIndex);

    template<typename blIntegerType>
    const blDataType&                               operator()(const blIntegerType& rowIndex,
                                                               const blIntegerType& colIndex,
                                                               const blIntegerType& pageIndex)const;



    // Generic version of
    // operator()

    template<typename...blIntegerTypes>
    blDataType&                                     operator()(const blIntegerTypes&...dataIndexes);

    template<typename...blIntegerTypes>
    const blDataType&                               operator()(const blIntegerTypes&...dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                                     operator()(const std::initializer_list<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                               operator()(const std::initializer_list<blIntegerType>& dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                                     operator()(const std::vector<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                               operator()(const std::vector<blIntegerType>& dataIndexes)const;



public: // Public functions



    // "at" functions which do the same
    // thing as the operator(), they still
    // do not check for out of bound indexes

    template<typename blIntegerType>
    blDataType&                                     at(const blIntegerType& dataIndex);

    template<typename blIntegerType>
    const blDataType&                               at(const blIntegerType& dataIndex)const;

    template<typename blIntegerType>
    blDataType&                                     at(const blIntegerType& rowIndex,
                                                       const blIntegerType& colIndex);

    template<typename blIntegerType>
    const blDataType&                               at(const blIntegerType& rowIndex,
                                                       const blIntegerType& colIndex)const;

    template<typename blIntegerType>
    blDataType&                                     at(const blIntegerType& rowIndex,
                                                       const blIntegerType& colIndex,
                                                       const blIntegerType& pageIndex);

    template<typename blIntegerType>
    const blDataType&                               at(const blIntegerType& rowIndex,
                                                       const blIntegerType& colIndex,
                                                       const blIntegerType& pageIndex)const;



    // Generic version of
    // at functions

    template<typename...blIntegerTypes>
    blDataType&                                     at(const blIntegerTypes&...dataIndexes);

    template<typename...blIntegerTypes>
    const blDataType&                               at(const blIntegerTypes&...dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                                     at(const std::initializer_list<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                               at(const std::initializer_list<blIntegerType>& dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                                     at(const std::vector<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                               at(const std::vector<blIntegerType>& dataIndexes)const;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blBuffer_2<blDataType,blDataPtr>::blBuffer_2() : blBuffer_1<blDataType,blDataPtr>()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blBuffer_2<blDataType,blDataPtr>::~blBuffer_2()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// operator[]
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::operator[](const blIntegerType& dataIndex)
{
    return this->data()[static_cast<std::size_t>(dataIndex)];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::operator[](const blIntegerType& dataIndex)const
{
    return this->data()[static_cast<std::size_t>(dataIndex)];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// operator()
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const blIntegerType& dataIndex)
{
    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const blIntegerType& dataIndex)const
{
    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const blIntegerType& rowIndex,
                                                                const blIntegerType& colIndex)
{
    return this->data()[colIndex * this->properties().rows() + rowIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const blIntegerType& rowIndex,
                                                                      const blIntegerType& colIndex)const
{
    return this->data()[colIndex * this->properties().rows() + rowIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const blIntegerType& rowIndex,
                                                                const blIntegerType& colIndex,
                                                                const blIntegerType& pageIndex)
{
    return this->data()[pageIndex * this->properties().cols() * this->properties().rows() + colIndex * this->properties().rows() + rowIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const blIntegerType& rowIndex,
                                                                      const blIntegerType& colIndex,
                                                                      const blIntegerType& pageIndex)const
{
    return this->data()[pageIndex * this->properties().cols() * this->properties().rows() + colIndex * this->properties().rows() + rowIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Generic versions of operator()
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

template<typename...blIntegerTypes>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const blIntegerTypes&...dataIndexes)
{
    return this->at({dataIndexes...});
}



template<typename blDataType,
         typename blDataPtr>

template<typename...blIntegerTypes>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const blIntegerTypes&...dataIndexes)const
{
    return this->at({dataIndexes...});
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const std::initializer_list<blIntegerType>& dataIndexes)
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = currentDataIndex;

        for(j = 0; j < i; ++j)
        {
            partialIndex *= this->size(j);
        }

        dataIndex += static_cast<std::size_t>(partialIndex);

        ++i;
    }



    // We've calculated the requested
    // index, so we return the data
    // point at the index in the buffer

    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const std::initializer_list<blIntegerType>& dataIndexes)const
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = currentDataIndex;

        for(j = 0; j < i; ++j)
        {
            partialIndex *= this->size(j);
        }

        dataIndex += static_cast<std::size_t>(partialIndex);

        ++i;
    }



    // We've calculated the requested
    // index, so we return the data
    // point at the index in the buffer

    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const std::vector<blIntegerType>& dataIndexes)
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = currentDataIndex;

        for(j = 0; j < i; ++j)
        {
            partialIndex *= this->size(j);
        }

        dataIndex += static_cast<std::size_t>(partialIndex);

        ++i;
    }



    // We've calculated the requested
    // index, so we return the data
    // point at the index in the buffer

    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::operator()(const std::vector<blIntegerType>& dataIndexes)const
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = currentDataIndex;

        for(j = 0; j < i; ++j)
        {
            partialIndex *= this->size(j);
        }

        dataIndex += static_cast<std::size_t>(partialIndex);

        ++i;
    }



    // We've calculated the requested
    // index, so we return the data
    // point at the index in the buffer

    return this->data()[dataIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// "at" functions (These function DO NOT check if the indexes
//                 are out of bounds)
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::at(const blIntegerType& dataIndex)
{
    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::at(const blIntegerType& dataIndex)const
{
    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::at(const blIntegerType& rowIndex,
                                                        const blIntegerType& colIndex)
{
    return this->data()[colIndex * this->properties().rows() + rowIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::at(const blIntegerType& rowIndex,
                                                              const blIntegerType& colIndex)const
{
    return this->data()[colIndex * this->properties().rows() + rowIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::at(const blIntegerType& rowIndex,
                                                        const blIntegerType& colIndex,
                                                        const blIntegerType& pageIndex)
{
    return this->data()[pageIndex * this->properties().cols() * this->properties().rows() + colIndex * this->properties().rows() + rowIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::at(const blIntegerType& rowIndex,
                                                              const blIntegerType& colIndex,
                                                              const blIntegerType& pageIndex)const
{
    return this->data()[pageIndex * this->properties().cols() * this->properties().rows() + colIndex * this->properties().rows() + rowIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Generic versions of at functions
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

template<typename...blIntegerTypes>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::at(const blIntegerTypes&...dataIndexes)
{
    return this->at({dataIndexes...});
}



template<typename blDataType,
         typename blDataPtr>

template<typename...blIntegerTypes>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::at(const blIntegerTypes&...dataIndexes)const
{
    return this->at({dataIndexes...});
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::at(const std::initializer_list<blIntegerType>& dataIndexes)
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = static_cast<std::size_t>(currentDataIndex);

        for(j = 0; j < i; ++j)
        {
            partialIndex *= this->size(j);
        }

        dataIndex += partialIndex;

        ++i;
    }



    // We've calculated the requested
    // index, so we return the data
    // point at the index in the buffer

    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::at(const std::initializer_list<blIntegerType>& dataIndexes)const
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = static_cast<std::size_t>(currentDataIndex);

        for(j = 0; j < i; ++j)
        {
            partialIndex *= this->size(j);
        }

        dataIndex += partialIndex;

        ++i;
    }



    // We've calculated the requested
    // index, so we return the data
    // point at the index in the buffer

    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_2<blDataType,blDataPtr>::at(const std::vector<blIntegerType>& dataIndexes)
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = static_cast<std::size_t>(currentDataIndex);

        for(j = 0; j < i; ++j)
        {
            partialIndex *= this->size(j);
        }

        dataIndex += partialIndex;

        ++i;
    }



    // We've calculated the requested
    // index, so we return the data
    // point at the index in the buffer

    return this->data()[dataIndex];
}



template<typename blDataType,
         typename blDataPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_2<blDataType,blDataPtr>::at(const std::vector<blIntegerType>& dataIndexes)const
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = static_cast<std::size_t>(currentDataIndex);

        for(j = 0; j < i; ++j)
        {
            partialIndex *= this->size(j);
        }

        dataIndex += partialIndex;

        ++i;
    }



    // We've calculated the requested
    // index, so we return the data
    // point at the index in the buffer

    return this->data()[dataIndex];
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_2_HPP
