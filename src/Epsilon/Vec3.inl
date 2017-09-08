#include "Vec3.h"
#include "Utility.h"
#include <logger/logger.h>

template <typename T>
Cellwars::Vec3<T>::Vec3 (T x, T y, T z) : Vec2<T> (x, y), z (z)
{
}

template <typename T>
Cellwars::Vec3<T>::Vec3 (const Vec2<T>& v, T z) : Vec2<T> (v), z (z)
{
}

template <typename T>
const Cellwars::Vec3<T>& Cellwars::Vec3<T>::operator+= (const Vec3<T>& rhs)
{
    Vec2<T>::operator+= (rhs);
    z += rhs.z;
    return (*this);
}

template <typename T>
const Cellwars::Vec3<T>& Cellwars::Vec3<T>::operator-= (const Vec3& rhs)
{
    Vec2<T>::operator-= (rhs);
    z -= rhs.z;
    return (*this);
}

template <typename T>
const Cellwars::Vec3<T> Cellwars::Vec3<T>::operator+ (const Vec3<T>& rhs) const
{
    Vec3<T> res (*this);
    res += rhs;
    return res;
}

template <typename T>
const Cellwars::Vec3<T> Cellwars::Vec3<T>::operator- (const Vec3<T>& rhs) const
{
    Vec3<T> res (*this);
    res -= rhs;
    return res;
}

template <typename T>
const Cellwars::Vec3<T> Cellwars::Vec3<T>::operator- () const
{
    return Vec3 (Vec2<T>::operator- (), -z);
}

template <typename T>
const Cellwars::Vec3<T>& Cellwars::Vec3<T>::operator*= (T scalar)
{
    Vec2<T>::operator*= (scalar);
    z *= scalar;
    return (*this);
}

template <typename T>
const Cellwars::Vec3<T>& Cellwars::Vec3<T>::operator/= (T scalar)
{
    logAssert (!IsEqual (scalar, (T)0));
    return (*this) *= ((T)1 / scalar);
}

template <typename T>
const Cellwars::Vec3<T> Cellwars::Vec3<T>::operator* (T scalar) const
{
    Vec3<T> res (*this);
    res *= scalar;
    return res;
}

template <typename T>
const Cellwars::Vec3<T> Cellwars::Vec3<T>::operator/ (T scalar) const
{
    Vec3<T> res (*this);
    res /= scalar;
    return res;
}
