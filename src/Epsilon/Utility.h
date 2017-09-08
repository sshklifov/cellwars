/*! @file Utility.h
 *
 *  Here, every functionality that does not operate on vectors,
 *  points, circles, etc. is defined. It is like a helper library
 *  for the epsilon one. It should not be included standalone.
 *  
 */

#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include "Types.h"

namespace Cellwars
{
    /*! @brief Cast float bits to int with equivalent size.
     *
     *  @param x The float.
     *  @return Integer with the same bit representation as @ref x.
     */

    float IntBitsToFloat (IntWithSize<sizeof (float)>::type x);
    float IntBitsToFloat (UintWithSize<sizeof (float)>::type x);
    double IntBitsToDouble (IntWithSize<sizeof (double)>::type x);
    double IntBitsToDouble (UintWithSize<sizeof (double)>::type x);

    /*! @brief Cast int bits to float with equivalent size.
     *
     *  @param x The integer.
     *  @return Floating point with the same bit representation as @ref x.
     */

    typename IntWithSize<sizeof (float)>::type FloatBitsToInt (float x);
    typename IntWithSize<sizeof (double)>::type FloatBitsToInt (double x);
    typename UintWithSize<sizeof (float)>::type FloatBitsToUInt (float x);
    typename UintWithSize<sizeof (double)>::type FloatBitsToUInt (double x);

    /*! @brief Internal function for comparing floats.
     *
     *  @remark Should not be called.
     */
    template <typename T>
    bool AlmostRelEq (T x, T y);

    /*! @brief Check if value is negative.
     *
     *  @param x The value.
     *  @return True/false when value is negative/nonnegative.
     *
     *  @remark Since 0.0 is represented without precision loss in IEEE 754, doing a
     *  x < 0 check for all arithmetic types should always yield a correct result.
     */

    template <typename T>
    bool IsNegative (T x);

    /*! @brief Similar to lhs == rhs.
     *
     *  @param lhs Left hand side
     *  @param rhs Right hand side
     *  @return lhs == rhs.
     *
     *  @remark Useful when comparing floats. Has compatibility with other arithmetic types.
     */

    template <typename T>
    bool IsEqual (T lhs, T rhs);

    /*! @brief Similar to lhs < rhs.
     *
     *  @param lhs Left hand side
     *  @param rhs Right hand side
     *  @return lhs < rhs.
     *
     *  @remark Useful when comparing floats. Has compatibility with other arithmetic types.
     */

    template <typename T>
    bool IsLess (T lhs, T rhs);

    /*! @brief Similar to lhs > rhs.
     *
     *  @param lhs Left hand side
     *  @param rhs Right hand side
     *  @return lhs > rhs.
     *
     *  @remark Useful when comparing floats. Has compatibility with other arithmetic types.
     */

    template <typename T>
    bool IsGreater (T lhs, T rhs);

    /*! @brief Similar to lhs <= rhs.
     *
     *  @param lhs Left hand side
     *  @param rhs Right hand side
     *  @return lhs <= rhs.
     *
     *  @remark Useful when comparing floats. Has compatibility with other arithmetic types.
     */

    template <typename T>
    bool IsLessEqual (T lhs, T rhs);

    /*! @brief Similar to lhs >= rhs.
     *
     *  @param lhs Left hand side
     *  @param rhs Right hand side
     *  @return lhs >= rhs.
     *
     *  @remark Useful when comparing floats. Has compatibility with other arithmetic types.
     */

    template <typename T>
    bool IsGreaterEqual (T lhs, T rhs);

    /*! @brief Similar to lhs != rhs.
     *
     *  @param lhs Left hand side
     *  @param rhs Right hand side
     *  @return lhs != rhs.
     *
     *  @remark Useful when comparing floats. Has compatibility with other arithmetic types.
     */

    template <typename T>
    bool IsNotEqual (T lhs, T rhs);

    /*! @brief Checks if x belongs to (a, b).
     *
     * @param x The value.
     * @param a Start of interval.
     * @param b End of interval.
     * @return True iif x belongs to (a, b).
     */

    template <typename T>
    bool InsideOpenInterval (T x, T a, T b);

    /*! @brief Checks if x belongs to [a, b].
     *
     * @param x The value.
     * @param a Start of interval.
     * @param b End of interval.
     * @return True iif x belongs to [a, b].
     */

    template <typename T>
    bool InsideClosedInterval (T x, T a, T b);
};

#include "Utility.inl"

#endif /* UTILITY_INCLUDED */
