#ifndef LOGGER_INCLUDED
#define LOGGER_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************
 * DOXYGEN documentation
 ****************************************************************************/

/*! @file logger.h
 *  @brief Logging API
 *
 *  This file shall define the API needed for logging. No other methods will be
 *  used to report errors. Their interface will be akin to printf(3). Using this
 *  API will provide the following advantages:
 *
 *  - timestamps
 *  - type of error (severtity)
 *  - errno string output in case of high severity
 *  - there the error exactly occured (source file, function and line)
 *  - unified mothod for logging
 */

/*! @defgoup fun_macros Convenience macros
 *
 *  Knowing the exact place where the error occured can be handy. To do so, we
 *  need to use macros that call the main functions (which the user be oblivious to).
 *
 *  Note that it is up to your understanding how these functions differ from one
 *  another. @ref logCrit here is only unique in that it produces a core dump
 *  once invoked. Also, @ref logDebug will not be called if compiling with
 *  -DNDEBUG (i.e. if the macro NDEBUG was been defined).
 *
 *  {
 */
#ifndef NDEBUG
  #define logDebug(args...) _logDebug (__FILE__, __FUNCTION__, __LINE__, args)
  #define logDebugStr(x) _logDebugStr (__FILE__, __FUNCTION__, __LINE__, x)
#else
  #define logDebug
#endif
  #define logWarn(args...) _logWarn (__FILE__, __FUNCTION__, __LINE__, args)
  #define logError(args...) _logError (__FILE__, __FUNCTION__, __LINE__, args)
  #define logCrit(args...) _logCrit (__FILE__, __FUNCTION__, __LINE__, args)

  #define logWarnStr(x) _logWarnStr (__FILE__, __FUNCTION__, __LINE__, x)
  #define logErrorStr(x) _logErrorStr (__FILE__, __FUNCTION__, __LINE__, x)
  #define logCritStr(x) _logCritStr (__FILE__, __FUNCTION__, __LINE__, x)
/*! }
 */

/*! @brief Custom assert (using logging API)
 *
 *  @remark If NDEBUG is defined, this is a nop.
 *  #remark If assertion failed, a abort(3) will be called.
 */
#ifndef NDEBUG
  #define logAssert(x)                                              \
  do                                                                \
  {                                                                 \
    if (!(x))                                                       \
    {                                                               \
        logCrit_Impl (__FILE__, __PRETTY_FUNCTION__, __LINE__,      \
                "assertion failed: \'"  #x  "\'");                  \
    }                                                               \
  }                                                                 \
  while (0)
#else
  #define logAssert(x)
#endif

/*! @brief Defines the maximum lenght of a message
 *
 *  @remark Messages longer than the specified limit
 *  will be silently truncated.
 */
#define LOGGER_BUF_CAP         4096

/*! @defgroup functions External functions
 *
 * @sa @ref fun_macros
 *
 * {
 */
__attribute__((format(printf, 4, 5)))
extern void logDebug_Impl (const char* file, const char* fun, int line,
        const char* fmt, ...);

__attribute__((format(printf, 4, 5)))
extern void logWarn_Impl (const char* file, const char* fun, int line,
        const char* fmt, ...);

__attribute__((format(printf, 4, 5)))
extern void logError_Impl (const char* file, const char* fun, int line,
        const char* fmt, ...);

__attribute__((format(printf, 4, 5)))
extern void logCrit_Impl (const char* file, const char* fun, int line,
        const char* fmt, ...);

extern void logDebugStr_Impl (const char* file, const char* fun, int line,
        const char* fmt);

extern void logWarnStr_Impl (const char* file, const char* fun, int line,
        const char* fmt);

extern void logErrorStr_Impl (const char* file, const char* fun, int line,
        const char* fmt);

extern void logCritStr_Impl (const char* file, const char* fun, int line,
        const char* fmt);

/*! }
 */

/*! @brief Reopen logging file
 *
 *  Performes a freopen(3). It is part of the API for
 *  completeness. So you do not need to do a #include <stdio.h>.
 *
 *  @param path Path to logging file
 *  @return Void
 *
 *  @remark If this function is not called at all, logging will
 *  default to stdout.
 */

void logReopen (const char* path);

#ifdef __cplusplus
}
#endif

#endif /* LOGGER_INCLUDED */
