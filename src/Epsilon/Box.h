/*! @file Box.h
 *
 *  Defines a rectangular type.
 *  There can be many representations, so the struct Box defines member function
 *  to support such representations.
 */

#ifndef BOX_INCLUDED
#define BOX_INCLUDED

#include "Utility.h"
#include "Point.h"
#include "Line.h"

namespace Cellwars
{
    template <typename T>
    struct Box
    {
    public:
        using length_t = typename LengthType<T>::type;
        using coord_t = T;
        using point_t = Point2<coord_t>;
        using line_t = Line<coord_t>;

    public:
        Box () = default;
        Box (coord_t botleft_x, coord_t botleft_y, length_t width, length_t height);
        Box (const point_t& p, length_t width, length_t height);
        Box& operator= (const Box& rhs) = default;

        const length_t GetWidth () const;
        const length_t GetHeight () const;

        const point_t GetBotLeft () const;
        const point_t GetBotRight () const;
        const point_t GetTopLeft () const;
        const point_t GetTopRight () const;

        const line_t GetLeft () const;
        const line_t GetRight () const;
        const line_t GetBot () const;
        const line_t GetTop () const;

        const coord_t GetLowerY () const;
        const coord_t GetUpperY () const;
        const coord_t GetLowerX () const;
        const coord_t GetUpperX () const;

    public:
        Point2<coord_t> botleft;
        length_t width;
        length_t height;
    };

    template struct Box<int>;
    template struct Box<unsigned>;
    template struct Box<float>;
    template struct Box<double>;

    using IBox = Box<int>;
    using UBox = Box<unsigned>;
    using FBox = Box<float>;
    using DBox = Box<double>;
};

#endif /* BOX_INCLUDED */
