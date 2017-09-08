#include "logger.h"

#define GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <errno.h>
#include <string.h>

static void logErrcode (int errcode)
{
    const unsigned LOCALBUFSIZ = 256;
    char localbuf[LOCALBUFSIZ];

    printf ("[errcode = %s]:\n", strerror_r (errcode, localbuf, LOCALBUFSIZ));
}

static void logTime ()
{
    const unsigned LOCALBUFSIZ = 256;
    char localbuf[LOCALBUFSIZ];
    
    time_t now = time (NULL);
    if (now == (time_t)-1)
    {
        printf ("[time N/A]");
        return;
    }

    struct tm timeinfo;
    if (localtime_r (&now, &timeinfo) == NULL)
    {
        printf ("[time N/A]");
        return;
    }

    if (strftime (localbuf, LOCALBUFSIZ, "%H:%M:%S", &timeinfo) == 0)
    {
        printf ("[time N/A]");
        return;
    }

    printf ("[%s]", localbuf);
}

static void logLocation (const char* type, const char* file, const char* fun, int line)
{
    printf ("[%s]: %s/%s:%d\n", type, file, fun, line);
}

static void logStrHelper (const char* type, const char* file, const char* fun, int line, const char* str)
{
    int saved_errno = errno;

    logTime ();
    logLocation (type, file, fun, line);

    if (type[0] == 'w' || type[0] == 'e' || type[0] == 'c')
    {
        logErrcode (saved_errno);
    }

    printf ("%s\n\n", str);
}

void _logDebugStr (const char* file, const char* fun, int line, const char* str)
{
    logStrHelper ("debug", file, fun, line, str);
}

void _logDebug (const char* file, const char* fun, int line, const char* fmt, ...)
{
    va_list args;
    char buf[LOGGER_BUF_CAP];

    va_start (args, fmt);
    vsnprintf (buf, LOGGER_BUF_CAP, fmt, args);
    va_end (args);

    _logDebugStr (file, fun, line, buf);
}

void _logWarnStr (const char* file, const char* fun, int line, const char* str)
{
    logStrHelper ("warning", file, fun, line, str);
}

void _logWarn (const char* file, const char* fun, int line, const char* fmt, ...)
{
    va_list args;
    char buf[LOGGER_BUF_CAP];

    va_start (args, fmt);
    vsnprintf (buf, LOGGER_BUF_CAP, fmt, args);
    va_end (args);

    _logWarnStr (file, fun, line, buf);
}

void _logErrorStr (const char* file, const char* fun, int line, const char* str)
{
    logStrHelper ("error", file, fun, line, str);
}

void _logError (const char* file, const char* fun, int line, const char* fmt, ...)
{
    va_list args;
    char buf[LOGGER_BUF_CAP];

    va_start (args, fmt);
    vsnprintf (buf, LOGGER_BUF_CAP, fmt, args);
    va_end (args);

    _logErrorStr (file, fun, line, buf);
}

void _logCritStr (const char* file, const char* fun, int line, const char* str)
{
    logStrHelper ("critical", file, fun, line, str);
    abort ();
}

void _logCrit (const char* file, const char* fun, int line, const char* fmt, ...)
{
    va_list args;
    char buf[LOGGER_BUF_CAP];

    va_start (args, fmt);
    vsnprintf (buf, LOGGER_BUF_CAP, fmt, args);
    va_end (args);

    _logCritStr (file, fun, line, buf);
}

void logReopen (const char* path)
{
    stdout = freopen (path, "a", stdout);
    if (stdout == NULL)
    {
        abort ();
    }
}
