#ifndef CIRCLE_INCLUDED
#define CIRCLE_INCLUDED

#include "Types.h"
#include "Point.h"

/*! @file Circle.h
 *
 *  Declares a 2D circle type.
 *  Mainly used as a container. Currently, it does not provide any functionality. Of course,
 *  this is subject to change.
 */

namespace Cellwars
{
    template <typename T>
    struct Circle
    {
    public:
        using length_t = typename LengthType<T>::type;
        using point_t = Point2<T>;

    public:
        Circle () = default;
        Circle (T x, T y, length_t rad);
        Circle (const point_t& center, length_t rad);

        Circle (const Circle<T>& rhs) = default;
        Circle& operator= (const Circle& rhs) = default;

        bool IsDegenerate () const;

    public:
        point_t center;
        length_t rad;
    };

    template struct Circle<float>;
    template struct Circle<double>;

    using FCircle = Circle<float>;
    using DCircle = Circle<double>;
};

#include "Circle.inl"

#endif /* CIRCLE_INCLUDED */
