#include "StringStream.h"
#include <logger/logger.h>

#include <utility>
#include <cstdio>
#include <cerrno>

template <typename... Args>
int Cellwars::InputStringStream::ScanFmt (const char* fmt, Args... args)
{
    if (!Good ()) return 0;

    String new_fmt (fmt);
    new_fmt += "%n";

    int pos = -1;
    int retval = ScanFmt_Impl (new_fmt.CStr (), args..., &pos);

    if (retval == EOF || ((unsigned)retval != sizeof... (args)))
    {
        SetStates (errno == EILSEQ ? StringStreamState::PARTIAL_WR | StringStreamState::ENCODING_ERR : StringStreamState::PARTIAL_WR);
        return 0;
    }

    offset += pos;
    return retval;
}

template <typename... Args>
int Cellwars::InputStringStream::ScanFmt_Impl (const char* fmt, Args... args)
{
    return sscanf (p.GetCPtr () + offset, fmt, args...);
}

template <typename... Args>
int Cellwars::OutputStringStream::PrintFmt (const char* fmt, Args... args)
{
    if (!Good ()) return 0;

    constexpr unsigned DEFAULT_SIZE = 128;

    unsigned try_resize = DEFAULT_SIZE;
    unsigned original_size = str.Size ();
    int num_read;

    while (str.Size () != str.MaxSize ())
    {
        str.RelativeResize (try_resize);

        char* buf = str.Str () + original_size;
        unsigned buf_size = str.Size () - original_size;
        num_read = snprintf (buf, buf_size, fmt, args...);

        if (num_read < 0)
        {
            SetStates (StringStreamState::ENCODING_ERR);
            num_read = 0;
            break;
        }
        if ((unsigned)num_read < buf_size)
        {
            break;
        }

        int suggested_resize = num_read - buf_size;
        try_resize = Max ((int)DEFAULT_SIZE, suggested_resize);
    }

    str.Resize (original_size + num_read);
    return num_read;
}
