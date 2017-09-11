#ifndef ITERATOR_INCLUDED
#define ITERATOR_INCLUDED

#include "IteratorTag.h"
#include <cstddef>

/*! @file Iterator.h
 *
 *  Implementation of iterator pattern for array.
 *  Declares four classes - ForwardIterator, BidirectionalIterator,
 *  RandomAccessIterator. These implement the tags decribed in
 *  @sa @file IteratorTag.h for plain array types.
 */

namespace Cellwars
{

    template <typename T>
    class ForwardIterator
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
        explicit ForwardIterator (Pointer p = NULL);
        bool operator== (ForwardIterator rhs);
        bool operator!= (ForwardIterator rhs);
        bool operator! ();

        Reference operator* ();
        Pointer operator-> ();

        ForwardIterator operator++ ();
        ForwardIterator operator++ (int);

    protected:
        Pointer p;
    };

    template <typename T>
    class BidirectionalIterator : public ForwardIterator<T>
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
        explicit BidirectionalIterator (Pointer p = NULL);
        BidirectionalIterator operator-- ();
        BidirectionalIterator operator-- (int);

    protected:
        using ForwardIterator<T>::p;
    };

    template <typename T>
    class RandomAccessIterator : public BidirectionalIterator<T>
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
        explicit RandomAccessIterator (Pointer p = NULL);
        RandomAccessIterator operator+= (unsigned n);
        RandomAccessIterator operator-= (unsigned n);
        RandomAccessIterator operator+ (unsigned n);
        RandomAccessIterator operator- (unsigned n);
        DifferenceType operator- (RandomAccessIterator rhs);

        bool operator< (RandomAccessIterator rhs);
        bool operator> (RandomAccessIterator rhs);
        bool operator<= (RandomAccessIterator rhs);
        bool operator>= (RandomAccessIterator rhs);

        Reference operator[] (unsigned n);

    protected:
        using BidirectionalIterator<T>::p;
    };

    template <typename T>
    auto Begin (T& container) -> decltype (container.Begin ());

    template <typename T, unsigned N>
    Cellwars::RandomAccessIterator<T> Begin (T (&arr)[N]);

    template <typename T>
    auto End (T& container) -> decltype (container.End ());

    template <typename T, unsigned N>
    Cellwars::RandomAccessIterator<T> End (T (&arr)[N]);

    template <typename T>
    auto CBegin (const T& container) -> decltype (container.CBegin ());

    template <typename T, unsigned N>
    Cellwars::RandomAccessIterator<const T> CBegin (const T (&arr)[N]);

    template <typename T>
    auto CEnd (const T& container) -> decltype (container.CEnd ());

    template <typename T, unsigned N>
    Cellwars::RandomAccessIterator<const T> CEnd (const T (&arr)[N]);
};

#include "Iterator.inl"

#endif /* ITERATOR_INCLUDED */
