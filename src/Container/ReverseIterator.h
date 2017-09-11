#ifndef REVERSE_ITERATOR_INCLUDED
#define REVERSE_ITERATOR_INCLUDED

#include "IteratorTag.h"
#include <cstddef>

/*! @file ReverseIterator.h
 *
 *  Implementation of iterator pattern for array.
 *  Declares four classes - ReverseForwardIterator, ReverseBidirectionalIterator,
 *  ReverseRandomAccessIterator. These implement the tags decribed in
 *  @sa @file IteratorTag.h for plain array types. Iteration is done in reverse
 */

namespace Cellwars
{
    template <typename T>
    class ReverseForwardIterator
    {
    public:
        using ValueType = T;
        using DifferenceType = ptrdiff_t;
        using Pointer = T*;
        using ConstPointer = const T*;
        using Reference = T&;
        using ConstReference = const T&;
        using Category = ForwardIteratorTag;

    public:
        explicit ReverseForwardIterator (Pointer p = NULL);
        bool operator== (ReverseForwardIterator rhs);
        bool operator!= (ReverseForwardIterator rhs);
        bool operator! ();

        Reference operator* ();
        Pointer operator-> ();

        ReverseForwardIterator operator++ ();
        ReverseForwardIterator operator++ (int);

    protected:
        Pointer p;
    };

    template <typename T>
    class ReverseBidirectionalIterator : public ReverseForwardIterator<T>
    {
    public:
        using ValueType = T;
        using DifferenceType = ptrdiff_t;
        using Pointer = T*;
        using ConstPointer = const T*;
        using Reference = T&;
        using ConstReference = const T&;
        using Category = BidirectionalIteratorTag;

    public:
        explicit ReverseBidirectionalIterator (Pointer p = NULL);
        ReverseBidirectionalIterator operator-- ();
        ReverseBidirectionalIterator operator-- (int);

    protected:
        using ReverseForwardIterator<T>::p;
    };

    template <typename T>
    class ReverseRandomAccessIterator : public ReverseBidirectionalIterator<T>
    {
    public:
        using ValueType = T;
        using DifferenceType = ptrdiff_t;
        using Pointer = T*;
        using ConstPointer = const T*;
        using Reference = T&;
        using ConstReference = const T&;
        using Category = RandomAccessIteratorTag;

    public:
        explicit ReverseRandomAccessIterator (Pointer p = NULL);
        ReverseRandomAccessIterator operator+= (unsigned n);
        ReverseRandomAccessIterator operator-= (unsigned n);
        ReverseRandomAccessIterator operator+ (unsigned n);
        ReverseRandomAccessIterator operator- (unsigned n);
        DifferenceType operator- (ReverseRandomAccessIterator rhs);

        bool operator< (ReverseRandomAccessIterator rhs);
        bool operator> (ReverseRandomAccessIterator rhs);
        bool operator<= (ReverseRandomAccessIterator rhs);
        bool operator>= (ReverseRandomAccessIterator rhs);

        Reference operator[] (unsigned n);

    protected:
        using ReverseBidirectionalIterator<T>::p;
    };

    template <typename T>
    auto RBegin (T& container) -> decltype (container.RBegin ());

    template <typename T, unsigned N>
    Cellwars::ReverseRandomAccessIterator<T> RBegin (T (&arr)[N]);

    template <typename T>
    auto REnd (T& container) -> decltype (container.REnd ());

    template <typename T, unsigned N>
    Cellwars::ReverseRandomAccessIterator<T> REnd (T (&arr)[N]);

    template <typename T>
    auto CRBegin (const T& container) -> decltype (container.CRBegin ());

    template <typename T, unsigned N>
    Cellwars::ReverseRandomAccessIterator<const T> CRBegin (const T (&arr)[N]);

    template <typename T>
    auto CREnd (const T& container) -> decltype (container.CREnd ());

    template <typename T, unsigned N>
    Cellwars::ReverseRandomAccessIterator<const T> CREnd (const T (&arr)[N]);
};

#include "ReverseIterator.inl"

#endif /* REVERSE_ITERATOR_INCLUDED */
