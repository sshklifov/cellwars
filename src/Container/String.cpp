#include "String.h"
#include <logger/logger.h>

#include <fstream>
#include <cstring>
#include <climits>

using Cellwars::String;
using Cellwars::Vector;

using Iterator = String::Iterator;
using ConstIterator = String::ConstIterator;
using ReverseIterator = String::ReverseIterator;
using ConstReverseIterator = String::ConstReverseIterator;

template <typename ForwardIt>
static ForwardIt SearchString (ForwardIt first, ForwardIt last, unsigned n, const bool* allowed)
{
    auto pred = [&allowed](char c)
    {
        unsigned idx = c + 128;
        return allowed[idx];
    };

    return SearchN (first, last, n, pred);
}

unsigned String::Npos = MaxSize ();

unsigned String::MaxSize ()
{
    return UINT_MAX;
}

String::String (unsigned n) : v (n)
{
}

String::String (const char* s) : v (ConstIterator (s), StrlenSafe (s))
{
}

String::String (const char* s, unsigned n)
{
    Resize (n);
    Copy (RandomAccessIterator<const char> (s), n, Begin ());
}

String& String::operator= (const char* s)
{
    return operator= (String (s));
}

unsigned String::Length () const
{
    return Size ();
}

unsigned String::Size () const
{
    return v.Size ();
}

unsigned String::Capacity () const
{
    return v.Capacity ();
}

void String::Reserve (unsigned n)
{
    v.Reserve (n);
}

void String::Resize (unsigned req_size)
{
    v.Resize (req_size);
}

void String::RelativeResize (unsigned req_size)
{
    v.RelativeResize (req_size);
}

void String::ShrinkToFit ()
{
    v.ShrinkToFit ();
}

void String::Clear ()
{
    v.Clear ();
}

void String::Swap (String& rhs)
{
    v.Swap (rhs.v);
}

void String::NullTerminate () const 
{
    v.Reserve (Length () + 1);
    v.Data()[Length ()] = '\0';
}

const char* String::CStr () const
{
    NullTerminate ();
    return v.Data ();
}

char* String::Str ()
{
    NullTerminate ();
    return v.Data ();
}

ConstIterator String::CBegin () const
{
    return v.CBegin ();
}

ConstIterator String::CEnd () const
{
    return v.CEnd ();
}

ConstReverseIterator String::CRBegin () const
{
    return v.CRBegin ();
}

ConstReverseIterator String::CREnd () const
{
    return v.CREnd ();
}

Iterator String::Begin ()
{
    return v.Begin ();
}

Iterator String::End ()
{
    return v.End ();
}

ReverseIterator String::RBegin ()
{
    return v.RBegin ();
}

ReverseIterator String::REnd ()
{
    return v.REnd ();
}

char String::Front () const 
{
    return v.Front ();
}

char& String::Front ()
{
    return v.Front ();
}

char String::Back () const
{
    return v.Back ();
}

char& String::Back ()
{
    return v.Back ();
}

bool String::Empty () const
{
    return v.Empty ();
}

char String::operator[] (unsigned idx) const
{
    return v[idx];
}

char& String::operator[] (unsigned idx)
{
    return v[idx];
}

String String::Substr (unsigned n) const
{
    if (n >= Size ()) return String ("");
    return String (CStr () + n, Size () - n);
}

String String::Substr (unsigned n, unsigned len) const
{
    if (n >= Size ()) return String ("");
    if (n + len > Size ()) len = Size () - n;

    return String (CStr () + n, len);
}

String& String::Append (const String& str)
{
    return Append (str.CStr (), str.Length ());
}

String& String::Append (const char* s)
{
    return Append (s, StrlenSafe (s));
}

String& String::Append (const char* s, unsigned n)
{
    v.PushBack (ConstIterator (s), n);
    return (*this);
}

String& String::Append (char c, unsigned n)
{
    v.PushBack (c, n);
    return (*this);
}

String& String::operator+= (const String& str)
{
    return Append (str);
}

String& String::operator+= (const char* s)
{
    return Append (s);
}

String& String::operator+= (char c)
{
    return Append (c, 1);
}

unsigned String::Find (const char* s, unsigned pos) const
{
    return Find_Impl (s, pos, StrlenSafe (s));
}

unsigned String::Find (const String& str, unsigned pos) const
{
    return Find_Impl (str.CStr (), pos, str.Length ());
}

