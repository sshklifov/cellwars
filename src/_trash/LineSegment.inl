#include "Line.h"
#include "Utility.h"

template <typename T>
Cellwars::LineSegment<T>::LineSegment (const point_t& start, const point_t& end) : start (start), end (end)
{
    logAssert (!IsDegenerate ());
}

template <typename T>
Cellwars::LineSegment<T>::LineSegment (const Vec2<T>& v, const point_t& start) : start (start), end (v.Translate (start))
{
    logAssert (!IsDegenerate ());
}

template <typename T>
bool Cellwars::LineSegment<T>::IsDegenerate () const
{
    return IsEqual (start.x, end.x) && IsEqual (start.y, end.y);
}

template <typename T>
Cellwars::Vec2<T> Cellwars::LineSegment<T>::Direction () const
{
    return Direction (start, end);
}

template <typename T>
T Cellwars::LineSegment<T>::Distance2 (const Point2<T>& p) const
{
    Line<T> l1 = Line<T> (start, end);
    Line<T> l2 = Line<T> (Direction ().Normal (), p);

    if (Intersects (l1, l2))
    {
        Point2<T> intersect = Intersection (l1, l2);
        if (InsideClosedInterval (intersect.x, start.x, end.x))
            return Distance2 (p, intersect);
    }

    T dst2_p1 = Distance2 (p, start);
    T dst2_p2 = Distance2 (p, end);

    return dst2_p1 < dst2_p2 ? dst2_p1 : dst2_p2;
}

template <typename T>
bool Cellwars::Line<T>::IsIntersecting_Impl (const Line<T>& rhs, Point2<T>& p) const
{
    logAssert (!IsDegenerate () && !rhs.IsDegenerate ());

    if (IsParallel (l1.Direction (), l2.Direction ()))
    {
#ifndef NDEBUG
        // We know that l1 and l2 are not degenerate and l1 || l2
        
        // Let P(l1, l2) : There exists a line such that l1 and l2 lie on
        // Let Q(l1, l2) : The bounding boxes of l1 and l2 overlap

        // Our function should return false iff P(l1, l2) & Q(l1, l2)
        // Therefore, is should look like this: ~(P(l2, l2) && Q(l1, l2))

        bool P = IsParallel (Direction (start, rhs.start), Direction (start, rhs.end));
        bool Q = InsideClosedInterval (start.x, rhs.start.x, rhs.end.x) ||
            InsideClosedInterval (end.x, rhs.start.x, rhs.end.x);

        logAssert (!(P && Q));
#endif
        return false;
    }

    p = Intersection (Line<T> (*this), Line<T> (rhs));

    return InsideClosedInterval (p.x, start.x, end.x) &&
        InsideClosedInterval (p.x, rhs.start.x, rhs.end.x);
}

template <typename T>
bool Cellwars::Line<T>::IsIntersecting (const Line<T>& rhs) const
{
    Point2 nop;
    return IsIntersecting_Impl (rhs, nop);
}

template <typename T>
Cellwars::Point2<T> Cellwars::Line<T>::Intersection (const Line<T>& rhs) const
{
    Point2 res;

    bool is_intersecting = IsIntersecting_Impl (rhs, res);
    logAssert (is_intersecting);

    return res;
}

template <typename T>
T Cellwars::Distance2 (const LineSegment<T>& l, const Point2<T>& p)
{
    return l.Distance2 (p);
}

template <typename T>
T Cellwars::Distance (const LineSegment<T>& l, const Point2<T>& p)
{
    return l.Distance (p);
}

template <typename T>
bool IsIntersecting (const Line<T>& lhs, const Line<T>& rhs)
{
    return lhs.IsIntersecting (rhs);
}

template <typename T>
Cellwars::Point2<T> Cellwars::Intersection (const Line<T>& lhs, const Line<T>& rhs)
{
    return lhs.Intersection (rhs);
}
