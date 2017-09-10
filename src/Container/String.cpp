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
static ForwardIt SearchStringForAny (ForwardIt first, ForwardIt last, unsigned n, const char* allowed)
{
    bool is_allowed[256] = {0};
    for (unsigned i = 0; allowed[i]; ++i)
    {
        unsigned idx = allowed[i] + 128;
        is_allowed[idx] = 1;
    }

    auto pred = [&is_allowed](char c)
    {
        unsigned idx = c + 128;
        return is_allowed[idx];
    };

    return SearchN (first, last, n, pred);
}

template <typename ForwardIt>
static ForwardIt SearchStringForNone (ForwardIt first, ForwardIt last, unsigned n, const char* not_allowed)
{
    bool is_not_allowed[256] = {0};
    for (unsigned i = 0; not_allowed[i]; ++i)
    {
        unsigned idx = not_allowed[i] + 128;
        is_not_allowed[idx] = 1;
    }

    auto pred = [&is_not_allowed](char c)
    {
        unsigned idx = c + 128;
        return !is_not_allowed[idx];
    };

    return SearchN (first, last, n, pred);
}

String::String ()
{
}

String::String (std::nullptr_t)
{
}

String::String (unsigned n)
{
    Resize (n);
}

String::String (const char* s) : String (s, StrlenSafe (s))
{
    AppendNull ();
}

String::String (const char* s, unsigned n)
{
    n = Min (n, StrlenSafe (s));
    v.PushBack (RandomAccessIterator<const char> (s), n);
    AppendNull ();
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
    AppendNull ();
}

void String::RelativeResize (unsigned req_size)
{
    v.RelativeResize (req_size);
    AppendNull ();
}

void String::ClosestRelativeResize (unsigned req_size)
{
    v.ClosestRelativeResize (req_size);
    AppendNull ();
}

void String::ShrinkToFit ()
{
    v.ShrinkToFit ();
    AppendNull ();
}

void String::Clear ()
{
    v.Clear ();
}

void String::Swap (String& rhs)
{
    v.Swap (rhs.v);
}

const char* String::CStr () const
{
    AppendNull ();
    return v.Data ();
}

char* String::Str ()
{
    AppendNull ();
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
    return Substr (n, Size () - n);
}

String String::Substr (unsigned n, unsigned len) const
{
    if (n == Npos) return String (nullptr);

    logAssert (n + len <= Size ());
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
    n = Min (n, StrlenSafe (s));
    v.PushBack (ConstIterator (s), n);
    AppendNull ();

    return (*this);
}

String& String::Append (char c, unsigned n)
{
    v.PushBack (c, n);
    AppendNull ();

    return (*this);
}

void String::AppendNull () const
{
    String* logical_const_this = const_cast<String*> (this);

    logical_const_this->v.Reserve (v.Size () + 1);
    logical_const_this->v.Data()[v.Size ()] = '\0';
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
    return Find (s, pos, StrlenSafe (s));
}

unsigned String::Find (const String& str, unsigned pos) const
{
    return Find (str.CStr (), pos, str.Length ());
}

unsigned String::Find (const String& str, unsigned pos, unsigned n) const
{
    return Find (str.CStr (), pos, n);
}

unsigned String::Find (const char* s, unsigned pos, unsigned n) const
{
    if (pos == Npos) return Npos;
    logAssert (pos < Length ());

    n = Min (n, StrlenSafe (s));

    ConstIterator it = FindSubset (CBegin () + pos, CEnd (), ConstIterator (s), ConstIterator (s + n));
    return Position (it);
}

unsigned String::RFind (const char* s, unsigned pos) const
{
    return RFind (s, pos, StrlenSafe (s));
}

unsigned String::RFind (const String& str, unsigned pos) const
{
    return RFind (str.CStr (), pos, str.Length ());
}

unsigned String::RFind (const String& str, unsigned pos, unsigned n) const
{
    return RFind (str.CStr (), pos, n);
}

unsigned String::RFind (const char* s, unsigned pos, unsigned n) const
{
    if (pos == Npos) return Npos;
    logAssert (pos < Length ());

    n = Min (n, StrlenSafe (s));

    ConstReverseIterator it = FindSubset (CRBegin () + pos,
            CREnd (),
            ConstReverseIterator (s + n - 1),
            ConstReverseIterator (s - 1));

    // NOTE: we are not calling Position (it) as we have reversed the search
    // and must revert back.
    return it == CREnd () ? Npos : Distance (it, CREnd ()) - n;
}

