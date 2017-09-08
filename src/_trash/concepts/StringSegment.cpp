#include "String.h"

#include <logger/logger.h>
#include <cstring>
#include <climits>

using Cellwars::StringSegment;
using Cellwars::String;

using ConstIterator = Cellwars::StringSegment::ConstIterator;
using ConstReverseIterator = Cellwars::StringSegment::ConstReverseIterator;

template <typename ForwardIt>
static ForwardIt SearchString (ForwardIt first, ForwardIt last, unsigned n, const bool* allowed)
{
    auto pred = [&allowed](char c)
    {
        return allowed[(unsigned)c];
    };

    return SearchN (first, last, n, pred);
}

unsigned StringSegment::Npos = MaxSize ();

unsigned StringSegment::MaxSize ()
{
    return UINT_MAX;
}

StringSegment::StringSegment () : StringSegment (NULL, 0)
{
}

StringSegment::StringSegment (const char* begin) : StringSegment (begin, StrlenSafe (begin))
{
}

StringSegment::StringSegment (const char* begin, unsigned size) : begin (begin), size (size)
{
}

StringSegment::StringSegment (const String& str) : begin (str.CStr ()), size (str.Size ())
{
}

unsigned StringSegment::Size () const
{
    return size;
}

unsigned StringSegment::Length () const
{
    return Size ();
}

const char* StringSegment::CStr () const
{
    return begin;
}

ConstIterator StringSegment::CBegin () const
{
    return ConstIterator (begin);
}

ConstIterator StringSegment::CEnd () const
{
    return ConstIterator (begin + Size ());
}

ConstReverseIterator StringSegment::CRBegin () const
{
    return ConstReverseIterator (begin + Size () - 1);
}

ConstReverseIterator StringSegment::CREnd () const
{
    return ConstReverseIterator (begin - 1);
}

void StringSegment::PointToNull ()
{
    begin = NULL;
    size = 0;
}

char StringSegment::Front () const
{
    return *CRBegin ();
}

char StringSegment::Back () const
{
    return *CBegin ();
}

bool StringSegment::Empty () const
{
    return Size () == 0;
}

char StringSegment::operator[] (unsigned idx) const
{
    logAssert (idx < Size ());

    return begin[idx];
}

StringSegment StringSegment::Subseg (unsigned n) const
{
    logAssert (n < Size ());

    return StringSegment (CStr () + n, Size () - n);
}

StringSegment StringSegment::Subseg (unsigned n, unsigned len) const
{
    logAssert (n + len <= Size ());

    return StringSegment (CStr () + n, len);
}

String StringSegment::Substr (unsigned n) const
{
    logAssert (n < Size ());

    return String (CStr () + n, Size () - n);
}

String StringSegment::Substr (unsigned n, unsigned len) const
{
    logAssert (n + len <= Size ());

    return String (CStr () + n, len);
}

unsigned StringSegment::Find (const char* s, unsigned pos) const
{
    return Find_Impl (s, pos, StrlenSafe (s));
}

unsigned StringSegment::Find (const StringSegment& str, unsigned pos) const
{
    return Find_Impl (str.CStr (), pos, str.Length ());
}

unsigned StringSegment::Find (const StringSegment& str, unsigned pos, unsigned n) const
{
    logAssert (str.Length () >= n);
    return Find_Impl (str.CStr (), pos, n);
}

unsigned StringSegment::Find (const char* s, unsigned pos, unsigned n) const
{
    logAssert (StrlenSafe (s) >= n);
    return Find_Impl (s, pos, n);
}

unsigned StringSegment::Find_Impl (const char* s, unsigned pos, unsigned n) const
{
    ConstIterator it = FindSubset (CBegin () + pos, CEnd (), ConstIterator (s), ConstIterator (s + n));
    return Position (it);
}

unsigned StringSegment::RFind (const char* s, unsigned pos) const
{
    return RFind_Impl (s, pos, StrlenSafe (s));
}

unsigned StringSegment::RFind (const StringSegment& str, unsigned pos) const
{
    return RFind_Impl (str.CStr (), pos, str.Length ());
}

unsigned StringSegment::RFind (const StringSegment& str, unsigned pos, unsigned n) const
{
    logAssert (str.Length () >= n);
    return RFind_Impl (str.CStr (), pos, n);
}

unsigned StringSegment::RFind (const char* s, unsigned pos, unsigned n) const
{
    logAssert (StrlenSafe (s) >= n);
    return RFind_Impl (s, pos, n);
}

unsigned StringSegment::RFind_Impl (const char* s, unsigned pos, unsigned n) const
{
    if (n == 0) return pos;

    ConstReverseIterator it = FindSubset (CRBegin () + pos, CREnd (), ConstReverseIterator (s + n - 1), ConstReverseIterator (s - 1));
    return it == CREnd () ? Npos : Distance (it, CREnd ()) - n;
}

unsigned StringSegment::FindFirstOf (const char* s, unsigned pos) const
{
    return FindFirstOf (s, pos, 1);
}

unsigned StringSegment::FindFirstOf (const char* s, unsigned pos, unsigned n) const
{
    bool allowed[256] = {0};
    for (unsigned i = 0; s[i]; ++i)
    {
       allowed[(unsigned)s[i]] = 1;
    }

    ConstIterator it = SearchString (CBegin () + pos, CEnd (), n, allowed);
    return Position (it);
}

unsigned StringSegment::FindFirstOf (char c, unsigned pos) const
{
    return FindFirstOf (c, pos, 1);
}

