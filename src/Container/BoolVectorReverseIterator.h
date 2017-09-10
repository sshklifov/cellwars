#ifndef BOOL_VECTOR_REVERSE_ITERATOR_INCLUDED
#define BOOL_VECTOR_REVERSE_ITERATOR_INCLUDED

#include "BoolVector.h"
#include "IteratorTag.h"

/*! @file BoolVectorReverseIterator.h
 *
 *  Random-access reverse iterator class for BoolVector.
 *  @sa @file IteratorTag.h
 */

namespace Cellwars
{
    template <typename T>
    class BoolVectorReverseIterator
    {
    public:
        using Category = RandomAccessIteratorTag;
        using DifferenceType = ptrdiff_t;
        using ValueType = T;
        using Reference = typename BoolVectorIterator<T>::Reference;
        using ConstReference = bool;

    public:
        BoolVectorReverseIterator ();
        BoolVectorReverseIterator (T* p, DifferenceType offset);
        BoolVectorReverseIterator (const BoolVectorReverseIterator& rhs) = default;
        BoolVectorReverseIterator& operator= (const BoolVectorReverseIterator& rhs) = default;

        bool operator== (const BoolVectorReverseIterator& rhs) const;
        bool operator!= (const BoolVectorReverseIterator& rhs) const;

        ConstReference operator* () const;
        Reference operator* ();
        ConstReference operator[] (unsigned idx) const;
        Reference operator[] (unsigned idx);

        BoolVectorReverseIterator& operator++ ();
        BoolVectorReverseIterator operator++ (int);
        BoolVectorReverseIterator& operator-- ();
        BoolVectorReverseIterator operator-- (int);

        BoolVectorReverseIterator& operator+= (unsigned n);
        BoolVectorReverseIterator& operator-= (unsigned n);
        BoolVectorReverseIterator operator+ (unsigned n) const;
        BoolVectorReverseIterator operator- (unsigned n) const;

        DifferenceType operator- (const BoolVectorReverseIterator& it) const;

        bool operator< (const BoolVectorReverseIterator& rhs) const;
        bool operator> (const BoolVectorReverseIterator& rhs) const;
        bool operator<= (const BoolVectorReverseIterator& rhs) const;
        bool operator>= (const BoolVectorReverseIterator& rhs) const;

    private:
        BoolVectorIterator<T> it;
    };
};

#include "BoolVectorReverseIterator.inl"

#endif /* BOOL_VECTOR_REVERSE_ITERATOR_INCLUDED */
