#include "HieroEvents.h"
#include "Events.h"

#include <Container/StringStream.h>
#include <stdexcept>

using Cellwars::OutputStringStream;
using Cellwars::InputStringStream;
using Cellwars::String;

constexpr char OPTION_INFIX = '=';
constexpr char STRING_OPEN_SYMBOL = '\"';
constexpr char STRING_CLOSE_SYMBOL = '\"';
constexpr const char DELIM[] = {' ', '\n', EOF, OPTION_INFIX, '\0'}; // '\0' is not a delim

void Cellwars::ThrowIfUnregisteredOption (const HieroOption& e)
{
    OutputStringStream ss;
    ss << "Could not register event: name=" << e.name;
    ss << " value=" << e.value;

    throw std::runtime_error (ss.CStr ());
}

static unsigned ParseLabel (String& res, const String& str, unsigned pos)
{
    unsigned first = str.FindFirstNotOf (DELIM, pos);
    if (first == String::Npos)
    {
        res.Clear ();
        return pos;
    }

    unsigned last;
    if (str[first] == STRING_OPEN_SYMBOL)
    {
        ++first;

        last = str.FindFirstOf (STRING_CLOSE_SYMBOL, first);
        if (last == String::Npos)
        {
            OutputStringStream ss;
            ss << "Invalid syntax: unterminated string label (" << STRING_OPEN_SYMBOL << STRING_CLOSE_SYMBOL << "): ";
            ss << str.Substr (first - 1);

            throw std::runtime_error (ss.CStr ());
        }
        pos = last + 1;
    }
    else
    {
        last = str.FindFirstOf (DELIM, first);
        if (last == String::Npos) last = str.Size ();
        pos = last;
    }

    res = str.Substr (first, last - first);
    return pos;
}

unsigned Cellwars::ParseSectionName (String& res, const String& str, unsigned pos)
{
    return ParseLabel (res, str, pos);
}

unsigned Cellwars::ParseOption (HieroOption& opt, const String& str, unsigned pos)
{
    pos = ParseLabel (opt.name, str, pos);
    if (opt.name.Empty ())
    {
        opt.value.Clear ();
        return pos;
    }

    pos = str.FindFirstOf (OPTION_INFIX, pos);
    if (pos == String::Npos)
    {
        OutputStringStream ss;
        ss << "Invalid syntax: unmached key-value pair in: " << str;

        throw std::runtime_error (ss.CStr ());
    }

    try
    {
        pos = ParseLabel (opt.value, str, pos + 1);
    }
    catch (std::exception& e)
    {
        OutputStringStream ss;
        ss << "Failed to parse value label for key with name=" << opt.name;
        ss << ": " << e.what ();

        throw std::runtime_error (ss.CStr ());
    }

    return pos;
}

/* static unsigned ParseOptionName (String& res, const String& str, unsigned pos = 0) */
/* { */
/*     unsigned first = str.FindFirstNotOf (DELIM, pos); */
/*     if (first == String::Npos) */
/*     { */
/*         res.Clear (); */
/*         return pos; */
/*     } */

/*     unsigned last = str.FindFirstOf (OPTION_INFIX, first); */
/*     if (last == String::Npos) */
/*     { */
/*         OutputStringStream ss; */
/*         ss << "Invalid syntax: cannot find infix option string (" << OPTION_INFIX << ") "; */
/*         ss << "for " << str.Substr (first); */

/*         throw std::runtime_error (ss.CStr ()); */
/*     } */

/*     /1* last = str.FindLastNotOf (DELIM, last - 1); *1/ */

/*     res = str.Substr (first, last - first); */
/*     return last; */
/* } */

/* static unsigned ParseOptionValue (String& res, const String& str, unsigned pos = 0) */
/* { */
/*     unsigned first = str.FindFirstNotOf (DELIM, pos); */
/*     if (first == String::Npos) */
/*     { */
/*         OutputStringStream ss; */
/*         ss << "Invalid syntax: cannot parse value for option from " << str; */

/*         throw std::runtime_error (ss.CStr ()); */
/*     } */

/*     unsigned last; */
/*     if (str[first] == VALUE_OPENING_SYMBOL) */
/*     { */
/*         ++first; */
/*         last = str.FindFirstOf (VALUE_CLOSING_SYMBOL, first); */

/*         if (last == String::Npos) */
/*         { */
/*             OutputStringStream ss; */
/*             ss << "Invalid syntax: unterminated value (" << VALUE_OPENING_SYMBOL << VALUE_CLOSING_SYMBOL << ") for option: "; */
/*             ss << str.Substr (first - 1); */

/*             throw std::runtime_error (ss.CStr ()); */
/*         } */
/*     } */
/*     else */
/*     { */
/*         last = str.FindFirstOf (DELIM, first); */
/*         if (last == String::Npos) last = str.Size (); */
/*         /1* { *1/ */
/*         /1*     OutputStringStream ss; *1/ */
/*         /1*     ss << "Invalid syntax: option value is not terminated: " << str.Substr (first); *1/ */

/*         /1*     throw std::runtime_error (ss.CStr ()); *1/ */
/*         /1* } *1/ */
/*     } */

/*     res = str.Substr (first, last - first); */
/*     return last; */
/* } */

/* unsigned Cellwars::ParseOption (HieroOption& res, const String& str, unsigned pos) */
/* { */
/*     pos = ParseOptionName (res.name, str, pos); */
/*     if (res.name.Empty ()) */
/*     { */
/*         res.value.Clear (); */
/*         return pos; */
/*     } */

/*     try */
/*     { */
/*         pos = str.FindFirstNotOf (OPTION_INFIX, pos); */
/*         pos = ParseOptionValue (res.value, str, pos); */
/*     } */
/*     catch (std::exception& e) */
/*     { */
/*         OutputStringStream ss; */
/*         ss << "Error while parsing option with name=" << res.name; */
/*         ss << ": " << e.what (); */

/*         throw std::runtime_error (ss.CStr ()); */
/*     } */

/*     return pos; */
/* } */
