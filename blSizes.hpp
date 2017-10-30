#ifndef BL_SIZES_HPP
#define BL_SIZES_HPP


//-------------------------------------------------------------------
// FILE:            blSizes.hpp
// CLASS:           blSizes
// BASE CLASS:      None
//
//
//
// PURPOSE:         -- This class holds the dimensional lengths of an
//                     N-Dimensional entity.  For example, if we are dealing
//                     with an N-Dimensional buffer, this can be used to
//                     represent its dimensional sizes and the number of dimensions
//
//                  -- As another example, for an N-Dimensional entity, this class
//                     can also be used to hold the offsets in each dimension of
//                     the entity, useful in defining Regions Of Interest in the buffer
//
//                  -- This class either holds the information of the sizes
//                     itself, or it can be used to wrap an external sizes
//                     vector, which is a must for example when using this
//                     class for entities living in shared memory
//
//                  -- The class is a template that accepts a size pointer type
//                     so for example, if this is used to represent information
//                     about N-Dimensional entities living in shared memory, the
//                     programmer can choose a boost::interprocess::offset_ptr as
//                     the size pointer type
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
// class blSizes declaration
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

class blSizes
{
public: // Public type aliases



    // Buffer iterators

    using iterator = blSizePtr;
    using const_iterator = const blSizePtr;

    using reverse_iterator = blReverseIterator<blSizeType,blSizePtr>;
    using const_reverse_iterator = blReverseIterator<blSizeType,const blSizePtr>;



public: // Constructors and destructors



    // Default constructor

    blSizes();



    // Constructor specifying the
    // number of dimensions and an
    // initial value for each dimensional
    // size

    blSizes(const blSizeType& numberOfDimensions,
            const blSizeType& initialSizeOfEachDimension);



    // Constructors from begin/end iterators

    template<typename blSourceIteratorType>

    blSizes(const blSourceIteratorType& beginIter,
            const blSourceIteratorType& endIter);



    // Constructor from another std::vector

    template<typename blAnotherSizeType>

    blSizes(const std::vector<blAnotherSizeType>& sizeVector);



    // Constructor from an initializer list

    template<typename blAnotherSizeType>

    blSizes(const std::initializer_list<blAnotherSizeType>& sizeInitializerList);



    // Copy constructor

    blSizes(const blSizes<blSizeType,blSizePtr>& buffer1) = default;



    // Destructor

    ~blSizes();



public: // Overloaded operators



    // Assignment operator

    blSizes<blSizeType,blSizePtr>&                  operator=(const blSizes<blSizeType,blSizePtr>& buffer1) = default;



    // Assignment operator from
    // an std::vector

    template<typename blAnotherSizeType>

    blSizes<blSizeType,blSizePtr>&                  operator=(const std::vector<blAnotherSizeType>& sizeVector);



    // Assignment operator from
    // an initializer list

    template<typename blAnotherSizeType>

    blSizes<blSizeType,blSizePtr>&                  operator=(const std::initializer_list<blAnotherSizeType>& sizeInitializerList);



    // Access operators

    template<typename blIntegerType>
    blSizeType&                                     operator[](const blIntegerType& sizeIndex);

    template<typename blIntegerType>
    const blSizeType&                               operator[](const blIntegerType& sizeIndex)const;

    template<typename blIntegerType>
    blSizeType&                                     operator()(const blIntegerType& sizeIndex);

    template<typename blIntegerType>
    const blSizeType&                               operator()(const blIntegerType& sizeIndex)const;



public: // Public functions



    // Functions used to get the
    // overall size/length of the
    // sizes vector

    const std::size_t&                              size()const;
    const std::size_t&                              length()const;



    // Functions used to get a pointer
    // to the first size in the sizes
    // vector, not dereferenceable when
    // buffer is empty

    iterator                                        data();
    const_iterator                                  data()const;




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



