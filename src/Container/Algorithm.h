#ifndef ALGORITHM_INCLUDED
#define ALGORITHM_INCLUDED

#include "IteratorTag.h"
#include <utility>

/*! @file Algorithm.h
 *
 *  Basic algorithm functions.
 *  Every container is an abstraction that stores data in a specific way.
 *  Iterators are the in-between class help 'iterate' this data. This file
 *  only implements the most basic algorithms, using exactly iterators. This
 *  means that any of the functions can be used on any data type, provided
 *  that they implement their own iterators and that their type is appropriate.
 */

#define ALGO_CHECK(x,y)                                                         \
        static_assert (std::is_base_of<y, typename x::Category>::value, "Invalid iterator type")

namespace Cellwars
{
    template <typename T>
    void Swap (T& a, T& b)
    {
        T c = a;
        a = b;
        b = c;
    }

    template <typename T>
    const T& Min (const T& lhs, const T& rhs)
    {
        return lhs < rhs ? lhs : rhs;
    }

    template <typename T>
    const T& Max (const T& lhs, const T& rhs)
    {
        return lhs > rhs ? lhs : rhs;
    }

    template <typename ForwardIt>
    bool IsBefore (ForwardIt lhs, ForwardIt rhs)
    {
        return IsBefore_Impl (lhs, rhs, typename ForwardIt::Category ());
    }

    template <typename ForwardIt>
    bool IsBefore_Impl (ForwardIt lhs, ForwardIt rhs, ForwardIteratorTag)
    {
        return lhs != rhs;
    }

    template <typename ForwardIt>
    bool IsBefore_Impl (ForwardIt lhs, ForwardIt rhs, BidirectionalIteratorTag)
    {
        return lhs != rhs;
    }

    template <typename ForwardIt>
    bool IsBefore_Impl (ForwardIt lhs, ForwardIt rhs, RandomAccessIteratorTag)
    {
        return lhs < rhs;
    }

    template <typename ForwardIt>
    unsigned Distance (ForwardIt first, ForwardIt last)
    {
        ALGO_CHECK (ForwardIt, ForwardIteratorTag);

        return Distance_Impl (first, last, typename ForwardIt::Category ());
    }

    template <typename ForwardIt>
    unsigned Distance_Impl (ForwardIt first, ForwardIt last, ForwardIteratorTag)
    {
        unsigned res = 0;
        for (; first != last; ++first)
        {
            ++res;
        }

        return res;
    }

    template <typename BidirectionIt>
    unsigned Distance_Impl (BidirectionIt first, BidirectionIt last, BidirectionalIteratorTag)
    {
        return Distance_Impl (first, last, ForwardIteratorTag ());
    }

    template <typename RandomAccessIt>
    unsigned Distance_Impl (RandomAccessIt first, RandomAccessIt last, RandomAccessIteratorTag)
    {
        return last - first;
    }

    template <typename ForwardIt, typename Predicate>
    void Sort (ForwardIt begin, ForwardIt end, Predicate cmp)
    {
        while (begin != end)
        {
            ForwardIt best = begin;
            for (ForwardIt curr = begin; curr != end; ++curr)
            {
                if (cmp (*curr, *best))
                {
                    best = curr;
                }
            }

            Swap (*begin, *best);
            ++begin;
        }
    }

    template <typename ForwardIt>
    void Sort (ForwardIt begin, ForwardIt end)
    {
        auto cmp = [](typename ForwardIt::ConstReference lhs, typename ForwardIt::ConstReference rhs)
        {
            return lhs < rhs;
        };

        return Sort (begin, end, cmp);
    }

    template <typename ForwardIt1, typename ForwardIt2>
    void Copy (ForwardIt1 src, unsigned n, ForwardIt2 dst)
    {
        ALGO_CHECK (ForwardIt1, ForwardIteratorTag);
        ALGO_CHECK (ForwardIt2, ForwardIteratorTag);

        for (unsigned i = 0; i < n; ++i)
        {
            *dst = *src;

            ++dst;
            ++src;
        }
    }

    template <typename ForwardIt1, typename ForwardIt2>
    void Copy (ForwardIt1 first, ForwardIt1 last, ForwardIt2 dst)
    {
        ALGO_CHECK (ForwardIt1, ForwardIteratorTag);
        ALGO_CHECK (ForwardIt2, ForwardIteratorTag);

        for (; IsBefore (first, last); ++first)
        {
            *dst = *first;

            ++dst;
        }
    }

    template <typename ForwardIt1, typename ForwardIt2>
    void Move (ForwardIt1 src, unsigned n, ForwardIt2 dst)
    {
        ALGO_CHECK (ForwardIt1, ForwardIteratorTag);
        ALGO_CHECK (ForwardIt2, ForwardIteratorTag);

        for (unsigned i = 0; i < n; ++i)
        {
            *dst = std::move (*src);

            ++dst;
            ++src;
        }
    }
    
    template <typename ForwardIt1, typename ForwardIt2>
    void Move (ForwardIt1 first, ForwardIt1 last, ForwardIt2 dst)
    {
        ALGO_CHECK (ForwardIt1, ForwardIteratorTag);
        ALGO_CHECK (ForwardIt2, ForwardIteratorTag);

        for (; IsBefore (first, last); ++first)
        {
            *dst = std::move (*first);

            ++dst;
        }
    }

