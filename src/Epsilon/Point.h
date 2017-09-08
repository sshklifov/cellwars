#ifndef POINT_INCLUDED
#define POINT_INCLUDED

#include "Vec.h"

namespace Cellwars
{
    template <typename T>
    struct Vec2;

    template <typename T>
    struct Point2
    {
    public:
        Point2 () = default;
        Point2 (T x, T y);
        Point2 (const Point2&) = default;
        Point2& operator= (const Point2&) = default;

    public:
        T x;
        T y;
    };

    template <typename T>
    Vec2<T> Direction (const Point2<T> p1, const Point2<T> p2);

    template <typename T>
    T Distance2 (const Point2<T>& p1, const Point2<T>& p2);

    template <typename T>
    T Distance (const Point2<T>& p1, const Point2<T>& p2);

    template struct Point2<int>;
    template struct Point2<unsigned>;
    template struct Point2<float>;
    template struct Point2<double>;

    using IPoint2 = Point2<int>;
    using UPoint2 = Point2<unsigned>;
    using FPoint2 = Point2<float>;
    using DPoint2 = Point2<double>;
};

#include "Point.inl"

#endif /* POINT_INCLUDED */
