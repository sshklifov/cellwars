#include "StringStream.h"

using Cellwars::StringStreamState;
using Cellwars::OutputStringStream;

OutputStringStream::OutputStringStream (String str) : str (str)
{
}

bool OutputStringStream::Good () const
{
    return state.GetStateBitField () == StringStreamState::GOOD;
}

OutputStringStream::operator bool () const
{
    return Good ();
}

bool OutputStringStream::operator! () const
{
    return !Good ();
}

void OutputStringStream::SetStates (StringStreamState::ValueType new_states)
{
    state.SetStates (new_states);
}

void OutputStringStream::ClearStates (StringStreamState::ValueType old_states)
{
    state.ClearStates (old_states);
}

StringStreamState::ValueType OutputStringStream::GetStateBitField () const
{
    return state.GetStateBitField ();
}

unsigned OutputStringStream::Length ()
{
    return str.Length ();
}

const char* OutputStringStream::CStr ()
{
    return str.CStr ();
}

void OutputStringStream::Clear ()
{
    str.Clear ();
}

OutputStringStream::ConstIterator OutputStringStream::CBegin () const
{
    return str.CBegin ();
}

OutputStringStream::ConstIterator OutputStringStream::CEnd () const
{
    return str.CEnd ();
}

OutputStringStream::ConstReverseIterator OutputStringStream::CRBegin () const
{
    return str.CRBegin ();
}

OutputStringStream::ConstReverseIterator OutputStringStream::CREnd () const
{
    return str.CREnd ();
}

OutputStringStream::Iterator OutputStringStream::Begin ()
{
    return str.Begin ();
}

OutputStringStream::Iterator OutputStringStream::End ()
{
    return str.End ();
}

OutputStringStream::ReverseIterator OutputStringStream::RBegin ()
{
    return str.RBegin ();
}

OutputStringStream::ReverseIterator OutputStringStream::REnd ()
{
    return str.REnd ();
}

Cellwars::String OutputStringStream::Substr (unsigned n) const
{
    return str.Substr (n);
}

Cellwars::String OutputStringStream::Substr (unsigned n, unsigned len) const
{
    return str.Substr (n, len);
}

OutputStringStream& OutputStringStream::operator<< (long long integer)
{
    PrintFmt ("%lld", integer);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (unsigned long long integer)
{
    PrintFmt ("%llu", integer);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (long integer)
{
    PrintFmt ("%ld", integer);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (unsigned long integer)
{
    PrintFmt ("%lu", integer);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (int integer)
{
    PrintFmt ("%d", integer);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (unsigned integer)
{
    PrintFmt ("%u", integer);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (short integer)
{
    PrintFmt ("%hd", integer);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (unsigned short integer)
{
    PrintFmt ("%hu", integer);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (char c)
{
    PrintFmt ("%c", c);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (const char* s)
{
    PrintFmt ("%s", s);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (const String& str)
{
    PrintFmt ("%.*s", str.Size (), str.CStr ());
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (float flt)
{
    PrintFmt ("%f", flt);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (double dbl)
{
    PrintFmt ("%lf", dbl);
    return (*this);
}

OutputStringStream& OutputStringStream::operator<< (bool b)
{
    return (*this) << (b ? "true" : "false");
}