    template <typename ForwardIt, typename T>
    void Fill (ForwardIt dst, const T& val, unsigned n)
    {
        ALGO_CHECK (ForwardIt, ForwardIteratorTag);

        for (unsigned i = 0; i < n; ++i)
        {
            *dst = val;
            ++dst;
        }
    }

    template <typename ForwardIt1, typename ForwardIt2>
    bool Equal (ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
    {
        ALGO_CHECK (ForwardIt1, ForwardIteratorTag);
        ALGO_CHECK (ForwardIt2, ForwardIteratorTag);

        for (; IsBefore (first1, last1) && IsBefore (first2, last2); ++first1, ++first2)
        {
            if (*first1 != *first2)
            {
                break;
            }
        }

        return first1 == last1 && first2 == last2;
    }

    template <typename ForwardIt, typename T>
    ForwardIt Find (ForwardIt first, ForwardIt last, const T& val)
    {
        ALGO_CHECK (ForwardIt, ForwardIteratorTag);

        auto pred = [](typename ForwardIt::ConstReference it_val, const T& val)
        {
            return it_val == val;
        };

        return Find (first, last, val, pred);
    }

    template <typename ForwardIt, typename T, typename Predicate>
    ForwardIt Find (ForwardIt first, ForwardIt last, const T& val, Predicate pred)
    {
        ALGO_CHECK (ForwardIt, ForwardIteratorTag);

        for (; IsBefore (first, last); ++first)
        {
            if (pred (*first, val))
            {
                break;
            }
        }

        return first;
    }

    template <typename ForwardIt, typename T>
    ForwardIt FindN (ForwardIt first, ForwardIt last, unsigned n, const T& val)
    {
        ALGO_CHECK (ForwardIt, ForwardIteratorTag);

        auto pred = [](typename ForwardIt::ConstReference it_val, const T& val)
        {
            return it_val == val;
        };

        return FindN (first, last, n, val, pred);
    }

    template <typename ForwardIt, typename T, typename Predicate>
    ForwardIt FindN (ForwardIt first, ForwardIt last, unsigned n, const T& val, Predicate pred)
    {
        while (n--)
        {
            first = Find (first, last, val, pred);
            if (!IsBefore (first, last) || n == 0)
            {
                break;
            }

            ++first;
        }

        return first;
    }

    template <typename ForwardIt1, typename ForwardIt2>
    ForwardIt1 FindSubset (ForwardIt1 first1, ForwardIt1 last1, ForwardIt2 first2, ForwardIt2 last2)
    {
        ALGO_CHECK (ForwardIt1, ForwardIteratorTag);
        ALGO_CHECK (ForwardIt2, ForwardIteratorTag);

        for (; IsBefore (first1, last1); ++first1)
        {
            ForwardIt1 it1 = first1;
            ForwardIt2 it2 = first2;

            for (; IsBefore (it1, last1) && IsBefore (it2, last2); ++it1, ++it2)
            {
                if (*it1 != *it2)
                {
                    break;
                }
            }

            if (it2 == last2)
            {
                break;
            }
        }

        return first1;
    }

    template <typename ForwardIt1, typename ForwardIt2>
    ForwardIt1 Search (ForwardIt1 first, ForwardIt1 last, ForwardIt2 s_first, ForwardIt2 s_last)
    {
        ALGO_CHECK (ForwardIt1, ForwardIteratorTag);
        ALGO_CHECK (ForwardIt2, ForwardIteratorTag);

        auto find = [&s_first, &s_last](typename ForwardIt1::ConstReference val)
        {
            return IsBefore (Find (s_first, s_last, val), s_last);
        };

        return Search (first, last, find);
    }

    template <typename ForwardIt1, typename FindFun>
    ForwardIt1 Search (ForwardIt1 first, ForwardIt1 last, FindFun find)
    {
        ALGO_CHECK (ForwardIt1, ForwardIteratorTag);

        for (; IsBefore (first, last); ++first)
        {
            if (find (*first))
            {
                break;
            }
        }

        return first;
    }

    template <typename ForwardIt1, typename ForwardIt2>
    ForwardIt1 SearchN (ForwardIt1 first, ForwardIt1 last, unsigned n, ForwardIt2 s_first, ForwardIt2 s_last)
    {
        ALGO_CHECK (ForwardIt1, ForwardIteratorTag);
        ALGO_CHECK (ForwardIt2, ForwardIteratorTag);

        auto find = [&s_first, &s_last](typename ForwardIt1::ConstReference val)
        {
            return IsBefore (Find (s_first, s_last, val), s_last);
        };

        return SearchN (first, last, n, find);
    }

    template <typename ForwardIt1, typename FindFun>
    ForwardIt1 SearchN (ForwardIt1 first, ForwardIt1 last, unsigned n, FindFun find)
    {
        while (n--)
        {
            first = Search (first, last, find);
            if (!IsBefore (first, last) || n == 0)
            {
                break;
            }

            ++first;
        }

        return first;
    }
};

#endif /* ALGORITHM_INCLUDED */
