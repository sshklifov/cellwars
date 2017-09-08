#include "BoolVectorReverseIterator.h"

#include <type_traits>

template <typename T>
Cellwars::BoolVectorReverseIterator<T>::BoolVectorReverseIterator ()
{
}

template <typename T>
Cellwars::BoolVectorReverseIterator<T>::BoolVectorReverseIterator (T* p, unsigned offset) : it (p, offset)
{
}

template <typename T>
bool Cellwars::BoolVectorReverseIterator<T>::operator== (const Cellwars::BoolVectorReverseIterator<T>& rhs) const
{
    return it == rhs.it;
}

template <typename T>
bool Cellwars::BoolVectorReverseIterator<T>::operator!= (const Cellwars::BoolVectorReverseIterator<T>& rhs) const
{
    return it != rhs.it;
}

template <typename T>
typename Cellwars::BoolVectorReverseIterator<T>::ConstReference Cellwars::BoolVectorReverseIterator<T>::operator* () const
{
    return *it;
}

template <typename T>
typename Cellwars::BoolVectorReverseIterator<T>::Reference Cellwars::BoolVectorReverseIterator<T>::operator* ()
{
    return *it;
}

template <typename T>
typename Cellwars::BoolVectorReverseIterator<T>::ConstReference Cellwars::BoolVectorReverseIterator<T>::operator[] (unsigned idx) const
{
    return *((*this) - idx);
}

template <typename T>
typename Cellwars::BoolVectorReverseIterator<T>::Reference Cellwars::BoolVectorReverseIterator<T>::operator[] (unsigned idx)
{
    return *((*this) - idx);
}

template <typename T>
Cellwars::BoolVectorReverseIterator<T>& Cellwars::BoolVectorReverseIterator<T>::operator++ ()
{
    --it;
    return (*this);
}

template <typename T>
Cellwars::BoolVectorReverseIterator<T> Cellwars::BoolVectorReverseIterator<T>::operator++ (int)
{
    Cellwars::BoolVectorReverseIterator<T> res (*this);
    --it;

    return res;
}

template <typename T>
Cellwars::BoolVectorReverseIterator<T>& Cellwars::BoolVectorReverseIterator<T>::operator-- ()
{
    ++it;
    return (*this);
}

template <typename T>
Cellwars::BoolVectorReverseIterator<T> Cellwars::BoolVectorReverseIterator<T>::operator-- (int)
{
    Cellwars::BoolVectorReverseIterator<T> res (*this);
    ++it;

    return res;
}

template <typename T>
Cellwars::BoolVectorReverseIterator<T>& Cellwars::BoolVectorReverseIterator<T>::operator+= (unsigned n)
{
    it -= n;
    return (*this);
}

template <typename T>
Cellwars::BoolVectorReverseIterator<T>& Cellwars::BoolVectorReverseIterator<T>::operator-= (unsigned n)
{
    it += n;
    return (*this);
}

template <typename T>
Cellwars::BoolVectorReverseIterator<T> Cellwars::BoolVectorReverseIterator<T>::operator+ (unsigned n) const
{
    Cellwars::BoolVectorReverseIterator<T> res (*this);
    res -= n;

    return res;
}

template <typename T>
Cellwars::BoolVectorReverseIterator<T> Cellwars::BoolVectorReverseIterator<T>::operator- (unsigned n) const
{
    Cellwars::BoolVectorReverseIterator<T> res (*this);
    res += n;

    return res;
}

template <typename T>
typename Cellwars::BoolVectorReverseIterator<T>::DifferenceType Cellwars::BoolVectorReverseIterator<T>::operator- (const Cellwars::BoolVectorReverseIterator<T>& rhs) const
{
    return rhs.it - it;
}

template <typename T>
bool Cellwars::BoolVectorReverseIterator<T>::operator< (const Cellwars::BoolVectorReverseIterator<T>& rhs) const
{
    return it > rhs.it;
}

template <typename T>
bool Cellwars::BoolVectorReverseIterator<T>::operator> (const Cellwars::BoolVectorReverseIterator<T>& rhs) const
{
    return it < rhs.it;
}

template <typename T>
bool Cellwars::BoolVectorReverseIterator<T>::operator<= (const Cellwars::BoolVectorReverseIterator<T>& rhs) const
{
    return it >= rhs.it;
}

template <typename T>
bool Cellwars::BoolVectorReverseIterator<T>::operator>= (const Cellwars::BoolVectorReverseIterator<T>& rhs) const
{
    return it <= rhs.it;
}
