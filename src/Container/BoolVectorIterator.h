#ifndef BOOL_VECTOR_ITERATOR_INCLUDED
#define BOOL_VECTOR_ITERATOR_INCLUDED

#include "BoolVector.h"
#include "IteratorTag.h"

#include <type_traits>

/*! @file BoolVectorIterator.h
 *
 *  Random-access iterator class for BoolVector.
 *  @sa @file IteratorTag.h
 */

namespace Cellwars
{
    template <typename T>
    class BoolVectorIterator
    {
    public:
        using Category = RandomAccessIteratorTag;
        using ValueType = T;
        using DifferenceType = ptrdiff_t;
        using Reference = typename std::conditional<
            std::is_const<T>::value,
            const BoolVector::Proxy,
            BoolVector::Proxy>::type;

        using ConstReference = bool;

    public:
        BoolVectorIterator ();
        BoolVectorIterator (T* p, DifferenceType offset);

        BoolVectorIterator (const BoolVectorIterator& rhs) = default;
        BoolVectorIterator& operator= (const BoolVectorIterator& rhs) = default;

        bool operator== (const BoolVectorIterator& rhs) const;
        bool operator!= (const BoolVectorIterator& rhs) const;

        ConstReference operator* () const;
        Reference operator* ();
        ConstReference operator[] (unsigned idx) const;
        Reference operator[] (unsigned idx);

        BoolVectorIterator& operator++ ();
        BoolVectorIterator operator++ (int);
        BoolVectorIterator& operator-- ();
        BoolVectorIterator operator-- (int);

        BoolVectorIterator& operator+= (unsigned n);
        BoolVectorIterator& operator-= (unsigned n);
        BoolVectorIterator operator+ (unsigned n) const;
        BoolVectorIterator operator- (unsigned n) const;

        DifferenceType operator- (const BoolVectorIterator& rhs) const;

        bool operator< (const BoolVectorIterator& rhs) const;
        bool operator> (const BoolVectorIterator& rhs) const;
        bool operator<= (const BoolVectorIterator& rhs) const;
        bool operator>= (const BoolVectorIterator& rhs) const;

    private:
        T* p;
        DifferenceType offset;
    };
};

#include "BoolVectorIterator.inl"

#endif /* BOOL_VECTOR_ITERATOR_INCLUDED */
