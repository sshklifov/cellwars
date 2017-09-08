#include "Utility.h"

float Cellwars::IntBitsToFloat (Cellwars::IntWithSize<sizeof (float)>::type x)
{
    return *((float*)(&x));
}

float Cellwars::UintBitsToFloat (Cellwars::UintWithSize<sizeof (float)>::type x)
{
    return *((float*)(&x));
}

double Cellwars::IntBitsToDouble (Cellwars::IntWithSize<sizeof (double)>::type x)
{
    return *((double*)(&x));
}

double Cellwars::UintBitsToDouble (Cellwars::UintWithSize<sizeof (double)>::type x)
{
    return *((double*)(&x));
}

typename Cellwars::IntWithSize<sizeof (float)>::type Cellwars::FloatBitsToInt (float x)
{
    return *((Cellwars::IntWithSize<sizeof (float)>::type*)(&x));
}

typename Cellwars::IntWithSize<sizeof (double)>::type Cellwars::DoubleBitsToInt (double x)
{
    return *((Cellwars::IntWithSize<sizeof (double)>::type*)(&x));
}

typename Cellwars::UintWithSize<sizeof (float)>::type Cellwars::FloatBitsToUint (float x)
{
    return *((Cellwars::UintWithSize<sizeof (float)>::type*)(&x));
}

typename Cellwars::UintWithSize<sizeof (double)>::type Cellwars::DoubleBitsToUint (double x)
{
    return *((Cellwars::UintWithSize<sizeof (double)>::type*)(&x));
}

template<>
bool Cellwars::IsEqual (float lhs, float rhs)
{
    return AlmostRelEq (lhs, rhs);
}

template<>
bool Cellwars::IsEqual (double lhs, double rhs)
{
    return AlmostRelEq (lhs, rhs);
}

template<>
bool Cellwars::IsLess (float lhs, float rhs)
{
    return lhs < rhs && !IsEqual (lhs, rhs);
}

template<>
bool Cellwars::IsLess (double lhs, double rhs)
{
    return lhs < rhs && !IsEqual (lhs, rhs);
}
