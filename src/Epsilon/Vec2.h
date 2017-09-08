#ifndef VEC2_INCLUDED
#define VEC2_INCLUDED

/*! @file Vec2.h
 *
 *  Declares two dimentional vector type.
 *  As is the case with the class Point2, 2D vectors can be represented in
 *  a single meaningful way, so its member variable are public.
 *
 *  Since the whole purpose of the Epsilone library is to be used in scenarios
 *  where 2D calculations must be made, the Vec2 class declares some basic
 *  memeber functions as well. These can be used outside of the class as
 *  regular functions, for convenience.
 */

namespace Cellwars
{
    // Depedency cicle -- use forward declaration in both files
    template <typename T>
    struct Point2;

    template <typename T>
    struct Vec2
    {
    public:
        Vec2 () = default;
        Vec2 (T x, T y);
        Vec2 (const Vec2& rhs) = default;
        Vec2& operator= (const Vec2& rhs) = default;

        const Vec2& operator+= (const Vec2& rhs);
        const Vec2& operator-= (const Vec2& rhs);
        const Vec2 operator- () const;

        const Vec2& operator*= (T scalar);
        const Vec2& operator/= (T scalar);

        void Normalize ();
        bool IsDegenerate () const;

        Point2<T> Translate (const Point2<T>& p) const;
        T Dot (const Vec2<T>& rhs) const;
        T Distance () const;
        T Distance2 () const;
        T Cross (const Vec2<T>& rhs) const;

        bool IsPerpendicular (const Vec2<T>& rhs) const;
        bool IsParallel (const Vec2<T>& rhs) const;
        Vec2<T> Normal () const;

    public:
        T x;
        T y;
    };

    template <typename T>
    const Vec2<T> operator+ (const Vec2<T>& lhs, const Vec2<T>& rhs);

    template <typename T>
    const Vec2<T> operator- (const Vec2<T>& lhs, const Vec2<T>& rhs);

    template <typename T>
    const Vec2<T> operator* (const Vec2<T>& lhs, T scalar);

    template <typename T>
    const Vec2<T> operator/ (const Vec2<T>& lhs, T scalar);

    template <typename T>
    Point2<T> Translate (const Point2<T>& p, const Vec2<T>& v);

    template <typename T>
    T Dot (const Vec2<T>& p, const Vec2<T>& v);

    template <typename T>
    T Cross (const Vec2<T>& p, const Vec2<T>& v);

    template <typename T>
    bool IsPerpendicular (const Vec2<T>& lhs, const Vec2<T>& rhs);

    template <typename T>
    bool IsParallel (const Vec2<T>& lhs, const Vec2<T>& rhs);

    template struct Vec2<int>;
    template struct Vec2<unsigned>;
    template struct Vec2<float>;
    template struct Vec2<double>;

    using IVec2 = Vec2<int>;
    using UVec2 = Vec2<unsigned>;
    using FVec2 = Vec2<float>;
    using DVec2 = Vec2<double>;
};

#include "Vec2.inl"

#endif /* VEC2_INCLUDED */