unsigned StringSegment::FindFirstOf (char c, unsigned pos, unsigned n) const
{
    ConstIterator it = FindN (CBegin () + pos, CEnd (), n, c);
    return Position (it);
}

unsigned StringSegment::FindLastOf (const char* s, unsigned pos) const
{
    return FindLastOf (s, pos, 1);
}

unsigned StringSegment::FindLastOf (const char* s, unsigned pos, unsigned n) const
{
    bool allowed[256] = {0};
    for (unsigned i = 0; s[i]; ++i)
    {
       allowed[(unsigned)s[i]] = 1;
    }

    ConstReverseIterator it = SearchString (CRBegin () + pos, CREnd (), n, allowed);
    return Position (it);
}

unsigned StringSegment::FindLastOf (char c, unsigned pos) const
{
    return FindLastOf (c, pos, 1);
}

unsigned StringSegment::FindLastOf (char c, unsigned pos, unsigned n) const
{
    ConstReverseIterator it = FindN (CRBegin () + pos, CREnd (), n, c);
    return Position (it);
}

unsigned StringSegment::FindFirstNotOf (const char* s, unsigned pos) const
{
    return FindFirstNotOf (s, pos, 1);
}

unsigned StringSegment::FindFirstNotOf (const char* s, unsigned pos, unsigned n) const
{
    bool allowed[256];
    Fill (RandomAccessIterator<bool> (allowed), true, 256);

    for (unsigned i = 0; s[i]; ++i)
    {
       allowed[(unsigned)s[i]] = 0;
    }

    ConstIterator it = SearchString (CBegin () + pos, CEnd (), n, allowed);
    return Position (it);
}

unsigned StringSegment::FindFirstNotOf (char c, unsigned pos) const
{
    return FindFirstNotOf (c, pos, 1);
}

unsigned StringSegment::FindFirstNotOf (char c, unsigned pos, unsigned n) const
{
    auto pred = [](char range_c, char c)
    {
        return range_c != c;
    };

    ConstIterator it = FindN (CBegin () + pos, CEnd (), n, c, pred);
    return Position (it);
}

unsigned StringSegment::FindLastNotOf (const char* s, unsigned pos) const
{
    return FindLastNotOf (s, pos, 1);
}

unsigned StringSegment::FindLastNotOf (const char* s, unsigned pos, unsigned n) const
{
    bool allowed[256];
    Fill (RandomAccessIterator<bool> (allowed), true, 256);

    for (unsigned i = 0; s[i]; ++i)
    {
       allowed[(unsigned)s[i]] = 0;
    }

    ConstReverseIterator it = SearchString (CRBegin () + pos, CREnd (), n, allowed);
    return Position (it);
}

unsigned StringSegment::FindLastNotOf (char c, unsigned pos) const
{
    return FindLastNotOf (c, pos, 1);
}

unsigned StringSegment::FindLastNotOf (char c, unsigned pos, unsigned n) const
{
    auto pred = [](char range_c, char c)
    {
        return range_c != c;
    };

    ConstReverseIterator it = FindN (CRBegin () + pos, CREnd (), n, c, pred);
    return Position (it);
}

int StringSegment::Compare (const char* s, unsigned pos, unsigned n) const
{
    logAssert (StrlenSafe (s) >= n);
    return Compare_Impl (s, pos, n);
}

int StringSegment::Compare (const StringSegment& str, unsigned pos, unsigned n) const
{
    logAssert (str.Length () >= n);
    return Compare (str.CStr (), pos, n);
}

int StringSegment::Compare (const char* s, unsigned pos) const
{
    return Compare_Impl (s, pos, StrlenSafe (s));
}

int StringSegment::Compare (const StringSegment& str, unsigned pos) const
{
    return Compare_Impl (str.CStr (), pos, str.Length ());
}

int StringSegment::Compare_Impl (const char* s, unsigned pos, unsigned n) const
{
    unsigned this_length = Length () - pos;
    unsigned s_length = n;

    if (this_length == s_length)
        return strncmp (CStr () + pos, s, n);

    return this_length > s_length ? 1 : -1;
}

unsigned StringSegment::Position (ConstIterator it) const
{
    return it >= CEnd () ? Npos : Distance (CBegin (), it);
}

unsigned StringSegment::Position (ConstReverseIterator it) const
{
    return it >= CREnd () ? Npos : Distance (it, CREnd ()) - 1;
}

unsigned Cellwars::StrlenSafe (const char* s)
{
    return s ? strlen (s) : 0;
}

bool Cellwars::operator== (const StringSegment& str1, const StringSegment& str2)
{
    return str1.Compare (str2) == 0;
}

bool Cellwars::operator== (const StringSegment& str, const char* s)
{
    return str.Compare (s) == 0;
}

bool Cellwars::operator!= (const StringSegment& str, const char* s)
{
    return !(str == s);
}

bool Cellwars::operator!= (const StringSegment& str1, const StringSegment& str2)
{
    return !(str1 == str2);
}

bool Cellwars::operator< (const StringSegment& str1, const StringSegment& str2)
{
    return str1.Compare (str2) < 0;
}

bool Cellwars::operator> (const StringSegment& str1, const StringSegment& str2)
{
    return Cellwars::operator< (str2, str1);
}

bool Cellwars::operator<= (const StringSegment& str1, const StringSegment& str2)
{
    return !Cellwars::operator> (str1, str2);
}

bool Cellwars::operator>= (const StringSegment& str1, const StringSegment& str2)
{
    return !Cellwars::operator< (str2, str1);
}
