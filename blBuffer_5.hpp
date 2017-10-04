#ifndef BL_BUFFER_5_HPP
#define BL_BUFFER_5_HPP


//-------------------------------------------------------------------
// FILE:            blBuffer_5.hpp
// CLASS:           blBuffer_5
// BASE CLASS:      blBuffer_4
//
//
//
// PURPOSE:         -- This class is based on blBuffer_4 and adds
//                     circular ROI random access functions as well
//                     as iterators for the Region Of Interest (m_roi)
//
//                  -- The ROI iterators introduced in this class
//                     allow the user of this buffer to iterate over
//                     the buffer's ROI as if it was its own buffer.
//
//                  -- The ROI iterators are circular and allow a
//                     specified maximum number of circulations before
//                     reached the "end" ROI iterator
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

#include "blBuffer_4.hpp"



// Include used to define
// ROI iterators and ROI
// reverse iterators

#include "blRoiReverseIterator.hpp"

//-------------------------------------------------------------------



//-------------------------------------------------------------------
// NOTE: This class is defined within the blBufferLIB namespace
//-------------------------------------------------------------------
namespace blBufferLIB
{
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// class blBuffer_5 declaration
//-------------------------------------------------------------------
template<typename blDataType>

class blBuffer_5 : public blBuffer_4<blDataType>
{
public: // Public typedefs



    // Buffer ROI iterators

    typedef blRoiIterator< blBuffer_5<blDataType> >                         roi_iterator;
    typedef blRoiIterator< blBuffer_5<const blDataType> >                   roi_const_iterator;

    typedef blRoiReverseIterator< blBuffer_5<blDataType> >                  roi_reverse_iterator;
    typedef blRoiReverseIterator< blBuffer_5<const blDataType> >            roi_const_reverse_iterator;



public: // Constructors and destructors



    // Default constructor

    blBuffer_5();



    // Copy constructor

    blBuffer_5(const blBuffer_5<blDataType>& buffer0) = default;



    // Destructor

    ~blBuffer_5();



public: // Overloaded operators



    // Assignment operator

    blBuffer_5<blDataType>&                 operator=(const blBuffer_5<blDataType>& buffer0) = default;



public: // Public functions



    // Functions used to get the
    // iterators to the buffer's
    // ROI, where the user can specify
    // the number of iteration cycles
    // before reaching the "end"
    // iterator (when maxcycles = -1 then
    // the iterator never reaches the
    // "end" iterator)

    roi_iterator                            roi_begin(const std::ptrdiff_t& maxNumberOfCirculations = 1);
    roi_iterator                            roi_end();
    roi_const_iterator                      roi_cbegin(const std::ptrdiff_t& maxNumberOfCirculations = 1)const;
    roi_const_iterator                      roi_cend()const;

    roi_reverse_iterator                    roi_rbegin(const std::ptrdiff_t& maxNumberOfCirculations = 1);
    roi_reverse_iterator                    roi_rend();
    roi_const_reverse_iterator              roi_crbegin(const std::ptrdiff_t& maxNumberOfCirculations = 1)const;
    roi_const_reverse_iterator              roi_crend()const;



    // Function used to get a ROI
    // iterator pointing in the
    // user specified position in
    // the ROI with a user specified
    // maximum number of circulations

    roi_iterator                            roi_iter(const std::ptrdiff_t& startingPositionIndex,
                                                     const std::ptrdiff_t& maxNumberOfCirculations);

    roi_const_iterator                      roi_citer(const std::ptrdiff_t& startingPositionIndex,
                                                      const std::ptrdiff_t& maxNumberOfCirculations)const;

    roi_reverse_iterator                    roi_riter(const std::ptrdiff_t& startingPositionIndex,
                                                      const std::ptrdiff_t& maxNumberOfCirculations);

    roi_const_reverse_iterator              roi_criter(const std::ptrdiff_t& startingPositionIndex,
                                                       const std::ptrdiff_t& maxNumberOfCirculations)const;



    // Circular ROI random access functions

    template<typename blIntegerType>
    blDataType&                             circ_roi_at(const blIntegerType& dataIndex);

    template<typename blIntegerType>
    const blDataType&                       circ_roi_at(const blIntegerType& dataIndex)const;

    template<typename blIntegerType>
    blDataType&                             circ_roi_at(const blIntegerType& rowIndex,
                                                        const blIntegerType& colIndex);

    template<typename blIntegerType>
    const blDataType&                       circ_roi_at(const blIntegerType &rowIndex,
                                                        const blIntegerType &colIndex)const;

    template<typename blIntegerType>
    blDataType&                             circ_roi_at(const blIntegerType& rowIndex,
                                                        const blIntegerType& colIndex,
                                                        const blIntegerType& pageIndex);

    template<typename blIntegerType>
    const blDataType&                       circ_roi_at(const blIntegerType& rowIndex,
                                                        const blIntegerType& colIndex,
                                                        const blIntegerType& pageIndex)const;



