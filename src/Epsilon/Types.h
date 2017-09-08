/*! @file Types.h
 *
 *  Defines some useful types, which are used internally.
 *  This means that it should not be included standalone.
 */

#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

#include <cstddef>

namespace Cellwars
{
    /*! @brief Integer type with specific size (via template)
     *
     *  Supported sizes are 1, 2, 4, and 8 bytes.
     *
     *  @remark Types are according to the x86 instruction set.
     */

    template <size_t size>
    struct IntWithSize;

    /*! @brief Unsigned interger type with specific size (via template)
     *
     *  Same as @ref IntWithSize but unsigned
     *
     *  @sa IntWithSize
     */

    template <size_t size>
    struct UintWithSize;

    /*! @brief returns type to appropriately represent length.
     *
     *  Since the library is heavily templated, sometimes a type must
     *  be deduced given another. A good example is the Box class. So,
     *  if we supply [T = int] to class Box, then the lower left corner
     *  could be in any 4 quadrants. But its size should always positive.
     *  So, given [T = int], the deduced type for width and height should
     *  be unsigned. However, if T were a float, then it should remain
     *  float, as floating types are always signed and it wouldn't
     *  make sense to use UintWithSize<sizeof (float)>, as neither
     *  width nor height can be fractions.
     */

    template <typename T>
    struct LengthType;
};

#include "Types.inl"

#endif /* TYPES_INCLUDED */
