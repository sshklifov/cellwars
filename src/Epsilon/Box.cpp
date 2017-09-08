#include "Box.h"

using Cellwars::Box;

template <typename T>
Box<T>::Box (coord_t botleft_x, coord_t botleft_y, length_t width, length_t height) :
    botleft (botleft_x, botleft_y),
    width (width),
    height (height)
{
}

template <typename T>
Box<T>::Box (const point_t& p, length_t width, length_t height) : Box (p.x, p.y, width, height)
{
}

template <typename T>
const typename Box<T>::length_t Box<T>::GetWidth () const
{
    return width;
}

template <typename T>
const typename Box<T>::length_t Box<T>::GetHeight () const
{
    return height;
}

template <typename T>
const typename Box<T>::point_t Box<T>::GetBotLeft () const
{
    return botleft;
}

template <typename T>
const typename Box<T>::point_t Box<T>::GetBotRight () const
{
    return point_t (botleft.x + width, botleft.y);
}

template <typename T>
const typename Box<T>::point_t Box<T>::GetTopLeft () const
{
    return point_t (botleft.x, botleft.y + height);
}

template <typename T>
const typename Box<T>::point_t Box<T>::GetTopRight () const
{
    return point_t (botleft.x + width, botleft.y + height);
}

template <typename T>
const typename Box<T>::line_t Box<T>::GetLeft () const
{
    return line_t (GetBotLeft (), GetTopLeft ());
}

template <typename T>
const typename Box<T>::line_t Box<T>::GetRight () const
{
    return line_t (GetBotRight (), GetTopRight ());
}

template <typename T>
const typename Box<T>::line_t Box<T>::GetBot () const
{
    return line_t (GetBotLeft (), GetBotRight ());
}

template <typename T>
const typename Box<T>::line_t Box<T>::GetTop () const
{
    return line_t (GetTopLeft (), GetTopRight ());
}

template <typename T>
const typename Box<T>::coord_t Box<T>::GetLowerY () const
{
    return botleft.y;
}

template <typename T>
const typename Box<T>::coord_t Box<T>::GetUpperY () const
{
    return botleft.y + height;
}

template <typename T>
const typename Box<T>::coord_t Box<T>::GetLowerX () const
{
    return botleft.x;
}

template <typename T>
const typename Box<T>::coord_t Box<T>::GetUpperX () const
{
    return botleft.x + width;
}
