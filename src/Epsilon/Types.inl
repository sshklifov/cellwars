#include "Types.h"

#include <type_traits>

template <>
struct Cellwars::IntWithSize<1>
{
    using type = char;
};
template <>
struct Cellwars::IntWithSize<2>
{
    using type = short;
};
template <>
struct Cellwars::IntWithSize<4>
{
    using type = int;
};
template <>
struct Cellwars::IntWithSize<8>
{
    using type = long long;
};

template <size_t size>
struct Cellwars::UintWithSize
{
    using type = typename std::make_unsigned<typename IntWithSize<size>::type>::type;
};

template <typename T, bool is_floating_point = std::is_floating_point<T>::value>
struct _LengthTypeImpl;

template <typename T>
struct _LengthTypeImpl<T, false>
{
    using type = typename std::make_unsigned<T>::type;
};

template <typename T>
struct _LengthTypeImpl<T, true>
{
    using type = T;
};

template <typename T>
struct Cellwars::LengthType
{
    using type = typename _LengthTypeImpl<T>::type;
};