unsigned String::Find (const String& str, unsigned pos, unsigned n) const
{
    logAssert (str.Length () >= n);
    return Find_Impl (str.CStr (), pos, n);
}

unsigned String::Find (const char* s, unsigned pos, unsigned n) const
{
    logAssert (StrlenSafe (s) >= n);
    return Find_Impl (s, pos, n);
}

unsigned String::Find_Impl (const char* s, unsigned pos, unsigned n) const
{
    ConstIterator it = FindSubset (CBegin () + pos, CEnd (), ConstIterator (s), ConstIterator (s + n));
    return Position (it);
}

unsigned String::RFind (const char* s, unsigned pos) const
{
    return RFind_Impl (s, pos, StrlenSafe (s));
}

unsigned String::RFind (const String& str, unsigned pos) const
{
    return RFind_Impl (str.CStr (), pos, str.Length ());
}

unsigned String::RFind (const String& str, unsigned pos, unsigned n) const
{
    logAssert (str.Length () >= n);
    return RFind_Impl (str.CStr (), pos, n);
}

unsigned String::RFind (const char* s, unsigned pos, unsigned n) const
{
    logAssert (StrlenSafe (s) >= n);
    return RFind_Impl (s, pos, n);
}

unsigned String::RFind_Impl (const char* s, unsigned pos, unsigned n) const
{
    if (n == 0) return pos;

    ConstReverseIterator it = FindSubset (CRBegin () + pos, CREnd (), ConstReverseIterator (s + n - 1), ConstReverseIterator (s - 1));
    return it == CREnd () ? Npos : Distance (it, CREnd ()) - n;
}

unsigned String::FindFirstOf (const char* s, unsigned pos) const
{
    return FindFirstOf (s, pos, 1);
}

unsigned String::FindFirstOf (const char* s, unsigned pos, unsigned n) const
{
    bool allowed[256] = {0};
    for (unsigned i = 0; s[i]; ++i)
    {
        unsigned idx = s[i] + 128;
        allowed[idx] = 1;
    }

    ConstIterator it = SearchString (CBegin () + pos, CEnd (), n, allowed);
    return Position (it);
}

unsigned String::FindFirstOf (char c, unsigned pos) const
{
    return FindFirstOf (c, pos, 1);
}

unsigned String::FindFirstOf (char c, unsigned pos, unsigned n) const
{
    ConstIterator it = FindN (CBegin () + pos, CEnd (), n, c);
    return Position (it);
}

unsigned String::FindLastOf (const char* s, unsigned pos) const
{
    return FindLastOf (s, pos, 1);
}

unsigned String::FindLastOf (const char* s, unsigned pos, unsigned n) const
{
    bool allowed[256] = {0};
    for (unsigned i = 0; s[i]; ++i)
    {
        unsigned idx = s[i] + 128;
        allowed[idx] = 1;
    }

    ConstReverseIterator it = SearchString (CRBegin () + pos, CREnd (), n, allowed);
    return Position (it);
}

unsigned String::FindLastOf (char c, unsigned pos) const
{
    return FindLastOf (c, pos, 1);
}

unsigned String::FindLastOf (char c, unsigned pos, unsigned n) const
{
    ConstReverseIterator it = FindN (CRBegin () + pos, CREnd (), n, c);
    return Position (it);
}

unsigned String::FindFirstNotOf (const char* s, unsigned pos) const
{
    return FindFirstNotOf (s, pos, 1);
}

unsigned String::FindFirstNotOf (const char* s, unsigned pos, unsigned n) const
{
    bool allowed[256];
    Fill (RandomAccessIterator<bool> (allowed), true, 256);

    for (unsigned i = 0; s[i]; ++i)
    {
        unsigned idx = s[i] + 128;
        allowed[idx] = 0;
    }

    ConstIterator it = SearchString (CBegin () + pos, CEnd (), n, allowed);
    return Position (it);
}

unsigned String::FindFirstNotOf (char c, unsigned pos) const
{
    return FindFirstNotOf (c, pos, 1);
}

unsigned String::FindFirstNotOf (char c, unsigned pos, unsigned n) const
{
    auto pred = [](char range_c, char c)
    {
        return range_c != c;
    };

    ConstIterator it = FindN (CBegin () + pos, CEnd (), n, c, pred);
    return Position (it);
}

