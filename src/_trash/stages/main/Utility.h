// TODO: Support for long double

#ifndef _UTILITY_H
#define _UTILITY_H

#include "Types.h"

#include <type_traits>
#include <cmath>

namespace Cellwars
{
    template <typename T>
    auto IntBitsToFloat (T x)
    {
        static_assert (std::is_integral<T>::value, "Expected integer type");
        static_assert (sizeof (T) == 4 || sizeof (T) == 8, "Expect 4 or 8 byte integer");

        using retval = typename IntegerWithSize<sizeof (T)>::type;

        return *((retval*)(&x));
    }

    template <typename T>
    auto FloatBitsToInt (T x)
    {
        static_assert (std::is_floating_point<T>::value, "Expected floating point type");
        static_assert (sizeof (T) == 4 || sizeof (T) == 8, "Expected 4 or 8 byte type");

        using retval = typename IntegerWithSize<sizeof (T)>::type;

        return *((retval*)(&x));
    }

    template <typename T, bool is_integral = std::is_integral<T>::value>
    struct _IsNegative;

    template <typename T>
    struct _IsNegative<T, true>
    {
        static bool call (T x)
        {
            return x >> (sizeof (T) - 1);
        }
    };

    template <typename T>
    struct _IsNegative<T, false>
    {
        static bool call (T x)
        {
            return FloatingType<T>(x).Sign ();
        }
    };

    template <typename T>
    bool IsNegative (T x)
    {
        static_assert (std::is_signed<T>::value, "Expected signed arithmetic type");

        return _IsNegative<T>::call (x);
    }

    template <typename T>
    struct _Cast
    {
        static_assert (std::is_arithmetic<T>::value, "not arithmetic type");

        using type = typename std::conditional<std::is_floating_point<T>::value, FloatingType<T>, T>::type;
    };

    template <typename T>
    bool IsLess (T lhs, T rhs)
    {
        using cast_type = typename _Cast<T>::type;

        return (cast_type)lhs < (cast_type)rhs;
    };

    template <typename T>
    bool IsGreater (T lhs, T rhs)
    {
        using cast_type = typename _Cast<T>::type;

        return (cast_type)lhs > (cast_type)rhs;
    };

    template <typename T>
    bool IsEqual (T lhs, T rhs)
    {
        using cast_type = typename _Cast<T>::type;

        return (cast_type)lhs == (cast_type)rhs;
    };

    template <typename T>
    bool IsNotEqual (T lhs, T rhs)
    {
        using cast_type = typename _Cast<T>::type;

        return (cast_type)lhs != (cast_type)rhs;
    };

    template <typename T>
    bool IsLessEqual (T lhs, T rhs)
    {
        using cast_type = typename _Cast<T>::type;

        return (cast_type)lhs <= (cast_type)rhs;
    };

    template <typename T>
    bool IsGreaterEqual (T lhs, T rhs)
    {
        using cast_type = typename _Cast<T>::type;

        return (cast_type)lhs >= (cast_type)rhs;
    };

    template <typename T>
    T Min (T a, T b)
    {
        IsLess (a, b) ? a : b;
    }

    template <typename T>
    T Max (T a, T b)
    {
        IsGreater (a, b) ? a : b;
    }

    template <typename T>
    T Abs (T x)
    {
        return abs (x);
    }

    template <typename T>
    T Sqrt (T x)
    {
        return sqrt (x);
    }
};

#endif /* _UTILITY_H */
