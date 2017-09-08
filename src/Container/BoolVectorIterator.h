#ifndef BOOL_VECTOR_ITERATOR_INCLUDED
#define BOOL_VECTOR_ITERATOR_INCLUDED

#include "BoolVector.h"
#include "Iterator.h"

#include <type_traits>

namespace Cellwars
{
    template <typename T>
    class BoolVectorIterator
    {
    public:
        using Category = RandomAccessIteratorTag;
        using ValueType = T;
        using DifferenceType = ptrdiff_t;
        using Reference = typename std::conditional<std::is_const<T>::value, bool, BoolVector::Proxy>::type;
        using ConstReference = bool;

    private:
        using ProxyType = typename std::conditional<std::is_const<T>::value, BoolVector::ConstProxy, BoolVector::Proxy>::type;

    public:
        BoolVectorIterator ();
        BoolVectorIterator (T* p, unsigned offset);

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
        unsigned offset;
    };
};

#include "BoolVectorIterator.inl"

#endif /* BOOL_VECTOR_ITERATOR_INCLUDED */
