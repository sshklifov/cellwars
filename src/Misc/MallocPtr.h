#ifndef MALLOCPTR_INCLUDED
#define MALLOCPTR_INCLUDED

#include "LocalPtr.h"
#include <cstdlib>

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
