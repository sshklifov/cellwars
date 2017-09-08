#include "StringStream.h"

using Cellwars::StringStreamState;
using Cellwars::InputStringStream;

InputStringStream::InputStringStream (const char* s) : InputStringStream (s, StrlenSafe (s))
{
}

InputStringStream::InputStringStream (const char* s, unsigned n) : p (new char[n + 1]), offset (0)
{
    Copy (ForwardIterator<const char> (s), ForwardIterator<const char> (s + n), ForwardIterator<char> (p.GetPtr ()));
    p[n] = '\0';
}

InputStringStream::InputStringStream (const String& str) : InputStringStream (str.CStr (), str.Size ())
{
}

bool InputStringStream::Good () const
{
    return state.GetStateBitField () == StringStreamState::GOOD;
}

InputStringStream::operator bool () const
{
    return Good ();
}

bool InputStringStream::operator! () const
{
    return !Good ();
}

void InputStringStream::SetStates (StringStreamState::ValueType new_states)
{
    state.SetStates (new_states);
}

void InputStringStream::ClearStates (StringStreamState::ValueType old_states)
{
    state.ClearStates (old_states);
}

StringStreamState::ValueType InputStringStream::GetStateBitField () const
{
    return state.GetStateBitField ();
}

InputStringStream& InputStringStream::operator>> (long long& integer)
{
    ScanFmt ("%lld", &integer);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (unsigned long long& integer)
{
    ScanFmt ("%llu", &integer);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (long& integer)
{
    ScanFmt ("%ld", &integer);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (unsigned long& integer)
{
    ScanFmt ("%lu", &integer);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (int& integer)
{
    ScanFmt ("%d", &integer);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (unsigned& integer)
{
    ScanFmt ("%u", &integer);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (short& integer)
{
    ScanFmt ("%hd", &integer);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (unsigned short& integer)
{
    ScanFmt ("%hu", &integer);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (char& c)
{
    ScanFmt ("%c", &c);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (float& flt)
{
    ScanFmt ("%f", &flt);
    return (*this);
}

InputStringStream& InputStringStream::operator>> (double& dbl)
{
    ScanFmt ("%lf", &dbl);
    return (*this);
}