unsigned String::FindFirstOf (const char* s, unsigned pos) const
{
    return FindFirstOf (s, pos, 1);
}

unsigned String::FindFirstOf (char c, unsigned pos) const
{
    return FindFirstOf (c, pos, 1);
}

unsigned String::FindFirstOf (char c, unsigned pos, unsigned n) const
{
    char s[] = {c};
    return FindFirstOf (s, pos, n);
}

unsigned String::FindFirstOf (const char* s, unsigned pos, unsigned n) const
{
    if (pos == Npos) return Npos;
    logAssert (pos < Length ());

    ConstIterator it = SearchStringForAny (CBegin () + pos, CEnd (), n, s);
    return Position (it);
}

unsigned String::FindLastOf (const char* s, unsigned pos) const
{
    return FindLastOf (s, pos, 1);
}

unsigned String::FindLastOf (char c, unsigned pos) const
{
    return FindLastOf (c, pos, 1);
}

unsigned String::FindLastOf (char c, unsigned pos, unsigned n) const
{
    char s[] = {c};
    return FindLastOf (s, pos, n);
}

unsigned String::FindLastOf (const char* s, unsigned pos, unsigned n) const
{
    if (pos == Npos) return Npos;
    logAssert (pos < Length ());

    ConstReverseIterator it = SearchStringForAny (CRBegin () + pos, CREnd (), n, s);
    return Position (it);
}

unsigned String::FindFirstNotOf (const char* s, unsigned pos) const
{
    return FindFirstNotOf (s, pos, 1);
}

unsigned String::FindFirstNotOf (char c, unsigned pos) const
{
    return FindFirstNotOf (c, pos, 1);
}

unsigned String::FindFirstNotOf (char c, unsigned pos, unsigned n) const
{
    char s[] = {c};
    return FindFirstNotOf (s, pos, n);
}

unsigned String::FindFirstNotOf (const char* s, unsigned pos, unsigned n) const
{
    if (pos == Npos) return Npos;
    logAssert (pos < Length ());

    ConstIterator it = SearchStringForNone (CBegin () + pos, CEnd (), n, s);
    return Position (it);
}

unsigned String::FindLastNotOf (const char* s, unsigned pos) const
{
    return FindLastNotOf (s, pos, 1);
}

unsigned String::FindLastNotOf (char c, unsigned pos) const
{
    return FindLastNotOf (c, pos, 1);
}

unsigned String::FindLastNotOf (char c, unsigned pos, unsigned n) const
{
    char s[] = {c};
    return FindLastNotOf (s, pos, n);
}

unsigned String::FindLastNotOf (const char* s, unsigned pos, unsigned n) const
{
    if (pos == Npos) return Npos;
    logAssert (pos < Length ());

    ConstReverseIterator it = SearchStringForNone (CRBegin () + pos, CREnd (), n, s);
    return Position (it);
}

int String::Compare (const String& str, unsigned pos, unsigned n) const
{
    return Compare (str.CStr (), pos, n);
}

int String::Compare (const char* s, unsigned pos) const
{
    return Compare (s, pos, StrlenSafe (s));
}

int String::Compare (const String& str, unsigned pos) const
{
    return Compare (str.CStr (), pos, str.Length ());
}

int String::Compare (const char* s, unsigned pos, unsigned n) const
{
    if (pos == Npos) return StrlenSafe (s) ? -1 : 0;
    logAssert (pos < Length ());

    unsigned this_length = Length () - pos;
    unsigned other_length = n;

    if (this_length == other_length)
        return strncmp (CStr () + pos, s, n);

    return this_length > other_length ? 1 : -1;
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

unsigned String::Npos = MaxSize ();

unsigned String::MaxSize ()
{
    return Vector<char>::MaxSize () - 1;
}

std::istream& Cellwars::Get (std::istream& istr, String& str, char delim)
{
    constexpr unsigned DEFAULT_RESIZE_AMOUNT = 128;
    unsigned resize_amount = DEFAULT_RESIZE_AMOUNT;
    unsigned cnt = 0;

    str.Clear ();

    while (istr && str.Size () != str.MaxSize ())
    {
        str.ClosestRelativeResize (resize_amount);

        unsigned remaining = str.Size () - cnt;
        istr.get (str.Str () + cnt, remaining, delim);
        cnt += istr.gcount ();

        if (istr.peek () == delim) break;
        resize_amount = cnt;
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

