#ifndef VEC3_INCLUDED
#define VEC3_INCLUDED

#include "Vec2.h"

/*! @file Vec3.h
 *
 *  Declares three dimentional vector type.
 *  As is the case with the class Vec2, 3D vectors can be represented in
 *  a single meaningful way, so its member variable are public.
 *
 *  The Vec3 class is solely used as a container, as 3D related maths is
 *  outside the scope of this library.
 */

namespace Cellwars
{
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

#include "Vec3.inl"

#endif /* VEC3_INCLUDED */
