#include "BoolVectorIterator.h"

template <typename T>
Cellwars::BoolVectorIterator<T>::BoolVectorIterator () : p (NULL), offset (0)
{
}

template <typename T>
Cellwars::BoolVectorIterator<T>::BoolVectorIterator (T* p, unsigned offset) : p (p), offset (offset)
{
}

template <typename T>
bool Cellwars::BoolVectorIterator<T>::operator== (const Cellwars::BoolVectorIterator<T>& rhs) const
{
    return p == rhs.p && offset == rhs.offset;
}

template <typename T>
bool Cellwars::BoolVectorIterator<T>::operator!= (const Cellwars::BoolVectorIterator<T>& rhs) const
{
    return !((*this) == rhs);
}

template <typename T>
typename Cellwars::BoolVectorIterator<T>::ConstReference Cellwars::BoolVectorIterator<T>::operator* () const
{
    return ProxyType (p, offset);
}

template <typename T>
typename Cellwars::BoolVectorIterator<T>::Reference Cellwars::BoolVectorIterator<T>::operator* ()
{
    return ProxyType (p, offset);
}

template <typename T>
typename Cellwars::BoolVectorIterator<T>::ConstReference Cellwars::BoolVectorIterator<T>::operator[] (unsigned idx) const
{
    return *((*this) + idx);
}

template <typename T>
typename Cellwars::BoolVectorIterator<T>::Reference Cellwars::BoolVectorIterator<T>::operator[] (unsigned idx)
{
    return *((*this) + idx);
}

template <typename T>
Cellwars::BoolVectorIterator<T>& Cellwars::BoolVectorIterator<T>::operator++ ()
{
    return (*this) += 1;
}

template <typename T>
Cellwars::BoolVectorIterator<T> Cellwars::BoolVectorIterator<T>::operator++ (int)
{
    Cellwars::BoolVectorIterator<T> res (*this);
    ++(*this);

    return res;
}

template <typename T>
Cellwars::BoolVectorIterator<T>& Cellwars::BoolVectorIterator<T>::operator-- ()
{
    return (*this) -= 1;
}

template <typename T>
Cellwars::BoolVectorIterator<T> Cellwars::BoolVectorIterator<T>::operator-- (int)
{
    Cellwars::BoolVectorIterator<T> res (*this);
    --(*this);

    return res;
}

template <typename T>
Cellwars::BoolVectorIterator<T>& Cellwars::BoolVectorIterator<T>::operator+= (unsigned n)
{
    offset += n;
    p += (offset >> BoolVector::Shift);
    offset &= BoolVector::Mask;

    return (*this);
}

template <typename T>
Cellwars::BoolVectorIterator<T>& Cellwars::BoolVectorIterator<T>::operator-= (unsigned n)
{
    p -= (n >> BoolVector::Shift);
    n &= BoolVector::Mask;

    if (n > offset)
    {
        --p;
        offset += BoolVector::Bits - n;
    }
    else
    {
        offset -= n;
    }

    return (*this);
}

template <typename T>
Cellwars::BoolVectorIterator<T> Cellwars::BoolVectorIterator<T>::operator+ (unsigned n) const
{
    Cellwars::BoolVectorIterator<T> res (*this);
    res += n;

    return res;
}

template <typename T>
Cellwars::BoolVectorIterator<T> Cellwars::BoolVectorIterator<T>::operator- (unsigned n) const
{
    Cellwars::BoolVectorIterator<T> res (*this);
    res -= n;

    return res;
}

template <typename T>
typename Cellwars::BoolVectorIterator<T>::DifferenceType Cellwars::BoolVectorIterator<T>::operator- (const Cellwars::BoolVectorIterator<T>& rhs) const
{
    DifferenceType res = (p - rhs.p) >> BoolVector::Shift;
    res += offset;
    res -= rhs.offset;

    return res;
}

template <typename T>
bool Cellwars::BoolVectorIterator<T>::operator< (const Cellwars::BoolVectorIterator<T>& rhs) const
{
    return p < rhs.p || (p == rhs.p && offset < rhs.offset);
}

template <typename T>
bool Cellwars::BoolVectorIterator<T>::operator> (const Cellwars::BoolVectorIterator<T>& rhs) const
{
    return rhs < (*this);
}

template <typename T>
bool Cellwars::BoolVectorIterator<T>::operator<= (const Cellwars::BoolVectorIterator<T>& rhs) const
{
    return !((*this) > rhs);
}

template <typename T>
bool Cellwars::BoolVectorIterator<T>::operator>= (const Cellwars::BoolVectorIterator<T>& rhs) const
{
    return !((*this) < rhs);
}
