#include "Point.h"

template <typename T>
Cellwars::Point2<T>::Point2 (T x, T y) : x (x), y (y)
{
}

template <typename T>
Cellwars::Vec2<T> Cellwars::Direction (const Point2<T> p1, const Point2<T> p2)
{
    return Vec2<T> (p2.x - p1.x, p2.y - p1.y);
}

template <typename T>
T Cellwars::Distance2 (const Point2<T>& p1, const Point2<T>& p2)
{
    return Direction (p1, p2).Distance2 ();
}
template <typename T>
T Cellwars::Distance (const Point2<T>& p1, const Point2<T>& p2)
{
    return Direction (p1, p2).Distance ();
}
