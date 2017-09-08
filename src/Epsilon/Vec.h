#ifndef VEC_INCLUDED
#define VEC_INCLUDED

#include "Point.h"

namespace Cellwars
{
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

    template <typename T>
    struct Vec3 : public Vec2<T>
    {
    public:
        Vec3 () = default;
        Vec3 (const Vec2<T>& v, T z);
        Vec3 (T x, T y, T z);
        Vec3 (const Vec3& rhs) = default;
        Vec3& operator= (const Vec3& rhs) = default;

        const Vec3& operator+= (const Vec3& rhs);
        const Vec3& operator-= (const Vec3& rhs);

        const Vec3 operator+ (const Vec3& rhs) const;
        const Vec3 operator- (const Vec3& rhs) const;
        const Vec3 operator- () const;

        const Vec3& operator*= (T scalar);
        const Vec3& operator/= (T scalar);
        const Vec3 operator* (T scalar) const;
        const Vec3 operator/ (T scalar) const;

    public:
        T z;
    };

    template struct Vec3<int>;
    template struct Vec3<unsigned>;
    template struct Vec3<float>;
    template struct Vec3<double>;

    using IVec3 = Vec3<int>;
    using UVec3 = Vec3<unsigned>;
    using FVec3 = Vec3<float>;
    using DVec3 = Vec3<double>;
};

#include "Vec2.inl"
#include "Vec3.inl"

#endif /* VEC_INCLUDED */
