#include "ReverseIterator.h"

template <typename T>
auto Cellwars::RBegin (T& container) -> decltype (container.RBegin ())
{
    return container.RBegin ();
}

template <typename T, unsigned N>
Cellwars::ReverseRandomAccessIterator<T> Cellwars::RBegin (T (&arr)[N])
{
    return Cellwars::ReverseRandomAccessIterator<T> (arr + N - 1);
}

template <typename T>
auto Cellwars::REnd (T& container) -> decltype (container.REnd ())
{
    return container.REnd ();
}

template <typename T, unsigned N>
Cellwars::ReverseRandomAccessIterator<T> Cellwars::REnd (T (&arr)[N])
{
    return Cellwars::ReverseRandomAccessIterator<T> (arr - 1);
}

template <typename T>
auto Cellwars::CRBegin (const T& container) -> decltype (container.CRBegin ())
{
    return container.CRBegin ();
}

template <typename T, unsigned N>
Cellwars::ReverseRandomAccessIterator<const T> Cellwars::CRBegin (const T (&arr)[N])
{
    return Cellwars::ReverseRandomAccessIterator<const T> (arr + N - 1);
}

template <typename T>
auto Cellwars::CREnd (const T& container) -> decltype (container.CREnd ())
{
    return container.CREnd ();
}

template <typename T, unsigned N>
Cellwars::ReverseRandomAccessIterator<const T> Cellwars::CREnd (const T (&arr)[N])
{
    return Cellwars::ReverseRandomAccessIterator<const T> (arr - 1);
}

template <typename T>
Cellwars::ReverseForwardIterator<T>::ReverseForwardIterator (Pointer p) : p (p)
{
}

template <typename T>
bool Cellwars::ReverseForwardIterator<T>::operator== (ReverseForwardIterator rhs)
{
    return p == rhs.p;
}

template <typename T>
bool Cellwars::ReverseForwardIterator<T>::operator!= (ReverseForwardIterator rhs)
{
    return p != rhs.p;
}

template <typename T>
bool Cellwars::ReverseForwardIterator<T>::operator! ()
{
    return !p;
}

template <typename T>
typename Cellwars::ReverseForwardIterator<T>::Reference Cellwars::ReverseForwardIterator<T>::operator* ()
{
    return *p;
}

template <typename T>
typename Cellwars::ReverseForwardIterator<T>::Pointer Cellwars::ReverseForwardIterator<T>::operator-> ()
{
    return p;
}

template <typename T>
Cellwars::ReverseForwardIterator<T> Cellwars::ReverseForwardIterator<T>::operator++ ()
{
    --p;
    return (*this);
}

template <typename T>
Cellwars::ReverseForwardIterator<T> Cellwars::ReverseForwardIterator<T>::operator++ (int)
{
    return ReverseForwardIterator<T> (p--);
}

template <typename T>
Cellwars::ReverseBidirectionalIterator<T>::ReverseBidirectionalIterator (Pointer p) : ReverseForwardIterator<T> (p)
{
}

template <typename T>
Cellwars::ReverseBidirectionalIterator<T> Cellwars::ReverseBidirectionalIterator<T>::operator-- ()
{
    ++p;
    return (*this);
}

template <typename T>
Cellwars::ReverseBidirectionalIterator<T> Cellwars::ReverseBidirectionalIterator<T>::operator-- (int)
{
    return ReverseBidirectionalIterator (p++);
}

template <typename T>
Cellwars::ReverseRandomAccessIterator<T>::ReverseRandomAccessIterator (Pointer p) : ReverseBidirectionalIterator<T> (p)
{
}

template <typename T>
Cellwars::ReverseRandomAccessIterator<T> Cellwars::ReverseRandomAccessIterator<T>::operator+= (unsigned n)
{
    p -= n;
    return (*this);
}

template <typename T>
Cellwars::ReverseRandomAccessIterator<T> Cellwars::ReverseRandomAccessIterator<T>::operator-= (unsigned n)
{
    p += n;
    return (*this);
}

template <typename T>
Cellwars::ReverseRandomAccessIterator<T> Cellwars::ReverseRandomAccessIterator<T>::operator+ (unsigned n)
{
    return ReverseRandomAccessIterator (p - n);
}

template <typename T>
Cellwars::ReverseRandomAccessIterator<T> Cellwars::ReverseRandomAccessIterator<T>::operator- (unsigned n)
{
    return ReverseRandomAccessIterator (p + n);
}

template <typename T>
typename Cellwars::ReverseRandomAccessIterator<T>::DifferenceType
Cellwars::ReverseRandomAccessIterator<T>::operator- (ReverseRandomAccessIterator rhs)
{
    return rhs.p - p;
}

template <typename T>
bool Cellwars::ReverseRandomAccessIterator<T>::operator< (ReverseRandomAccessIterator rhs)
{
    return p > rhs.p;
}

template <typename T>
bool Cellwars::ReverseRandomAccessIterator<T>::operator> (ReverseRandomAccessIterator rhs)
{
    return p < rhs.p;
}

template <typename T>
bool Cellwars::ReverseRandomAccessIterator<T>::operator<= (ReverseRandomAccessIterator rhs)
{
    return p >= rhs.p;
}

template <typename T>
bool Cellwars::ReverseRandomAccessIterator<T>::operator>= (ReverseRandomAccessIterator rhs)
{
    return p <= rhs.p;
}

template <typename T>
typename Cellwars::ReverseRandomAccessIterator<T>::Reference
Cellwars::ReverseRandomAccessIterator<T>::operator[] (unsigned n)
{
    return *((*this) + n);
}
