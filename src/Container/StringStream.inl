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
    int retval = ScanFmtWrap (new_fmt.CStr (), args..., &pos);

    if (retval == EOF)
    {
        SetStates (StringStreamState::BAD);
    }
    else if ((unsigned)retval != sizeof... (args))
    {
        SetStates (StringStreamState::FAIL);
    }

    offset += pos;
    return retval;
}

template <typename... Args>
int Cellwars::InputStringStream::ScanFmtWrap (const char* fmt, Args... args)
{
    return sscanf (&str[offset], fmt, args...);
}

template <typename... Args>
int Cellwars::OutputStringStream::PrintFmt (const char* fmt, Args... args)
{
    if (!Good ()) return 0;

    constexpr unsigned DEFAULT_RESIZE_AMOUNT = 128;
    int num_written = TryPrintFmt (DEFAULT_RESIZE_AMOUNT, fmt, args...);

    bool try_again = num_written >= (int)DEFAULT_RESIZE_AMOUNT;
    if (try_again)
    {
        int sufficiently_large = num_written + 1;
        num_written = TryPrintFmt (sufficiently_large, fmt, args...);
        logAssert (num_written > 0 && num_written < sufficiently_large);
    }

    return num_written;

}

template <typename... Args>
int Cellwars::OutputStringStream::TryPrintFmt (unsigned resize_amount, const char* fmt, Args... args)
{
    unsigned old_size = str.Size ();
    str.RelativeResize (resize_amount);

    int num_written = snprintf (&str[old_size], resize_amount, fmt, args...);

    bool failed = num_written < 0 || ((unsigned)num_written >= resize_amount);
    if (failed)
    {
        if (num_written < 0)
        {
            SetStates (StringStreamState::FAIL);
        }
        str.Resize (old_size);
    }
    else
    {
        str.Resize (old_size + num_written);
    }

    return num_written;
}
