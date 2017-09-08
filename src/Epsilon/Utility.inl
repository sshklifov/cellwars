#include "Utility.h"

#include <cmath>
#include <limits>
#include <type_traits>

template <typename T>
bool Cellwars::AlmostRelEq (T x, T y)
{
    static_assert (std::is_floating_point<T>::value, "Expected a floating point type");

    constexpr T epsilon = std::numeric_limits<T>::epsilon ();

    T delta = fabs (x - y);
    x = fabs (x);
    y = fabs (y);

    T bigger = x > y ? x : y;

    return delta <= bigger * epsilon;
}

template <typename T>
bool Cellwars::IsNegative (T x)
{
    return x < (T)0;
}


template <typename T>
bool Cellwars::IsEqual (T lhs, T rhs)
{
    return lhs == rhs;
}

template <typename T>
bool Cellwars::IsLess (T lhs, T rhs)
{
    return lhs < rhs;
}

template <typename T>
bool Cellwars::IsGreater (T lhs, T rhs)
{
    return IsLess (rhs, lhs);
}

template <typename T>
bool Cellwars::IsLessEqual (T lhs, T rhs)
{
    return !IsGreater (lhs, rhs);
}

template <typename T>
bool Cellwars::IsGreaterEqual (T lhs, T rhs)
{
    return !IsLess (lhs, rhs);
}

template <typename T>
bool Cellwars::IsNotEqual (T lhs, T rhs)
{
    return !IsEqual (lhs, rhs);
}

template <typename T>
bool Cellwars::InsideOpenInterval (T x, T a, T b)
{
    return IsGreater (x, a) && IsLess (x, b);
}

template <typename T>
bool Cellwars::InsideClosedInterval (T x, T a, T b)
{
    return IsGreaterEqual (x, a) && IsLessEqual (x, b);
}