unsigned String::FindLastNotOf (const char* s, unsigned pos) const
{
    return FindLastNotOf (s, pos, 1);
}

unsigned String::FindLastNotOf (const char* s, unsigned pos, unsigned n) const
{
    bool allowed[256];
    Fill (RandomAccessIterator<bool> (allowed), true, 256);

    for (unsigned i = 0; s[i]; ++i)
    {
        unsigned idx = s[i] + 128;
       allowed[idx] = 0;
    }

    ConstReverseIterator it = SearchString (CRBegin () + pos, CREnd (), n, allowed);
    return Position (it);
}

unsigned String::FindLastNotOf (char c, unsigned pos) const
{
    return FindLastNotOf (c, pos, 1);
}

unsigned String::FindLastNotOf (char c, unsigned pos, unsigned n) const
{
    auto pred = [](char range_c, char c)
    {
        return range_c != c;
    };

    ConstReverseIterator it = FindN (CRBegin () + pos, CREnd (), n, c, pred);
    return Position (it);
}

int String::Compare (const char* s, unsigned pos, unsigned n) const
{
    logAssert (StrlenSafe (s) >= n);
    return Compare_Impl (s, pos, n);
}

int String::Compare (const String& str, unsigned pos, unsigned n) const
{
    logAssert (str.Length () >= n);
    return Compare (str.CStr (), pos, n);
}

int String::Compare (const char* s, unsigned pos) const
{
    return Compare_Impl (s, pos, StrlenSafe (s));
}

int String::Compare (const String& str, unsigned pos) const
{
    return Compare_Impl (str.CStr (), pos, str.Length ());
}

int String::Compare_Impl (const char* s, unsigned pos, unsigned n) const
{
    unsigned this_length = Length () - pos;
    unsigned s_length = n;

    if (this_length == s_length)
        return strncmp (CStr () + pos, s, n);

    return this_length > s_length ? 1 : -1;
}

unsigned String::Position (ConstIterator it) const
{
    return it >= CEnd () ? Npos : Distance (CBegin (), it);
}

unsigned String::Position (ConstReverseIterator it) const
{
    return it >= CREnd () ? Npos : Distance (it, CREnd ()) - 1;
}

unsigned Cellwars::StrlenSafe (const char* s)
{
    return s ? strlen (s) : 0;
}

bool Cellwars::operator== (const String& str1, const String& str2)
{
    return str1.Compare (str2) == 0;
}

bool Cellwars::operator== (const String& str, const char* s)
{
    return str.Compare (s) == 0;
}

bool Cellwars::operator!= (const String& str, const char* s)
{
    return !(str == s);
}

bool Cellwars::operator!= (const String& str1, const String& str2)
{
    return !(str1 == str2);
}

bool Cellwars::operator< (const String& str1, const String& str2)
{
    return str1.Compare (str2) < 0;
}

bool Cellwars::operator> (const String& str1, const String& str2)
{
    return Cellwars::operator< (str2, str1);
}

bool Cellwars::operator<= (const String& str1, const String& str2)
{
    return !Cellwars::operator> (str1, str2);
}

bool Cellwars::operator>= (const String& str1, const String& str2)
{
    return !Cellwars::operator< (str2, str1);
}

std::istream& Cellwars::Get (std::istream& istr, String& str, char delim)
{
    str.Clear ();

    constexpr unsigned DEFAULT_SIZE = 128;
    unsigned try_resize = DEFAULT_SIZE;
    unsigned cnt = 0;

    while (istr && str.Size () != str.MaxSize ())
    {
        str.RelativeResize (try_resize);

        unsigned remaining = str.Size () - cnt;
        istr.get (str.Str () + cnt, remaining, delim);
        cnt += istr.gcount ();

        if (istr.peek () == delim) break;
        try_resize = cnt;
    }

    str.Resize (cnt);
    return istr;
}

std::istream& Cellwars::Getline (std::istream& istr, String& str, char delim)
{
    if (istr.peek () == delim)
    {
        istr.ignore ();
        return istr;
    }

    Cellwars::Get (istr, str, delim);
    istr.ignore ();

    return istr;
}

String Cellwars::operator+ (const String& str1, const String& str2)
{
    String res (str1.Length () + str2.Length ());

    res += str1;
    res += str2;

    return res;
}
