#ifndef BL_BUFFER_3_HPP
#define BL_BUFFER_3_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer_3.hpp
// CLASS:           blBuffer_3
// BASE CLASS:      blBuffer_2
//
//
//
// PURPOSE:         -- This class is based on blBuffer_2 and adds
//                     circular access functions turning it into a
//                     ring-buffer where buffer indexes can be
//                     positive or negative and it still works
//
//                  -- This class also adds circular iterators that
//                     can be used in stl-like algorithms because
//                     these circular iterators allow the user to
//                     specify the number of circulations/cycles to
//                     go through before reaching the "end" iterator
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

#include "blBuffer_2.hpp"



// Used to define circular iterators
// and reverse circular iterators

#include "blCircularReverseIterator.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blBuffer_3 declaration
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

class blBuffer_3 : public blBuffer_2<blDataType,blDataPtr>
{
public: // Public type aliases



    // Buffer circular iterators

    using circular_iterator = blCircularIterator< blBuffer_2<blDataType,blDataPtr>,blBufferPtr >;
    using circular_const_iterator = blCircularIterator< blBuffer_2<blDataType,const blDataPtr>,const blBufferPtr >;

    using circular_reverse_iterator = blCircularReverseIterator< blBuffer_2<blDataType,blDataPtr>,blBufferPtr >;
    using circular_const_reverse_iterator = blCircularReverseIterator< blBuffer_2<blDataType,const blDataPtr>,const blBufferPtr >;



public: // Constructors and destructors



    // Default constructor

    blBuffer_3();



    // Copy constructor

    blBuffer_3(const blBuffer_3<blDataType,blDataPtr,blBufferPtr>& buffer3) = default;



    // Destructor

    ~blBuffer_3();



public: // Overloaded operators



    // Assignment operator

    blBuffer_3<blDataType,blDataPtr,blBufferPtr>&           operator=(const blBuffer_3<blDataType,blDataPtr,blBufferPtr>& buffer3) = default;



public: // Public static functions



    // Function used to get a buffer
    // index circularly given an index
    // and a buffer size

    template<typename blIntegerType>
    static std::size_t                                      circ_index(const blIntegerType& index,
                                                                       const std::size_t& totalLength)
    {
        return static_cast<std::size_t>( (index % static_cast<blIntegerType>(totalLength) + static_cast<blIntegerType>(totalLength)) ) % totalLength;
    }



public: // Public functions



    // Functions used to get circular
    // iterators to the buffer, where
    // the user can specify the number
    // of iteration cycles before
    // reaching the "end" iterator
    // (When maxcycles is negative then
    // the iterator never reaches the
    // "end" iterator)

    circular_iterator                                       circ_begin(const std::ptrdiff_t& maxNumberOfCirculations = 1);
    circular_iterator                                       circ_end();
    circular_const_iterator                                 circ_cbegin(const std::ptrdiff_t& maxNumberOfCirculations = 1)const;
    circular_const_iterator                                 circ_cend()const;

    circular_reverse_iterator                               circ_rbegin(const std::ptrdiff_t& maxNumberOfCirculations = 1);
    circular_reverse_iterator                               circ_rend();
    circular_const_reverse_iterator                         circ_crbegin(const std::ptrdiff_t& maxNumberOfCirculations = 1)const;
    circular_const_reverse_iterator                         circ_crend()const;



    // Function used to get a circular
    // iterator pointing in the
    // user specified position in
    // the buffer with a user specified
    // maximum number of circulations

    circular_iterator                                       circ_iter(const std::ptrdiff_t& startingPositionIndex,
                                                                      const std::ptrdiff_t& maxNumberOfCirculations);

    circular_const_iterator                                 circ_citer(const std::ptrdiff_t& startingPositionIndex,
                                                                       const std::ptrdiff_t& maxNumberOfCirculations)const;

    circular_reverse_iterator                               circ_riter(const std::ptrdiff_t& startingPositionIndex,
                                                                       const std::ptrdiff_t& maxNumberOfCirculations);

    circular_const_reverse_iterator                         circ_criter(const std::ptrdiff_t& startingPositionIndex,
                                                                        const std::ptrdiff_t& maxNumberOfCirculations)const;



    // "circ_at" functions used to access data
    // points in the buffer circularly like in
    // a ring-buffer, the indexes can be positive
    // or negative

    template<typename blIntegerType>
    blDataType&                                             circ_at(const blIntegerType& dataIndex);

    template<typename blIntegerType>
    const blDataType&                                       circ_at(const blIntegerType& dataIndex)const;

    template<typename blIntegerType>
    blDataType&                                             circ_at(const blIntegerType& rowIndex,
                                                                    const blIntegerType& colIndex);

    template<typename blIntegerType>
    const blDataType&                                       circ_at(const blIntegerType &rowIndex,
                                                                    const blIntegerType &colIndex)const;

    template<typename blIntegerType>
    blDataType&                                             circ_at(const blIntegerType& rowIndex,
                                                                    const blIntegerType& colIndex,
                                                                    const blIntegerType& pageIndex);

    template<typename blIntegerType>
    const blDataType&                                       circ_at(const blIntegerType& rowIndex,
                                                                    const blIntegerType& colIndex,
                                                                    const blIntegerType& pageIndex)const;



    // Generic version of
    // circ_at functions

    template<typename...Indexes>
    blDataType&                                             circ_at(const Indexes&...dataIndexes);

