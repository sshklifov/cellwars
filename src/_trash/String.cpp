#include "String.h"
#include <fstream>

using Cellwars::StringBase;
using Cellwars::String;
using Cellwars::Vector;

using Iterator = String::Iterator;
using ConstIterator = String::ConstIterator;
using ReverseIterator = String::ReverseIterator;
using ConstReverseIterator = String::ConstReverseIterator;

String::String ()
{
}

String::String (unsigned n) : v (n)
{
}

String::String (const char* s) : v (ConstIterator (s), StrlenSafe (s))
{
}

String::String (const char* s, unsigned n) : String ()
{
    Reserve (n);
    Copy (RandomAccessIterator<const char> (s), n, Str ());
}

String::String (const StringBase& s) : String (s.CStr (), s.Size ())
{
}

String::~String ()
{
}

String::String (const String& rhs) : v (rhs.v)
{
}

String::String (String&& rhs) : v (std::move (rhs.v))
{
}

String& String::operator= (const String& rhs)
{
    v = rhs.v;
    return (*this);
}

String& String::operator= (String&& rhs)
{
    v = std::move (rhs.v);
    return (*this);
}

String& String::operator= (const char* s)
{
    return operator= (String (s));
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

unsigned String::Length () const
{
    return Size ();
}

unsigned String::Size () const
{
    return v.Size ();
}

const char* String::CStr () const
{
    return v.Data ();
}

char* String::Str ()
{
    return v.Data ();
}


ConstIterator String::CBegin () const
{
    return ConstIterator (CStr ());
}

ConstIterator String::CEnd () const
{
    return ConstIterator (CStr () + Size ());
}

ConstReverseIterator String::CRBegin () const
{
    return ConstReverseIterator (CStr () + Size () - 1);
}

ConstReverseIterator String::CREnd () const
{
    return ConstReverseIterator (CStr () - 1);
}

Iterator String::Begin ()
{
    return Iterator (Str ());
}

Iterator String::End ()
{
    return Iterator (Str () + Size ());
}

ReverseIterator String::RBegin ()
{
    return ReverseIterator (Str () + Size () - 1);
}

ReverseIterator String::REnd ()
{
    return ReverseIterator (Str () - 1);
}

char String::Front () const 
{
    return *CRBegin ();
}

char String::Back () const
{
    return *CBegin ();
}

bool String::Empty () const
{
    return Size () == 0;
}

char String::operator[] (unsigned idx) const
{
    return v[idx];
}

char& String::operator[] (unsigned idx)
{
    return v[idx];
}

String& String::Append (const StringBase& str)
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
    return TreatAsStringSegment().Find (s, pos);
}

unsigned String::Find (const StringBase& str, unsigned pos) const
{
    return TreatAsStringSegment().Find (str, pos);
}

unsigned String::Find (const StringBase& str, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().Find (str, pos, n);
}

unsigned String::Find (const char* s, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().Find (s, pos, n);
}

unsigned String::RFind (const char* s, unsigned pos) const
{
    return TreatAsStringSegment().RFind (s, pos);
}

unsigned String::RFind (const StringBase& str, unsigned pos) const
{
    return TreatAsStringSegment().RFind (str, pos);
}

unsigned String::RFind (const StringBase& str, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().RFind (str, pos, n);
}

unsigned String::RFind (const char* s, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().RFind (s, pos, n);
}

unsigned String::FindFirstOf (const char* s, unsigned pos) const
{
    return TreatAsStringSegment().FindFirstOf (s, pos);
}

unsigned String::FindFirstOf (const char* s, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().FindFirstOf (s, pos, n);
}

unsigned String::FindFirstOf (char c, unsigned pos) const
{
    return TreatAsStringSegment().FindFirstOf (c, pos);
}

unsigned String::FindFirstOf (char c, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().FindFirstOf (c, pos, n);
}

unsigned String::FindLastOf (const char* s, unsigned pos) const
{
    return TreatAsStringSegment().FindLastOf (s, pos);
}

unsigned String::FindLastOf (const char* s, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().FindLastOf (s, pos, n);
}

unsigned String::FindLastOf (char c, unsigned pos) const
{
    return TreatAsStringSegment().FindLastOf (c, pos);
}

unsigned String::FindLastOf (char c, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().FindLastOf (c, pos, n);
}

unsigned String::FindFirstNotOf (const char* s, unsigned pos) const
{
    return TreatAsStringSegment().FindFirstNotOf (s, pos);
}

unsigned String::FindFirstNotOf (const char* s, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().FindFirstNotOf (s, pos, n);
}

unsigned String::FindFirstNotOf (char c, unsigned pos) const
{
    return TreatAsStringSegment().FindFirstNotOf (c, pos);
}

unsigned String::FindFirstNotOf (char c, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().FindFirstNotOf (c, pos, n);
}

unsigned String::FindLastNotOf (const char* s, unsigned pos) const
{
    return TreatAsStringSegment().FindLastNotOf (s, pos);
}

unsigned String::FindLastNotOf (const char* s, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().FindLastNotOf (s, pos, n);
}

unsigned String::FindLastNotOf (char c, unsigned pos) const
{
    return TreatAsStringSegment().FindLastNotOf (c, pos);
}

unsigned String::FindLastNotOf (char c, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().FindLastNotOf (c, pos, n);
}

int String::Compare (const char* s, unsigned pos) const
{
    return TreatAsStringSegment().Compare (s, pos);
}

int String::Compare (const StringBase& str, unsigned pos) const
{
    return TreatAsStringSegment().Compare (str, pos);
}

int String::Compare (const StringBase& str, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().Compare (str, pos, n);
}

int String::Compare (const char* s, unsigned pos, unsigned n) const
{
    return TreatAsStringSegment().Compare (s, pos, n);
}

Cellwars::StringSegment String::TreatAsStringSegment () const
{
    return StringSegment (v.Data (), v.Size ());
}

bool Cellwars::operator== (const StringBase& str1, const StringBase& str2)
{
    return str1.Compare (str2) == 0;
}

bool Cellwars::operator== (const StringBase& str, const char* s)
{
    return str.Compare (s) == 0;
}

bool Cellwars::operator< (const StringBase& str1, const StringBase& str2)
{
    return str1.Compare (str2) == -1;
}

bool Cellwars::operator> (const StringBase& str1, const StringBase& str2)
{
    return Cellwars::operator< (str2, str1);
}

bool Cellwars::operator<= (const StringBase& str1, const StringBase& str2)
{
    return !Cellwars::operator> (str1, str2);
}

bool Cellwars::operator>= (const StringBase& str1, const StringBase& str2)
{
    return !Cellwars::operator< (str2, str1);
}

std::istream& Cellwars::Get (std::istream& istr, String& str, char delim)
{
    constexpr unsigned DEFAULT_SIZE = 1024;

    str.Clear ();
    str.Reserve (DEFAULT_SIZE);

    while (istr && str.Size () != str.MaxSize ())
    {
        unsigned remaining = str.Capacity () - str.Size ();
        istr.get (str.Str () + str.Size (), remaining, delim);
        
        if (istr.peek () == delim)
        {
            break;
        }

        str.Reserve (str.Size ());
    }

    return istr;
}

std::istream& Cellwars::Getline (std::istream& istr, String& str, char delim)
{
    Cellwars::Get (istr, str, delim);
    istr.ignore ();

    return istr;
}

String MakeString (const StringBase& s, unsigned n, unsigned len)
{
    return String (s.CStr () + n, len);
}

String MakeString (const StringBase& s, unsigned n)
{
    return String (s.CStr () + n, s.Size () - n);
}
