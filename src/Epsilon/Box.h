/*! @file Box.h
 *
 *  Defines a rectangular type. There can be many representations,
 *  so the struct Box defines member function to support such
 *  representations. It offers -- for flexibility, public member
 *  variables. This approach has both advantages and disadvantages.
 *
 *  This class cannot be expanded much in the future, so chosing to
 *  grant access to memeber variables is not a bad implementation
 *  decision.
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

        length_t GetWidth () const;
        length_t GetHeight () const;

        point_t GetBotLeft () const;
        point_t GetBotRight () const;
        point_t GetTopLeft () const;
        point_t GetTopRight () const;

        line_t GetLeft () const;
        line_t GetRight () const;
        line_t GetBot () const;
        line_t GetTop () const;

        coord_t GetLowerY () const;
        coord_t GetUpperY () const;
        coord_t GetLowerX () const;
        coord_t GetUpperX () const;

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