    // Because the sizes vector could be
    // wrapping sizes data from an external
    // source without owning it, this
    // function can be used to ask
    // whether the sizes vector owns the data
    // it's currently working with

    bool                                            doesSizesVectorOwnData()const;



    // This function lets derived classes
    // overwrite the m_dataPointer pointer
    // useful when wrapping existing data
    // without copying the data into
    // the buffer
    // Of course the derived class also has
    // to specify the sizes of the wrapped
    // data

    template<typename blAnotherSizesVector>
    void                                            wrap(blAnotherSizesVector& externalSizesVector);



    // This function resets the data pointers
    // to point to the sizes vector's first
    // element

    void                                            resetIterators();



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



    // The vector holding the sizes if
    // the sizes vector owns the sizes
    // data

    std::vector<blSizeType>                         m_sizes;



    // The number of dimensions

    std::size_t                                     m_dimensions;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

inline blSizes<blSizeType,blSizePtr>::blSizes()
{
    // Default all data iterators
    // to null pointers

    m_begin = nullptr;
    m_end = nullptr;
    m_rbegin = nullptr;
    m_rend = nullptr;



    // Default the number of
    // dimensions to zero

    m_dimensions = 0;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructor specifying the number of dimensions and an
// initial value for each dimensional size
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

inline blSizes<blSizeType,blSizePtr>::blSizes(const blSizeType& numberOfDimensions,
                                              const blSizeType& initialSizeOfEachDimension)
{
    // First we initialize the
    // vector holding the sizes

    m_sizes = std::vector<blSizeType>(numberOfDimensions,initialSizeOfEachDimension);



    // Then we reset the
    // iterators to point
    // to the newly generated
    // sizes vector

    resetIterators();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors from begin/end iterators
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

template<typename blSourceIteratorType>

inline blSizes<blSizeType,blSizePtr>::blSizes(const blSourceIteratorType& beginIter,
                                              const blSourceIteratorType& endIter)
{
    m_sizes = std::vector<blSizeType>(beginIter,endIter);

    resetIterators();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors from an std::vector
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

template<typename blAnotherSizeType>

inline blSizes<blSizeType,blSizePtr>::blSizes(const std::vector<blAnotherSizeType>& sizeVector)
{
    m_sizes = std::vector<blSizeType>(sizeVector.begin(),sizeVector.end());

    resetIterators();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Constructors from an initializer list
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

template<typename blAnotherSizeType>

inline blSizes<blSizeType,blSizePtr>::blSizes(const std::initializer_list<blAnotherSizeType>& sizeInitializerList)
{
    m_sizes = std::vector<blSizeType>(sizeInitializerList.begin(),sizeInitializerList.end());

    resetIterators();
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

inline blSizes<blSizeType,blSizePtr>::~blSizes()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Assignment from another type of vector holding sizes
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

template<typename blAnotherSizeType>

inline blSizes<blSizeType,blSizePtr>& blSizes<blSizeType,blSizePtr>::operator=(const std::vector<blAnotherSizeType>& sizeVector)
{
    m_sizes = std::vector<blSizeType>(sizeVector.begin(),sizeVector.end());

    resetIterators();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Assignment from an initializer list
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

template<typename blAnotherSizeType>

inline blSizes<blSizeType,blSizePtr>& blSizes<blSizeType,blSizePtr>::operator=(const std::initializer_list<blAnotherSizeType>& sizeInitializerList)
{
    m_sizes = std::vector<blSizeType>(sizeInitializerList.begin(),sizeInitializerList.end());

    resetIterators();

    return (*this);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Access operators
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

template<typename blIntegerType>

inline blSizeType& blSizes<blSizeType,blSizePtr>::operator[](const blIntegerType& sizeIndex)
{
    return m_begin[sizeIndex];
}



template<typename blSizeType,
         typename blSizePtr>

template<typename blIntegerType>

inline const blSizeType& blSizes<blSizeType,blSizePtr>::operator[](const blIntegerType& sizeIndex)const
{
    return m_begin[sizeIndex];
}



template<typename blSizeType,
          typename blSizePtr>

 template<typename blIntegerType>

 inline blSizeType& blSizes<blSizeType,blSizePtr>::operator()(const blIntegerType& sizeIndex)
 {
     return m_begin[sizeIndex];
 }



 template<typename blSizeType,
          typename blSizePtr>

 template<typename blIntegerType>

 inline const blSizeType& blSizes<blSizeType,blSizePtr>::operator()(const blIntegerType& sizeIndex)const
 {
     return m_begin[sizeIndex];
 }
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// wrap function -- used to wrap sizes data from an external source
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

template<typename blAnotherSizesVector>
inline void blSizes<blSizeType,blSizePtr>::wrap(blAnotherSizesVector& externalSizesVector)
{
    // First we save the
    // number of dimensions

    m_dimensions = externalSizesVector.size();



    // Then we set the begin/end
    // iterators so they point to
    // the external data vector

    m_begin = iterator(&externalSizesVector[0]);
    m_end = m_begin + m_dimensions;

    m_rbegin = reverse_iterator(m_begin + m_dimensions - 1);
    m_rend = reverse_iterator(m_begin - 1);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to reset the data pointers
// so that they point at buffer's internal
// sizes vector in case they were originally
// pointing to some external sizes vector
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

inline void blSizes<blSizeType,blSizePtr>::resetIterators()
{
    if(m_sizes.size() > 0)
    {
        m_dimensions = m_sizes.size();

        m_begin = m_sizes.data();
        m_end = m_begin + m_dimensions;

        m_rbegin = reverse_iterator(m_begin + m_dimensions - 1);
        m_rend = reverse_iterator(m_begin - 1);
    }
    else
    {
        m_dimensions = 0;

        m_begin = nullptr;
        m_end = nullptr;

        m_rbegin = nullptr;
        m_rend = nullptr;
    }
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Function used to know if the buffer is pointing
// to its own internal data or handling data from
// an external source
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

inline bool blSizes<blSizeType,blSizePtr>::doesSizesVectorOwnData()const
{
    return ( m_begin == m_sizes.data() );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to return the length of the sizes vector
// meaning the number of dimensions
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

inline const std::size_t& blSizes<blSizeType,blSizePtr>::size()const
{
    return m_dimensions;
}



template<typename blSizeType,
         typename blSizePtr>

inline const std::size_t& blSizes<blSizeType,blSizePtr>::length()const
{
    return m_dimensions;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get a pointer to
// the first element in the sizes vector
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::iterator blSizes<blSizeType,blSizePtr>::data()
{
    return m_begin;
}



template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::const_iterator blSizes<blSizeType,blSizePtr>::data()const
{
    return m_begin;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Iterators to the buffer
//-------------------------------------------------------------------
template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::iterator blSizes<blSizeType,blSizePtr>::begin()
{
    return m_begin;
}



template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::iterator blSizes<blSizeType,blSizePtr>::end()
{
    return m_end;
}



template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::const_iterator blSizes<blSizeType,blSizePtr>::cbegin()const
{
    return m_begin;
}



template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::const_iterator blSizes<blSizeType,blSizePtr>::cend()const
{
    return m_end;
}



template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::reverse_iterator blSizes<blSizeType,blSizePtr>::rbegin()
{
    return m_rbegin;
}



template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::reverse_iterator blSizes<blSizeType,blSizePtr>::rend()
{
    return m_rend;
}



template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::const_reverse_iterator blSizes<blSizeType,blSizePtr>::crbegin()const
{
    return m_rbegin;
}



template<typename blSizeType,
         typename blSizePtr>

inline typename blSizes<blSizeType,blSizePtr>::const_reverse_iterator blSizes<blSizeType,blSizePtr>::crend()const
{
    return m_rend;
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_SIZES_HPP
