#ifndef FILEPTR_INCLUDED
#define FILEPTR_INCLUDED

#include "LocalPtr.h"
#include <cstdio>

/*! @file FilePtr.h
 *
 *  Convenience class, stores FILE pointer.
 *  Performs a tempalte substitution of the LocalPtr class. Can be used
 *  to store FILE pointers and automatically call fclose.
 *
 *  @remark This file is already included in LocalPtr.h
 */

namespace Cellwars
{
    struct FilePtrDeleter
    {
        void operator() (FILE* ptr)
        {
            fclose (ptr);
        }
    };

    using FilePtr = LocalPtr<FILE, FilePtrDeleter>;
};

#endif /* FILE_PTR_INCLUDED */
