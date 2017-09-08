#ifndef BYTE_INCLUDED
#define BYTE_INCLUDED

/*! @file Byte.h
 *  Declaration of byte_t.
 *  Many programmes require the use of a type to store exactly a single byte.
 *  Using directly unsigned char is not a good idea, as it does not portray
 *  that exact need. Declaring typedefs in every file is also bad. This file,
 *  albeit simple, solves this issue.
 */

namespace Cellwars
{
    using byte_t = unsigned char;
};


#endif /* BYTE_INCLUDED */
