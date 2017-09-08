#ifndef LINE_INCLUDED
#define LINE_INCLUDED

#include "Vec.h"
#include "Point.h"

/*! @file Line.h
 *
 *  Declares a 2D line.
 *  A line can be represented width a line equation or a a pair of
 *  tanger/offset values. Both have advantages and disadvantages.
 *  So both representation are accessible.
 *
 *  Plus some functionality is also defined.
 */

namespace Cellwars
{
    template <typename T>
    class Line
    {
    public:
        Line () = default;
        explicit Line (T a, T b, T c);
        explicit Line (const Vec2<T>& norm, T offset);
        explicit Line (const Vec2<T>& dir, const Point2<T>& p);
        explicit Line (const Point2<T>& p1, const Point2<T>& p2);

        Line (const Line& rhs) = default;
        Line<T>& operator= (const Line<T>& rhs) = default;

        T GetA () const;
        T GetB () const;
        T GetC () const;

        Vec2<T> GetNorm () const;
        Vec2<T> GetDir () const;

        T Distance (const Point2<T>& p) const;
        T Distance2 (const Point2<T>& p) const;
        void Normalize ();

        bool IsPerpendicular (const Line<T>& rhs) const;
        bool IsParallel (const Line<T>& rhs) const;
        bool IsIntersecting (const Line<T>& rhs) const;

        Point2<T> Intersection (const Line<T>& rhs) const;

        bool IsDegenerate () const;

    private:
        Vec2<T> norm;
        T offset;
    };

    template <typename T>
    bool IsPerpendicular (const Line<T>& lhs, const Line<T>& rhs);

    template <typename T>
    bool IsParallel (const Line<T>& lhs, const Line<T>& rhs);

    template <typename T>
    bool IsIntersecting (const Line<T>& lhs, const Line<T>& rhs);

    template <typename T>
    Point2<T> Intersection (const Line<T>& lhs, const Line<T>& rhs);

    template class Line<int>;
    template class Line<unsigned>;
    template class Line<float>;
    template class Line<double>;

    using ILine = Line<int>;
    using ULine = Line<unsigned>;
    using FLine = Line<float>;
    using DLine = Line<double>;

};

#include "Line.inl"

#endif /* LINE_INCLUDED */
