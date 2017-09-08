#ifndef REVERSE_ITERATOR_INCLUDED
#define REVERSE_ITERATOR_INCLUDED

#include "Iterator.h"

namespace Cellwars
{
    template <typename T>
    class ReverseOutputIterator
    {
    public:
        using ValueType = T;
        using DifferenceType = ptrdiff_t;
        using Pointer = T*;
        using Reference = T&;
        using Category = OutputIteratorTag;

    public:
        explicit ReverseOutputIterator (Pointer p = NULL);

        Reference operator* ();
        Pointer operator-> ();
        ReverseOutputIterator operator++ ();
        ReverseOutputIterator operator++ (int);

    private:
        explicit ReverseOutputIterator (OutputIterator<T> it);

    private:
        OutputIterator<T> it;
    };

    template <typename T>
    class ReverseForwardIterator
    {
    public:
        using ValueType = T;
        using DifferenceType = ptrdiff_t;
        using Pointer = T*;
        using Reference = T&;
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

    private:
        explicit ReverseForwardIterator (ForwardIterator<T> it);

    private:
        ForwardIterator<T> it;
    };

    template <typename T>
    class ReverseBidirectionalIterator
    {
    public:
        using ValueType = T;
        using DifferenceType = ptrdiff_t;
        using Pointer = T*;
        using Reference = T&;
        using Category = BidirectionalIteratorTag;

    public:
        explicit ReverseBidirectionalIterator (Pointer p = NULL);

        ReverseBidirectionalIterator operator-- ();
        ReverseBidirectionalIterator operator-- (int);

    private:
        explicit ReverseBidirectionalIterator (BidirectionalIterator<T> it);

    private:
        BidirectionalIterator<T> it;
    };

    template <typename T>
    class ReverseRandomAccessIterator
    {
    public:
        using ValueType = T;
        using DifferenceType = ptrdiff_t;
        using Pointer = T*;
        using Reference = T&;
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

    private:
        explicit ReverseRandomAccessIterator (RandomAccessIterator<T> it);

    private:
        RandomAccessIterator<T> it;
    };

};

#endif /* REVERSE_ITERATOR_INCLUDED */
