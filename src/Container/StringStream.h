#ifndef STRING_STREAM_INCLUDED
#define STRING_STREAM_INCLUDED

#include "String.h"
#include <Misc/NewPtr.h>

/*! @file StringStream.h
 *
 *  Provides cin/cout like features for String (@sa @file String.h).
 *  It would be nice if one could treat a string as a stream, with the
 *  exception that data is not coming from/going to an IO device but
 *  simply retried from/stored in memory. InputStringStream and OutputStringStream
 *  do exactly that, respectively.
 */

namespace Cellwars
{
    class StringStreamState
    {
    public:
        using ValueType = unsigned short;
        enum {GOOD = 0, FAIL = 1, BAD = 2};

    public:
        void SetStates (ValueType new_states);
        void ClearStates (ValueType old_states);
        ValueType GetStateBitField () const;

    private:
        ValueType state = GOOD;
    };


    class InputStringStream
    {
    public:
        explicit InputStringStream (String str);
        explicit InputStringStream (const char* s);
        explicit InputStringStream (const char* s, unsigned n);

        InputStringStream () = delete;
        InputStringStream (const InputStringStream&) = delete;
        void operator= (const InputStringStream&) = delete;

        bool Good () const;
        operator bool () const;
        bool operator! () const;
        void SetStates (StringStreamState::ValueType new_states);
        void ClearStates (StringStreamState::ValueType old_states);
        StringStreamState::ValueType GetStateBitField () const;

        template <typename... Args>
        int ScanFmt (const char* fmt, Args... args);

        InputStringStream& operator>> (long long&);
        InputStringStream& operator>> (unsigned long long&);
        InputStringStream& operator>> (long&);
        InputStringStream& operator>> (unsigned long&);
        InputStringStream& operator>> (int&);
        InputStringStream& operator>> (unsigned&);
        InputStringStream& operator>> (short&);
        InputStringStream& operator>> (unsigned short&);

        InputStringStream& operator>> (char&);

        InputStringStream& operator>> (float&);
        InputStringStream& operator>> (double&);

    private:
        template <typename... Args>
        int ScanFmtWrap (const char* fmt, Args... args);

    private:
        String str;
        unsigned offset;

        StringStreamState state;
    };

    class OutputStringStream
    {
    public:
        using Iterator = String::Iterator;
        using ReverseIterator = String::ReverseIterator;
        using ConstIterator = String::ConstIterator;
        using ConstReverseIterator = String::ConstReverseIterator;

    public:
        explicit OutputStringStream (String str);

        OutputStringStream () = default;
        OutputStringStream (const OutputStringStream&) = delete;
        void operator= (const OutputStringStream&) = delete;

        bool Good () const;
        operator bool () const;
        bool operator! () const;
        void SetStates (StringStreamState::ValueType new_states);
        void ClearStates (StringStreamState::ValueType old_states);
        StringStreamState::ValueType GetStateBitField () const;

        unsigned Length ();
        const char* CStr ();
        void Clear ();

        ConstIterator CBegin () const;
        ConstIterator CEnd () const;
        ConstReverseIterator CRBegin () const;
        ConstReverseIterator CREnd () const;
        Iterator Begin ();
        Iterator End ();
        ReverseIterator RBegin ();
        ReverseIterator REnd ();

        String Substr (unsigned n) const;
        String Substr (unsigned n, unsigned len) const;

        template <typename... Args>
        int PrintFmt (const char* fmt, Args... args);

        OutputStringStream& operator<< (long long);
        OutputStringStream& operator<< (unsigned long long);
        OutputStringStream& operator<< (long);
        OutputStringStream& operator<< (unsigned long);
        OutputStringStream& operator<< (int);
        OutputStringStream& operator<< (unsigned);
        OutputStringStream& operator<< (short);
        OutputStringStream& operator<< (unsigned short);

        OutputStringStream& operator<< (char);
        OutputStringStream& operator<< (const char*);
        OutputStringStream& operator<< (const String&);

        OutputStringStream& operator<< (float);
        OutputStringStream& operator<< (double);

        OutputStringStream& operator<< (bool);

    private:
        template <typename... Args>
        int TryPrintFmt (unsigned resize_amount, const char* fmt, Args... args);

    private:
        String str;
        StringStreamState state;
    };
};

#include "StringStream.inl"

#endif /* STRING_STREAM_INCLUDED */
