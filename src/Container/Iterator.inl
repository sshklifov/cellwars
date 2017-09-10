#include "Iterator.h"

template <typename T>
auto Cellwars::Begin (T& container) -> decltype (container.Begin ())
{
    return container.Begin ();
}

template <typename T, unsigned N>
Cellwars::RandomAccessIterator<T> Cellwars::Begin (T (&arr)[N])
{
    return Cellwars::RandomAccessIterator<T> (arr);
}

template <typename T>
auto Cellwars::End (T& container) -> decltype (container.End ())
{
    return container.End ();
}

template <typename T, unsigned N>
Cellwars::RandomAccessIterator<T> Cellwars::End (T (&arr)[N])
{
    return Cellwars::RandomAccessIterator<T> (arr + N);
}

template <typename T>
auto Cellwars::CBegin (const T& container) -> decltype (container.CBegin ())
{
    return container.CBegin ();
}

template <typename T, unsigned N>
Cellwars::RandomAccessIterator<const T> Cellwars::CBegin (const T (&arr)[N])
{
    return Cellwars::RandomAccessIterator<const T> (arr);
}

template <typename T>
auto Cellwars::CEnd (const T& container) -> decltype (container.CEnd ())
{
    return container.End ();
}

template <typename T, unsigned N>
Cellwars::RandomAccessIterator<const T> Cellwars::CEnd (const T (&arr)[N])
{
    return Cellwars::RandomAccessIterator<const T> (arr + N);
}

template <typename T>
Cellwars::ForwardIterator<T>::ForwardIterator (Pointer p) : p (p)
{
}

template <typename T>
bool Cellwars::ForwardIterator<T>::operator== (ForwardIterator rhs)
{
    return p == rhs.p;
}

template <typename T>
bool Cellwars::ForwardIterator<T>::operator!= (ForwardIterator rhs)
{
    return p != rhs.p;
}

template <typename T>
bool Cellwars::ForwardIterator<T>::operator! ()
{
    return !p;
}

template <typename T>
typename Cellwars::ForwardIterator<T>::Reference Cellwars::ForwardIterator<T>::operator* ()
{
    return *p;
}

template <typename T>
typename Cellwars::ForwardIterator<T>::Pointer Cellwars::ForwardIterator<T>::operator-> ()
{
    return p;
}

template <typename T>
Cellwars::ForwardIterator<T> Cellwars::ForwardIterator<T>::operator++ ()
{
    ++p;
    return (*this);
}

template <typename T>
Cellwars::ForwardIterator<T> Cellwars::ForwardIterator<T>::operator++ (int)
{
    return ForwardIterator (p++);
}

template <typename T>
Cellwars::BidirectionalIterator<T>::BidirectionalIterator (Pointer p) : ForwardIterator<T> (p)
{
}

template <typename T>
Cellwars::BidirectionalIterator<T> Cellwars::BidirectionalIterator<T>::operator-- ()
{
    --p;
    return (*this);
}

template <typename T>
Cellwars::BidirectionalIterator<T> Cellwars::BidirectionalIterator<T>::operator-- (int)
{
    return BidirectionalIterator (p--);
}

template <typename T>
Cellwars::RandomAccessIterator<T>::RandomAccessIterator (Pointer p) : BidirectionalIterator<T> (p)
{
}

template <typename T>
Cellwars::RandomAccessIterator<T> Cellwars::RandomAccessIterator<T>::operator+= (unsigned n)
{
    p += n;
    return (*this);
}

template <typename T>
Cellwars::RandomAccessIterator<T> Cellwars::RandomAccessIterator<T>::operator-= (unsigned n)
{
    p -= n;
    return (*this);
}

template <typename T>
Cellwars::RandomAccessIterator<T> Cellwars::RandomAccessIterator<T>::operator+ (unsigned n)
{
    return RandomAccessIterator (p + n);
}

template <typename T>
Cellwars::RandomAccessIterator<T> Cellwars::RandomAccessIterator<T>::operator- (unsigned n)
{
    return RandomAccessIterator (p - n);
}

template <typename T>
typename Cellwars::RandomAccessIterator<T>::DifferenceType
Cellwars::RandomAccessIterator<T>::operator- (RandomAccessIterator rhs)
{
    return p - rhs.p;
}

template <typename T>
bool Cellwars::RandomAccessIterator<T>::operator< (RandomAccessIterator rhs)
{
    return p < rhs.p;
}

template <typename T>
bool Cellwars::RandomAccessIterator<T>::operator> (RandomAccessIterator rhs)
{
    return p > rhs.p;
}

template <typename T>
bool Cellwars::RandomAccessIterator<T>::operator<= (RandomAccessIterator rhs)
{
    return p <= rhs.p;
}

template <typename T>
bool Cellwars::RandomAccessIterator<T>::operator>= (RandomAccessIterator rhs)
{
    return p >= rhs.p;
}

template <typename T>
typename Cellwars::RandomAccessIterator<T>::Reference Cellwars::RandomAccessIterator<T>::operator[] (unsigned n)
{
    return p[n];
}
