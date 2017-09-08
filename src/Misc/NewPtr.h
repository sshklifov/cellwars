#ifndef NEWPTR_INCLUDED
#define NEWPTR_INCLUDED

#include "LocalPtr.h"

namespace Cellwars
{
    struct NewPtrDeleter
    {
        template <typename T>
        void operator() (T* ptr)
        {
            delete ptr;
        }
    };

    template <typename T>
    using NewPtr = LocalPtr<T, NewPtrDeleter>;
};

#endif /* NEWPTR_INCLUDED */
