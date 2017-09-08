#include "Line.h"
#include "Vec.h"
#include <logger/logger.h>

template <typename T>
Cellwars::Line<T>::Line (T a, T b, T c) : norm (a, b), offset (c)
{
}

template <typename T>
Cellwars::Line<T>::Line (const Vec2<T>& norm, T offset) : norm (norm), offset (offset)
{
}

template <typename T>
Cellwars::Line<T>::Line (const Vec2<T>& dir, const Point2<T>& p)
{
    norm = dir.Normal ();
    offset = -norm.x * p.x -norm.y * p.y;
}

template <typename T>
Cellwars::Line<T>::Line (const Point2<T>& p1, const Point2<T>& p2)
{
    norm = Direction (p1, p2).Normal ();
    offset = -norm.x * p1.x - norm.y * p1.y;
}

template <typename T>
bool Cellwars::Line<T>::IsDegenerate () const
{
    return norm.IsDegenerate ();
}

template <typename T>
T Cellwars::Line<T>::GetA () const
{
    return norm.y;
}

template <typename T>
T Cellwars::Line<T>::GetB () const
{
    return norm.x;
}

template <typename T>
T Cellwars::Line<T>::GetC () const
{
    return offset;
}

template <typename T>
Cellwars::Vec2<T> Cellwars::Line<T>::GetNorm () const
{
    return norm;
}

template <typename T>
Cellwars::Vec2<T> Cellwars::Line<T>::GetDir () const
{
    return Vec2<T> (norm.y, -norm.x);
}

template <typename T>
T Cellwars::Line<T>::Distance2 (const Point2<T>& p) const
{
    logAssert (!IsDegenerate ());

    T oriented_dst = GetA () * p.x + GetB () * p.y + GetC ();
    return oriented_dst * oriented_dst / norm.Distance2 ();
}

template <typename T>
T Cellwars::Line<T>::Distance (const Point2<T>& p) const
{
    logAssert (!IsDegenerate ());
    return sqrt (Distance2 (p));
}

template <typename T>
void Cellwars::Line<T>::Normalize ()
{
    logAssert (!IsDegenerate ());

    T factor = norm.Distance ();
    norm /= factor;
    offset /= factor;
}

template <typename T>
bool Cellwars::Line<T>::IsPerpendicular (const Line<T>& rhs) const
{
    logAssert (!IsDegenerate () && !rhs.IsDegenerate ());
    return norm.IsPerpendicular (rhs.norm);
}

template <typename T>
bool Cellwars::Line<T>::IsParallel (const Line<T>& rhs) const
{
    logAssert (!IsDegenerate () && !rhs.IsDegenerate ());
    return norm.IsParallel (rhs.norm);
}

template <typename T>
bool Cellwars::Line<T>::IsIntersecting (const Line<T>& rhs) const
{
    logAssert (!IsDegenerate () && !rhs.IsDegenerate ());
    return !IsParallel (rhs);
}

template <typename T>
Cellwars::Point2<T> Cellwars::Line<T>::Intersection (const Line<T>& rhs) const
{
    logAssert (!IsDegenerate () && !rhs.IsDegenerate ());

    Vec2<T> col_x (GetA (), rhs.GetA ());
    Vec2<T> col_y (GetB (), rhs.GetB ());
    Vec2<T> col_const (-GetC (), -rhs.GetC ());

    T det = Cross (col_x, col_y);
    logAssert (!IsEqual (det, (T)0));

    T cofactor_x = Cross (col_const, col_y);
    T cofactor_y = Cross (col_x, col_const);

    return Point2<T> (cofactor_x/ det, cofactor_y / det);
}

template <typename T>
bool Cellwars::IsPerpendicular (const Line<T>& lhs, const Line<T>& rhs)
{
    return lhs.IsPerpendicular (rhs);
}

template <typename T>
bool Cellwars::IsParallel (const Line<T>& lhs, const Line<T>& rhs)
{
    return lhs.IsParallel (rhs);
}

template <typename T>
bool Cellwars::IsIntersecting (const Line<T>& lhs, const Line<T>& rhs)
{
    return lhs.IsIntersecting (rhs);
}

template <typename T>
Cellwars::Point2<T> Cellwars::Intersection (const Line<T>& lhs, const Line<T>& rhs)
{
    return lhs.Intersection (rhs);
}
