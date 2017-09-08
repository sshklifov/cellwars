#ifndef NEWPTR_INCLUDED
#define NEWPTR_INCLUDED

#include "LocalPtr.h"

/*! @file NewPtr.h
 *
 *  Convenience class, stores pointers returned from calls to new.
 *  Performs a tempalte substitution of the LocalPtr class. Can be used
 *  to store new pointers and automatically call delete on them.
 *
 *  @remark This file is already included in LocalPtr.h
 */

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