    template<typename...Indexes>
    const blDataType&                                       circ_at(const Indexes&...dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                                             circ_at(const std::initializer_list<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                                       circ_at(const std::initializer_list<blIntegerType>& dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                                             circ_at(const std::vector<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                                       circ_at(const std::vector<blIntegerType>& dataIndexes)const;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline blBuffer_3<blDataType,blDataPtr,blBufferPtr>::blBuffer_3() : blBuffer_2<blDataType,blDataPtr>()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline blBuffer_3<blDataType,blDataPtr,blBufferPtr>::~blBuffer_3()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to access buffer's circular begin/end iterators
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_begin(const std::ptrdiff_t& maxNumberOfCirculations)
{
    return circular_iterator(this,0,maxNumberOfCirculations);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_end()
{
    return circular_iterator(this,0,0);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_const_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_cbegin(const std::ptrdiff_t& maxNumberOfCirculations)const
{
    return circular_const_iterator(this,0,maxNumberOfCirculations);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_const_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_cend()const
{
    return circular_const_iterator(this,0,0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to access buffer's circular reverse
// begin/end iterators
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_reverse_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_rbegin(const std::ptrdiff_t& maxNumberOfCirculations)
{
    return circular_reverse_iterator(this,0,maxNumberOfCirculations);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_reverse_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_rend()
{
    return circular_reverse_iterator(this,0,0);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_const_reverse_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_crbegin(const std::ptrdiff_t& maxNumberOfCirculations)const
{
    return circular_const_reverse_iterator(this,0,maxNumberOfCirculations);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_const_reverse_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_crend()const
{
    return circular_const_reverse_iterator(this,0,0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get a circular iterator pointing in
// a user specified buffer location and with a user specified
// maximum number of circulations/cycles before it reaches
// the "end" iterator
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_iter(const std::ptrdiff_t& startingPositionIndex,
                                                                                                                                                                                              const std::ptrdiff_t& maxNumberOfCirculations)
{
    return circular_iterator(this,startingPositionIndex,maxNumberOfCirculations);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_const_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_citer(const std::ptrdiff_t& startingPositionIndex,
                                                                                                                                                                                                     const std::ptrdiff_t& maxNumberOfCirculations)const
{
    return circular_const_iterator(this,startingPositionIndex,maxNumberOfCirculations);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_reverse_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_riter(const std::ptrdiff_t& startingPositionIndex,
                                                                                                                                                                                                       const std::ptrdiff_t& maxNumberOfCirculations)
{
    return circular_reverse_iterator(this,startingPositionIndex,maxNumberOfCirculations);
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

inline typename blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circular_const_reverse_iterator blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_criter(const std::ptrdiff_t& startingPositionIndex,
                                                                                                                                                                                                              const std::ptrdiff_t& maxNumberOfCirculations)const
{
    return circular_const_reverse_iterator(this,startingPositionIndex,maxNumberOfCirculations);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// "circ_at" functions
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const blIntegerType& dataIndex)
{
    return this->at( this->circ_index(dataIndex,this->size()) );
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const blIntegerType& dataIndex)const
{
    return this->at( this->circ_index(dataIndex,this->size()) );
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const blIntegerType &rowIndex,
                                                                         const blIntegerType &colIndex)
{
    return this->at( this->circ_index(rowIndex,this->rows()),
                     this->circ_index(colIndex,this->cols()) );
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const blIntegerType& rowIndex,
                                                                               const blIntegerType& colIndex)const
{
    return this->at( this->circ_index(rowIndex,this->rows()),
                     this->circ_index(colIndex,this->cols()) );
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const blIntegerType& rowIndex,
                                                                         const blIntegerType& colIndex,
                                                                         const blIntegerType& pageIndex)
{
    return this->at( this->circ_index(rowIndex,this->rows()),
                     this->circ_index(colIndex,this->cols()),
                     this->circ_index(pageIndex,this->pages()) );
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const blIntegerType& rowIndex,
                                                                               const blIntegerType& colIndex,
                                                                               const blIntegerType& pageIndex)const
{
    return this->at( this->circ_index(rowIndex,this->rows()),
                     this->circ_index(colIndex,this->cols()),
                     this->circ_index(pageIndex,this->pages()) );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Generic versions of circ_at functions
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename...Indexes>

inline blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const Indexes&...dataIndexes)
{
    return this->circ_at({dataIndexes...});
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename...Indexes>

inline const blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const Indexes&...dataIndexes)const
{
    return this->circ_at({dataIndexes...});
}



template<typename blDataType,
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const std::initializer_list<blIntegerType>& dataIndexes)
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = circ_index(currentDataIndex,this->size(i));

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
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const std::initializer_list<blIntegerType>& dataIndexes)const
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = circ_index(currentDataIndex,this->size(i));

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
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const std::vector<blIntegerType>& dataIndexes)
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = circ_index(currentDataIndex,this->size(i));

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
         typename blDataPtr,
         typename blBufferPtr>

template<typename blIntegerType>

inline const blDataType& blBuffer_3<blDataType,blDataPtr,blBufferPtr>::circ_at(const std::vector<blIntegerType>& dataIndexes)const
{
    std::size_t dataIndex = 0;

    std::size_t i = 0;
    std::size_t j = 0;

    std::size_t partialIndex = 0;



    for(const blIntegerType& currentDataIndex : dataIndexes)
    {
        partialIndex = circ_index(currentDataIndex,this->size(i));

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



#endif // BL_BUFFER_3_HPP
