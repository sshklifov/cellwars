#ifndef SOURCE_FILE_INCLUDED
#define SOURCE_FILE_INCLUDED

#include <Misc/LocalPtr.h>

/*! @file SourceFile.h
 *
 *  Read the contents of a file.
 *  In some cases a file must be read entirely. This file declares a function
 *  for doing so. It should be noted that functionality should be used only
 *  when necessary. A certain file may be too large and allocation will fail.
 *  Also reading a segment of a file and then parsing may be advantageous
 *  instread of reading the whole file first and then parsing. Do not include
 *  this file as a default when dealing with files.
 *
 */

namespace Cellwars
{
    NewPtr<char> SourceFile (const char* path);
};

#endif /* SOURCE_FILE_INCLUDED */
