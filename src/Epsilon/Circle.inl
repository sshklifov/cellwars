#include "Circle.h"
#include "Utility.h"

template <typename T>
Cellwars::Circle<T>::Circle (T x, T y, length_t rad) : center (x, y), rad (rad)
{
}

template <typename T>
Cellwars::Circle<T>::Circle (const point_t& center, length_t rad) : center (center), rad (rad)
{
}

template <typename T>
bool Cellwars::Circle<T>::IsDegenerate () const
{
    return IsEqual (rad, (T)0);
}
