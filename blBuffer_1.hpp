#ifndef BL_BUFFER_1_HPP
#define BL_BUFFER_1_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer_1.hpp
// CLASS:           blBuffer_1
// BASE CLASS:      blBuffer_0
//
//
//
// PURPOSE:         -- This class is based on blBuffer_0 and adds
//                     begin/end iterators to the buffer, plus functions
//                     to access the buffer's data as raw data
//
//                  -- The class allows the user to specify the type
//                     of pointer used, which is defaulted to a raw pointer
//                     The user could instead opt for a "offset_ptr"
//                     from the boost interprocess library to allow
//                     the use of blBuffer in shared memory for multi-
//                     process applications
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

// Building upon blBuffer_0

#include "blBuffer_0.hpp"



// Used to define iterators

#include "blReverseIterator.hpp"


//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blBuffer_1 declaration
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

class blBuffer_1 : public blBuffer_0<blDataType>
{
public: // Public type aliases



    // Buffer iterators

    using iterator = blDataPtr;
    using const_iterator = const blDataPtr;

    using reverse_iterator = blReverseIterator<blDataType,blDataPtr>;
    using const_reverse_iterator = blReverseIterator<blDataType,const blDataPtr>;



public: // Constructors and destructors



    // Default constructor

    blBuffer_1();



    // Copy constructor

    blBuffer_1(const blBuffer_1<blDataType,blDataPtr>& buffer1) = default;



    // Destructor

    ~blBuffer_1();



public: // Overloaded operators



    // Assignment operator

    blBuffer_1<blDataType,blDataPtr>&               operator=(const blBuffer_1<blDataType,blDataPtr>& buffer1) = default;



public: // Public functions



    // Functions used to get a pointer
    // to the first data point in the
    // buffer, not dereferenceable when
    // buffer is empty

    blDataPtr                                       data();
    const blDataPtr                                 data()const;



    // Functions used to get a pointer
    // to the first data point in the
    // buffer but cast to a raw byte array
    // again the pointer is not derefenceable
    // when buffer is empty

    unsigned char*                                  dataBytes();
    const unsigned char*                            dataBytes()const;



    // Function used to return the size of
    // a single data point for the data
    // currently stored in this buffer
    //
    // This is useful when wrapping external
    // data that is of different type than
    // "blDataType"

    const std::size_t&                              sizeOfSingleDataPoint()const;




    // Useful iterators pointing at the
    // "first" element of the array and
    // its "end"

    iterator                                        begin();
    iterator                                        end();
    const_iterator                                  cbegin()const;
    const_iterator                                  cend()const;

    reverse_iterator                                rbegin();
    reverse_iterator                                rend();
    const_reverse_iterator                          crbegin()const;
    const_reverse_iterator                          crend()const;



    // Because the buffer could be
    // wrapping data from another
    // source without owning it, this
    // function can be used to ask
    // whether the buffer owns the data
    // it's currently working with

    bool                                            doesBufferOwnData()const;



    // This function lets derived classes
    // overwrite the m_dataPointer pointer
    // useful when wrapping existing data
    // without copying the data into
    // the buffer
    // Of course the derived class also has
    // to specify the sizes of the wrapped
    // data

    template<typename blExistingDataType,
             typename...blIntegerType>
    void                                            wrap(blExistingDataType& data,
                                                         const blIntegerType&... bufferLengths);

    template<typename blExistingDataType>
    void                                            wrap(blExistingDataType& data,
                                                         const std::initializer_list<std::size_t>& bufferLengths);

    template<typename blExistingDataType>
    void                                            wrap(blExistingDataType& data,
                                                         const std::vector<std::size_t>& bufferLengths);

    template<typename blExistingDataType,
             typename...blIntegerType>
    void                                            wrap(blExistingDataType* dataPointer,
                                                         const blIntegerType&... bufferLengths);

    template<typename blExistingDataType>
    void                                            wrap(blExistingDataType* dataPointer,
                                                         const std::initializer_list<std::size_t>& bufferLengths);

