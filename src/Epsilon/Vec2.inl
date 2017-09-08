#include "Vec.h"
#include "Utility.h"
#include <logger/logger.h>

#include <cmath>

template <typename T>
Cellwars::Vec2<T>::Vec2 (T x, T y) : x (x), y (y)
{
}

template <typename T>
const Cellwars::Vec2<T>& Cellwars::Vec2<T>::operator+= (const Vec2<T>& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return (*this);
}

template <typename T>
const Cellwars::Vec2<T>& Cellwars::Vec2<T>::operator-= (const Vec2<T>& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return (*this);
}

template <typename T>
const Cellwars::Vec2<T> Cellwars::operator+ (const Vec2<T>& lhs, const Vec2<T>& rhs)
{
    Vec2<T> res (lhs);
    return res += rhs;
}

template <typename T>
const Cellwars::Vec2<T> Cellwars::operator- (const Vec2<T>& lhs, const Vec2<T>& rhs)
{
    Vec2<T> res (lhs);
    return res -= rhs;
}

template <typename T>
const Cellwars::Vec2<T> Cellwars::Vec2<T>::operator- () const
{
    return Vec2 (-x, -y);
}

template <typename T>
const Cellwars::Vec2<T>& Cellwars::Vec2<T>::operator*= (T scalar)
{
    x *= scalar;
    y *= scalar;
    return (*this);
}

template <typename T>
const Cellwars::Vec2<T>& Cellwars::Vec2<T>::operator/= (T scalar)
{
    logAssert (!IsEqual (scalar, (T)0));
    return (*this) *= ((T)1 / scalar);
}

template <typename T>
const Cellwars::Vec2<T> Cellwars::operator* (const Vec2<T>& v, T scalar)
{
    Vec2<T> res (v);
    return res *= scalar;
}

template <typename T>
const Cellwars::Vec2<T> Cellwars::operator/ (const Vec2<T>& v, T scalar)
{
    Vec2<T> res (v);
    return res /= scalar;
}

template <typename T>
void Cellwars::Vec2<T>::Normalize ()
{
    logAssert (!IsDegenerate ());
    (*this) /= Distance ();
}

template <typename T>
bool Cellwars::Vec2<T>::IsDegenerate () const
{
    return IsEqual (x, (T)0) && IsEqual (y, (T)0);
}

template <typename T>
Cellwars::Point2<T> Cellwars::Vec2<T>::Translate (const Point2<T>& p) const
{
    return Point2<T> (x + p.x, y + p.y);
}

template <typename T>
T Cellwars::Vec2<T>::Dot (const Vec2<T>& rhs) const
{
    return x * rhs.x + y * rhs.y;
}

template <typename T>
T Cellwars::Vec2<T>::Distance2 () const
{
    return x * x + y * y;
}

template <typename T>
T Cellwars::Vec2<T>::Distance () const
{
    return sqrt (Distance2 ());
}

template <typename T>
T Cellwars::Vec2<T>::Cross (const Vec2<T>& rhs) const
{
    return x * rhs.y - y * rhs.x;
}

template <typename T>
bool Cellwars::Vec2<T>::IsPerpendicular (const Vec2<T>& rhs) const
{
    logAssert (!IsDegenerate () && !rhs.IsDegenerate ());

    return IsEqual (Dot (rhs), (T)0);
}

template <typename T>
bool Cellwars::Vec2<T>::IsParallel (const Vec2<T>& rhs) const
{
    logAssert (!IsDegenerate () && !rhs.IsDegenerate ());

    return IsEqual (Cross (rhs), (T)0);
}

template <typename T>
Cellwars::Vec2<T> Cellwars::Vec2<T>::Normal () const
{
    logAssert (!IsDegenerate ());
    return Vec2<T> (-y, x);
}

template <typename T>
Cellwars::Point2<T> Cellwars::Translate (const Point2<T>& p, const Vec2<T>& v)
{
    return v.Translate (p);
}

template <typename T>
T Cellwars::Dot (const Vec2<T>& v1, const Vec2<T>& v2)
{
    return v1.Dot (v2);
}

template <typename T>
T Cellwars::Cross (const Vec2<T>& v1, const Vec2<T>& v2)
{
    return v1.Cross (v2);
}

template <typename T>
bool Cellwars::IsPerpendicular (const Vec2<T>& v1, const Vec2<T>& v2)
{
    return v1.IsPerpendicular (v2);
}

template <typename T>
bool Cellwars::IsParallel (const Vec2<T>& v1, const Vec2<T>& v2)
{
    return v1.IsParallel (v2);
}
