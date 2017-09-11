#ifndef STRING_INCLUDED
#define STRING_INCLUDED

#include "Vector.h"
#include "Iterator.h"
#include "ReverseIterator.h"

#include <iosfwd>

/*! @file String.h
 *
 *  Provides string manipulation functionality.
 *  The String class is basically a Vector<char> with extra member
 *  functions.
 *
 *  You can additionality compare strings, search inside them and
 *  performing I/O (Get and Getline).
 */

namespace Cellwars
{
    class String
    {
    public:
        using Iterator = Vector<char>::Iterator;
        using ConstIterator = Vector<char>::ConstIterator;
        using ReverseIterator = Vector<char>::ReverseIterator;
        using ConstReverseIterator = Vector<char>::ConstReverseIterator;

    public:
        String ();
        explicit String (std::nullptr_t);
        explicit String (unsigned n);
        explicit String (const char* s);
        explicit String (const char* s, unsigned n);
        ~String () = default;

        String (const String& rhs) = default;
        String (String&& rhs) = default;

        String& operator= (const String& rhs) = default;
        String& operator= (String&& rhs) = default;
        String& operator= (const char* s);

        unsigned Capacity () const;
        void Reserve (unsigned req_size);
        void Resize (unsigned req_size);
        void RelativeResize (unsigned req_size);
        void ClosestRelativeResize (unsigned req_size);
        void ShrinkToFit ();
        void Clear ();
        void Swap (String& rhs);

        static unsigned MaxSize ();
        unsigned Length () const;
        unsigned Size () const;
        const char* CStr () const;
        char* Str ();

        ConstIterator CBegin () const;
        ConstIterator CEnd () const;
        ConstReverseIterator CRBegin () const;
        ConstReverseIterator CREnd () const;
        Iterator Begin ();
        Iterator End ();
        ReverseIterator RBegin ();
        ReverseIterator REnd ();

        char Front () const;
        char& Front ();
        char Back () const;
        char& Back ();
        bool Empty () const;
        char operator[] (unsigned idx) const;
        char& operator[] (unsigned idx);

        String Substr (unsigned n) const;
        String Substr (unsigned n, unsigned len) const;

        String& Append (const String& str);
        String& Append (const char* s);
        String& Append (const char* s, unsigned n);
        String& Append (char c, unsigned n = 1);

        String& operator+= (const String& str);
        String& operator+= (const char* s);
        String& operator+= (char c);

        unsigned Find (const char* s, unsigned pos = 0) const;
        unsigned Find (const String& str, unsigned pos = 0) const;
        unsigned Find (const char* s, unsigned pos, unsigned n) const;
        unsigned Find (const String& str, unsigned pos, unsigned n) const;

        unsigned RFind (const char* s, unsigned pos = 0) const;
        unsigned RFind (const String& str, unsigned pos = 0) const;
        unsigned RFind (const char* s, unsigned pos, unsigned n) const;
        unsigned RFind (const String& str, unsigned pos, unsigned n) const;

        unsigned FindFirstOf (const char* s, unsigned pos = 0) const;
        unsigned FindFirstOf (const char* s, unsigned pos, unsigned n) const;
        unsigned FindFirstOf (char c, unsigned pos = 0) const;
        unsigned FindFirstOf (char c, unsigned pos, unsigned n) const;

        unsigned FindLastOf (const char* s, unsigned pos = 0) const;
        unsigned FindLastOf (const char* s, unsigned pos, unsigned n) const;
        unsigned FindLastOf (char c, unsigned pos = 0) const;
        unsigned FindLastOf (char c, unsigned pos, unsigned n) const;

        unsigned FindFirstNotOf (const char* s, unsigned pos = 0) const;
        unsigned FindFirstNotOf (const char* s, unsigned pos, unsigned n) const;
        unsigned FindFirstNotOf (char c, unsigned pos = 0) const;
        unsigned FindFirstNotOf (char c, unsigned pos, unsigned n) const;

        unsigned FindLastNotOf (const char* s, unsigned pos = 0) const;
        unsigned FindLastNotOf (const char* s, unsigned pos, unsigned n) const;
        unsigned FindLastNotOf (char c, unsigned pos = 0) const;
        unsigned FindLastNotOf (char c, unsigned pos, unsigned n) const;

        int Compare (const char* s, unsigned pos = 0) const;
        int Compare (const String& str, unsigned pos = 0) const;
        int Compare (const char* s, unsigned pos, unsigned n) const;
        int Compare (const String& str, unsigned pos, unsigned n) const;

    private:
        unsigned Position (ConstIterator it) const;
        unsigned Position (ConstReverseIterator it) const;
        void AppendNull () const;

    private:
        Vector<char> v;

    public:
        static unsigned Npos;
    };

    bool operator== (const String& str1, const String& str2);
    bool operator== (const String& str, const char* s);
    bool operator!= (const String& str1, const String& str2);
    bool operator!= (const String& str, const char* s);
    bool operator< (const String& str1, const String& str2);
    bool operator> (const String& str1, const String& str2);
    bool operator<= (const String& str1, const String& str2);
    bool operator>= (const String& str1, const String& str2);
    String operator+ (const String& str1, const String& str2);

    std::istream& Get (std::istream& istr, String& str, char delim = '\n');
    std::istream& Getline (std::istream& istr, String& str, char delim = '\n');

    unsigned StrlenSafe (const char* s);
};

#endif /* STRING_INCLUDED */