    template<typename blExistingDataType>
    void                                            wrap(blExistingDataType* dataPointer,
                                                         const std::vector<std::size_t>& bufferLengths);



    // This function resets the m_dataPointer
    // pointer to point to the buffer's
    // first element

    void                                            resetDataPointers();



private: // Private variables



    // -- Iterators pointing to the beginning
    //    and end of the data buffer
    //
    // -- Most of the times these iterators
    //    will point to the beginning and
    //    end of m_data vector, unless the
    //    buffer is wrapping data from an
    //    external source

    iterator                                        m_begin;
    iterator                                        m_end;

    reverse_iterator                                m_rbegin;
    reverse_iterator                                m_rend;



    // Size of a single data point, useful
    // when wrapping external data of different
    // type than "blDataPoint"

    std::size_t                                     m_sizeOfSingleDataPoint;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blBuffer_1<blDataType,blDataPtr>::blBuffer_1() : blBuffer_0<blDataType>()
{
    // Default all data iterators
    // to null pointers

    m_begin = nullptr;
    m_end = nullptr;
    m_rbegin = nullptr;
    m_rend = nullptr;

    m_sizeOfSingleDataPoint = sizeof(blDataType);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blBuffer_1<blDataType,blDataPtr>::~blBuffer_1()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// wrap functions -- used to wrap data from an external source
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

template<typename blExistinDataType,
         typename...blIntegerType>

inline void blBuffer_1<blDataType,blDataPtr>::wrap(blExistinDataType& data,
                                                   const blIntegerType&... bufferLengths)
{
    wrap(&data,{static_cast<std::size_t>(bufferLengths)...});
}



template<typename blDataType,
         typename blDataPtr>

template<typename blExistinDataType>

inline void blBuffer_1<blDataType,blDataPtr>::wrap(blExistinDataType& data,
                                                   const std::initializer_list<std::size_t>& bufferLengths)
{
    wrap(&data,bufferLengths);
}



template<typename blDataType,
         typename blDataPtr>

template<typename blExistinDataType>

inline void blBuffer_1<blDataType,blDataPtr>::wrap(blExistinDataType& data,
                                                   const std::vector<std::size_t>& bufferLengths)
{
    wrap(&data,bufferLengths);
}



template<typename blDataType,
         typename blDataPtr>

template<typename blExistinDataType,
         typename...blIntegerType>

inline void blBuffer_1<blDataType,blDataPtr>::wrap(blExistinDataType* dataPointer,
                                                   const blIntegerType&... bufferLengths)
{
    wrap(dataPointer,{static_cast<std::size_t>(bufferLengths)...});
}



template<typename blDataType,
         typename blDataPtr>

template<typename blExistinDataType>

inline void blBuffer_1<blDataType,blDataPtr>::wrap(blExistinDataType* dataPointer,
                                                   const std::initializer_list<std::size_t>& bufferLengths)
{
    // First we create the
    // sizes vector with the
    // specified lengths

    this->m_properties.setDimensionalSizes(bufferLengths);



    // Then we set the begin/end
    // iterators

    m_begin = dataPointer;
    m_end = m_begin + this->size();

    m_rbegin = reverse_iterator(m_begin + this->size() - 1);
    m_rend = reverse_iterator(m_begin - 1);



    // Let's not forget to set
    // the size of a single data
    // point as the data being
    // wrapped might be of a different
    // type than "blDataType"

    m_sizeOfSingleDataPoint = sizeof(blExistinDataType);
}



template<typename blDataType,
         typename blDataPtr>

template<typename blExistinDataType>

inline void blBuffer_1<blDataType,blDataPtr>::wrap(blExistinDataType* dataPointer,
                                                   const std::vector<std::size_t>& bufferLengths)
{
    // First we create the
    // sizes vector with the
    // specified lengths

    this->m_properties.setDimensionalSizes(bufferLengths);



    // Then we set the begin/end
    // iterators

    m_begin = dataPointer;
    m_end = m_begin + this->size();

    m_rbegin = reverse_iterator(m_begin + this->size() - 1);
    m_rend = reverse_iterator(m_begin - 1);



    // Let's not forget to set
    // the size of a single data
    // point as the data being
    // wrapped might be of a different
    // type than "blDataType"

    m_sizeOfSingleDataPoint = sizeof(blExistinDataType);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to reset the data pointers
// so that they point at buffer's internal
// data in case they were originally pointing
// to some external data source
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline void blBuffer_1<blDataType,blDataPtr>::resetDataPointers()
{
    // First we set the
    // data iterators and
    // pointers

    if(this->m_data.size() > 0)
    {
        m_begin = this->m_data.data();
        m_end = m_begin + this->size();

        m_rbegin = reverse_iterator(m_begin + (this->size() - 1));
        m_rend = reverse_iterator(m_begin - 1);
    }
    else
    {
        m_begin = nullptr;
        m_end = nullptr;

        m_rbegin = nullptr;
        m_rend = nullptr;
    }



    // Finally we reset the size of
    // a single data point to its
    // default

    m_sizeOfSingleDataPoint = sizeof(blDataType);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to know if the buffer is pointing
// to its own internal data or handling data from
// an external source
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline bool blBuffer_1<blDataType,blDataPtr>::doesBufferOwnData()const
{
    return ( m_begin == this->m_data.data() );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get a pointer to
// the first element in the data buffer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline blDataPtr blBuffer_1<blDataType,blDataPtr>::data()
{
    return m_begin;
}



template<typename blDataType,
         typename blDataPtr>

inline const blDataPtr blBuffer_1<blDataType,blDataPtr>::data()const
{
    return m_begin;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get a poitner to the
// first element in the data buffer but cast
// to a raw byte pointer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline unsigned char* blBuffer_1<blDataType,blDataPtr>::dataBytes()
{
    return reinterpret_cast<unsigned char*>(m_begin);
}



template<typename blDataType,
         typename blDataPtr>

inline const unsigned char* blBuffer_1<blDataType,blDataPtr>::dataBytes()const
{
    return reinterpret_cast<const unsigned char*>(m_begin);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Iterators to the buffer
//-------------------------------------------------------------------
template<typename blDataType,
         typename blDataPtr>

inline typename blBuffer_1<blDataType,blDataPtr>::iterator blBuffer_1<blDataType,blDataPtr>::begin()
{
    return m_begin;
}



template<typename blDataType,
         typename blDataPtr>

inline typename blBuffer_1<blDataType,blDataPtr>::iterator blBuffer_1<blDataType,blDataPtr>::end()
{
    return m_end;
}



template<typename blDataType,
         typename blDataPtr>

inline typename blBuffer_1<blDataType,blDataPtr>::const_iterator blBuffer_1<blDataType,blDataPtr>::cbegin()const
{
    return m_begin;
}



template<typename blDataType,
         typename blDataPtr>

inline typename blBuffer_1<blDataType,blDataPtr>::const_iterator blBuffer_1<blDataType,blDataPtr>::cend()const
{
    return m_end;
}



template<typename blDataType,
         typename blDataPtr>

inline typename blBuffer_1<blDataType,blDataPtr>::reverse_iterator blBuffer_1<blDataType,blDataPtr>::rbegin()
{
    return m_rbegin;
}



template<typename blDataType,
         typename blDataPtr>

inline typename blBuffer_1<blDataType,blDataPtr>::reverse_iterator blBuffer_1<blDataType,blDataPtr>::rend()
{
    return m_rend;
}



template<typename blDataType,
         typename blDataPtr>

inline typename blBuffer_1<blDataType,blDataPtr>::const_reverse_iterator blBuffer_1<blDataType,blDataPtr>::crbegin()const
{
    return m_rbegin;
}



template<typename blDataType,
         typename blDataPtr>

inline typename blBuffer_1<blDataType,blDataPtr>::const_reverse_iterator blBuffer_1<blDataType,blDataPtr>::crend()const
{
    return m_rend;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_1_HPP
