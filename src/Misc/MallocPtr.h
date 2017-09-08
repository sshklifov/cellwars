#ifndef MALLOCPTR_INCLUDED
#define MALLOCPTR_INCLUDED

#include "LocalPtr.h"
#include <cstdlib>

/*! @file MallocPtr.h
 *
 *  Convenience class, stores pointers returned from malloc.
 *  Performs a tempalte substitution of the LocalPtr class. Can be used
 *  to store malloc pointers and automatically call free on them.
 *
 *  @remark This file is already included in LocalPtr.h
 */

namespace Cellwars
{
    struct MallocPtrDeleter
    {
        void operator() (void* ptr)
        {
            free (ptr);
        }
    };

    template <typename T>
    using MallocPtr = LocalPtr<T, MallocPtrDeleter>;
};

#endif /* MALLOC_PTR_INCLUDED */
