#include <glad/glad.h>
#include <logger/logger.h>

#include "String.h"
#include "StringStream.h"
#include "FilePtr.h"

#include <stdexcept>

using Cellwars::String;
using Cellwars::StringSegment;
using Cellwars::StringStream;

#define QUOTE '\"'
#define DELIM " \n"
#define ASSIGNMENT '='


struct HieroDescr
{
    String name;
};

unsigned Parse (HieroDescr& descr, const StringSegment& str, unsigned pos)
{
    unsigned first = str.FindFirstNotOf (DELIM, pos);
    unsigned last = str.FindFirstOf (DELIM, first);
    descr.name = str.Substr (first, last - first);

    return last;
}

struct HieroOption
{
    String name;
    String value;
};

unsigned Parse (HieroOption& opt, const StringSegment& str, unsigned pos)
{
    unsigned first = str.FindFirstNotOf (DELIM, pos);
    unsigned last = str.FindFirstOf (ASSIGNMENT, first);
    opt.name = str.Substr (first, last - first);

    first = str.FindFirstNotOf (DELIM, last);
    if (str[first] == QUOTE)
    {
        ++first;
        last = str.FindFirstOf (QUOTE, first);
    }
    else
    {
        last = str.FindFirstOf (DELIM, first);
    }

    opt.value = str.Substr (first, last - first);
    if (!opt.name.Empty () && opt.value.Empty ())
    {
        StringStream ss;
        ss << "Hiero option parse failure: name is ";
        ss << opt.name << " but key is empty";

        throw std::runtime_error (ss.CStr ());
    }

    return last;
}

/* struct HieroRegister */
/* { */
/* }; */

struct HieroHeader
{
    String tex_name;
    unsigned tex_width;
    unsigned tex_height;
    GLenum tex_format;
    GLenum tex_type;
};

unsigned Parse (HieroHeader& hh, const StringSegment& str, unsigned n)
{
    HieroOption opt;
}