    // Generic version of the
    // circular ROI random access
    // functions

    template<typename...Indexes>
    blDataType&                             circ_roi_at(const Indexes&...dataIndexes);

    template<typename...Indexes>
    const blDataType&                       circ_roi_at(const Indexes&...dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                             circ_roi_at(const std::initializer_list<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                       circ_roi_at(const std::initializer_list<blIntegerType>& dataIndexes)const;

    template<typename blIntegerType>
    blDataType&                             circ_roi_at(const std::vector<blIntegerType>& dataIndexes);

    template<typename blIntegerType>
    const blDataType&                       circ_roi_at(const std::vector<blIntegerType>& dataIndexes)const;
};
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Default constructor
//-------------------------------------------------------------------
template<typename blDataType>
inline blBuffer_5<blDataType>::blBuffer_5() : blBuffer_4<blDataType>()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Destructor
//-------------------------------------------------------------------
template<typename blDataType>
inline blBuffer_5<blDataType>::~blBuffer_5()
{
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to access ROI's begin/end iterators
//-------------------------------------------------------------------
template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_iterator blBuffer_5<blDataType>::roi_begin(const std::ptrdiff_t& maxNumberOfCirculations)
{
    return roi_iterator(*this,0,maxNumberOfCirculations);
}



template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_iterator blBuffer_5<blDataType>::roi_end()
{
    return roi_iterator(*this,this->roi().size(),0);
}



template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_const_iterator blBuffer_5<blDataType>::roi_cbegin(const std::ptrdiff_t& maxNumberOfCirculations)const
{
    return roi_const_iterator(*this,0,maxNumberOfCirculations);
}



template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_const_iterator blBuffer_5<blDataType>::roi_cend()const
{
    return roi_const_iterator(*this,this->roi().size(),0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to access ROI's begin/end reverse iterators
//-------------------------------------------------------------------
template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_reverse_iterator blBuffer_5<blDataType>::roi_rbegin(const std::ptrdiff_t& maxNumberOfCirculations)
{
    return roi_reverse_iterator(*this,0,maxNumberOfCirculations);
}



template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_reverse_iterator blBuffer_5<blDataType>::roi_rend()
{
    return roi_reverse_iterator(*this,0,0);
}



template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_const_reverse_iterator blBuffer_5<blDataType>::roi_crbegin(const std::ptrdiff_t& maxNumberOfCirculations)const
{
    return roi_const_reverse_iterator(*this,0,maxNumberOfCirculations);
}



template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_const_reverse_iterator blBuffer_5<blDataType>::roi_crend()const
{
    return roi_const_reverse_iterator(*this,0,0);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Functions used to get a roi iterator pointing in
// a user specified ROI location and with a user specified
// maximum number of circulations/cycles before it reaches
// the "end" iterator
//-------------------------------------------------------------------
template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_iterator blBuffer_5<blDataType>::roi_iter(const std::ptrdiff_t& startingPositionIndex,
                                                                                      const std::ptrdiff_t& maxNumberOfCirculations)
{
    return roi_iterator(*this,startingPositionIndex,maxNumberOfCirculations);
}



template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_const_iterator blBuffer_5<blDataType>::roi_citer(const std::ptrdiff_t& startingPositionIndex,
                                                                                             const std::ptrdiff_t& maxNumberOfCirculations)const
{
    return roi_const_iterator(*this,startingPositionIndex,maxNumberOfCirculations);
}



template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_reverse_iterator blBuffer_5<blDataType>::roi_riter(const std::ptrdiff_t& startingPositionIndex,
                                                                                               const std::ptrdiff_t& maxNumberOfCirculations)
{
    return roi_reverse_iterator(*this,startingPositionIndex,maxNumberOfCirculations);
}



template<typename blDataType>
inline typename blBuffer_5<blDataType>::roi_const_reverse_iterator blBuffer_5<blDataType>::roi_criter(const std::ptrdiff_t& startingPositionIndex,
                                                                                                      const std::ptrdiff_t& maxNumberOfCirculations)const
{
    return roi_const_reverse_iterator(*this,startingPositionIndex,maxNumberOfCirculations);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// "circ_at" functions
//-------------------------------------------------------------------
template<typename blDataType>
template<typename blIntegerType>
inline blDataType& blBuffer_5<blDataType>::circ_roi_at(const blIntegerType& dataIndex)
{
    return this->roi_at( this->circ_index(dataIndex,this->roi().size()) );
}



template<typename blDataType>
template<typename blIntegerType>
inline const blDataType& blBuffer_5<blDataType>::circ_roi_at(const blIntegerType& dataIndex)const
{
    return this->roi_at( this->circ_index(dataIndex,this->roi().size()) );
}



template<typename blDataType>
template<typename blIntegerType>
inline blDataType& blBuffer_5<blDataType>::circ_roi_at(const blIntegerType &rowIndex,
                                                       const blIntegerType &colIndex)
{
    return this->roi_at( this->circ_index(rowIndex,this->roi().rows()),
                         this->circ_index(colIndex,this->roi().cols()) );
}



template<typename blDataType>
template<typename blIntegerType>
inline const blDataType& blBuffer_5<blDataType>::circ_roi_at(const blIntegerType& rowIndex,
                                                             const blIntegerType& colIndex)const
{
    return this->roi_at( this->circ_index(rowIndex,this->roi().rows()),
                         this->circ_index(colIndex,this->roi().cols()) );
}



template<typename blDataType>
template<typename blIntegerType>
inline blDataType& blBuffer_5<blDataType>::circ_roi_at(const blIntegerType& rowIndex,
                                                       const blIntegerType& colIndex,
                                                       const blIntegerType& pageIndex)
{
    return this->roi_at( this->circ_index(rowIndex,this->roi().rows()),
                         this->circ_index(colIndex,this->roi().cols()),
                         this->circ_index(pageIndex,this->roi().pages()) );
}



template<typename blDataType>
template<typename blIntegerType>
inline const blDataType& blBuffer_5<blDataType>::circ_roi_at(const blIntegerType& rowIndex,
                                                             const blIntegerType& colIndex,
                                                             const blIntegerType& pageIndex)const
{
    return this->roi_at( this->circ_index(rowIndex,this->roi().rows()),
                         this->circ_index(colIndex,this->roi().cols()),
                         this->circ_index(pageIndex,this->roi().pages()) );
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// Generic versions of circ_at functions
//-------------------------------------------------------------------
template<typename blDataType>
template<typename...Indexes>
inline blDataType& blBuffer_5<blDataType>::circ_roi_at(const Indexes&...dataIndexes)
{
    return this->circ_at({dataIndexes...});
}



template<typename blDataType>
template<typename...Indexes>
inline const blDataType& blBuffer_5<blDataType>::circ_roi_at(const Indexes&...dataIndexes)const
{
    return this->circ_at({dataIndexes...});
}



template<typename blDataType>
template<typename blIntegerType>
inline blDataType& blBuffer_5<blDataType>::circ_roi_at(const std::initializer_list<blIntegerType>& dataIndexes)
{
    std::vector<std::size_t> offsettedAndCirculatedDataIndexes(dataIndexes.begin(),dataIndexes.end());

    for(std::size_t i = 0; i < offsettedAndCirculatedDataIndexes.size(); ++i)
        offsettedAndCirculatedDataIndexes[i] = this->circ_index(offsettedAndCirculatedDataIndexes,this->roi().size(i)) + this->roi().offset(i);

    return this->at(offsettedAndCirculatedDataIndexes);
}



template<typename blDataType>
template<typename blIntegerType>
inline const blDataType& blBuffer_5<blDataType>::circ_roi_at(const std::initializer_list<blIntegerType>& dataIndexes)const
{
    std::vector<std::size_t> offsettedAndCirculatedDataIndexes(dataIndexes.begin(),dataIndexes.end());

    for(std::size_t i = 0; i < offsettedAndCirculatedDataIndexes.size(); ++i)
        offsettedAndCirculatedDataIndexes[i] = this->circ_index(offsettedAndCirculatedDataIndexes,this->roi().size(i)) + this->roi().offset(i);

    return this->at(offsettedAndCirculatedDataIndexes);
}



template<typename blDataType>
template<typename blIntegerType>
inline blDataType& blBuffer_5<blDataType>::circ_roi_at(const std::vector<blIntegerType>& dataIndexes)
{
    std::vector<std::size_t> offsettedAndCirculatedDataIndexes(dataIndexes.begin(),dataIndexes.end());

    for(std::size_t i = 0; i < offsettedAndCirculatedDataIndexes.size(); ++i)
        offsettedAndCirculatedDataIndexes[i] = this->circ_index(offsettedAndCirculatedDataIndexes,this->roi().size(i)) + this->roi().offset(i);

    return this->at(offsettedAndCirculatedDataIndexes);
}



template<typename blDataType>
template<typename blIntegerType>
inline const blDataType& blBuffer_5<blDataType>::circ_roi_at(const std::vector<blIntegerType>& dataIndexes)const
{
    std::vector<std::size_t> offsettedAndCirculatedDataIndexes(dataIndexes.begin(),dataIndexes.end());

    for(std::size_t i = 0; i < offsettedAndCirculatedDataIndexes.size(); ++i)
        offsettedAndCirculatedDataIndexes[i] = this->circ_index(offsettedAndCirculatedDataIndexes,this->roi().size(i)) + this->roi().offset(i);

    return this->at(offsettedAndCirculatedDataIndexes);
}
//-------------------------------------------------------------------



//-------------------------------------------------------------------
// End of namespace
}
//-------------------------------------------------------------------



#endif // BL_BUFFER_5_HPP
