#ifndef FILEPTR_INCLUDED
#define FILEPTR_INCLUDED

#include "LocalPtr.h"
#include <cstdio>

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
