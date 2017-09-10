#ifndef ITERATOR_TAG_INCLUDED
#define ITERATOR_TAG_INCLUDED

/*! @file IteratorTag.h
 *
 *  Declares the three basic types of iterators.
 *  These types are:
 *  - forward (e.g. singly linked list)
 *  - bidirectional (e.g. doubly linked list)
 *  - random-access (e.g. plain array)
 *
 *  No other iteration type really makes sense -- neither for containers,
 *  not for algorithms.
 *
 *  This file just defines the 'tags'. These are going to be used to
 *  identify the underlying iterator type (via std::is_same or std::is_base_of,
 *  for example).
 */

namespace Cellwars
{
    struct ForwardIteratorTag
    {
    };

    struct BidirectionalIteratorTag : ForwardIteratorTag
    {
    };

    struct RandomAccessIteratorTag : BidirectionalIteratorTag
    {
    };
};

#endif /* ITERATOR_TAG_INCLUDED */
