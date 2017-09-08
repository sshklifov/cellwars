#ifndef STRING_INCLUDED
#define STRING_INCLUDED

#include "Vector.h"
#include "Iterator.h"
#include "ReverseIterator.h"

#include <iosfwd>

namespace Cellwars
{
    class StringSegment
    {
    public:
        using ConstIterator = RandomAccessIterator<const char>;
        using ConstReverseIterator = ReverseRandomAccessIterator<const char>;

    public:
        StringSegment ();
        explicit StringSegment (const char* begin);
        explicit StringSegment (const char* begin, unsigned size);
        StringSegment (const String& str);

        StringSegment (const StringSegment& rhs) = default;
        StringSegment& operator= (const StringSegment& rhs) = default;
        ~StringSegment () = default;

        static unsigned MaxSize ();
        unsigned Size () const;
        unsigned Length () const;
        const char* CStr () const;

        ConstIterator CBegin () const;
        ConstIterator CEnd () const;
        ConstReverseIterator CRBegin () const;
        ConstReverseIterator CREnd () const;

        void PointToNull ();
        char Front () const;
        char Back () const;
        bool Empty () const;
        char operator[] (unsigned idx) const;

        StringSegment Subseg (unsigned n) const;
        StringSegment Subseg (unsigned n, unsigned len) const;
        String Substr (unsigned n) const;
        String Substr (unsigned n, unsigned len) const;

        unsigned Find (const char* s, unsigned pos = 0) const;
        unsigned Find (const StringSegment& str, unsigned pos = 0) const;
        unsigned Find (const char* s, unsigned pos, unsigned n) const;
        unsigned Find (const StringSegment& str, unsigned pos, unsigned n) const;

        unsigned RFind (const char* s, unsigned pos = 0) const;
        unsigned RFind (const StringSegment& str, unsigned pos = 0) const;
        unsigned RFind (const char* s, unsigned pos, unsigned n) const;
        unsigned RFind (const StringSegment& str, unsigned pos, unsigned n) const;

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
        int Compare (const StringSegment& str, unsigned pos = 0) const;
        int Compare (const char* s, unsigned pos, unsigned n) const;
        int Compare (const StringSegment& str, unsigned pos, unsigned n) const;

    public:
        static unsigned Npos;

    private:
        unsigned Find_Impl (const char* s, unsigned pos, unsigned n) const;
        unsigned RFind_Impl (const char* s, unsigned pos, unsigned n) const;
        int Compare_Impl (const char* s, unsigned pos, unsigned n) const;

        unsigned Position (ConstIterator it) const;
        unsigned Position (ConstReverseIterator it) const;

    private:
        const char* begin;
        unsigned size;
    };

    class String
    {
    public:
        using Iterator = Vector<char>::Iterator;
        using ConstIterator = Vector<char>::ConstIterator;
        using ReverseIterator = Vector<char>::ReverseIterator;
        using ConstReverseIterator = Vector<char>::ConstReverseIterator;

    public:
        String () = default;
        explicit String (unsigned n);
        explicit String (const char* s);
        explicit String (const char* s, unsigned n);
        explicit String (const StringSegment& s);
        ~String () = default;

        String (const String& rhs) = default;
        String (String&& rhs);

        String& operator= (const String& rhs) = default;
        String& operator= (String&& rhs);
        String& operator= (const char* s);

        unsigned Capacity () const;
        void Reserve (unsigned req_size);
        void DoubleCapacity ();
        void Resize (unsigned req_size);
        void RelativeResize (unsigned req_size);
        void ShrinkToFit ();
        void Clear ();
        void Swap (String& rhs);
        void NullTerminate ();

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

        StringSegment Subseg (unsigned n) const;
        StringSegment Subseg (unsigned n, unsigned len) const;
        String Substr (unsigned n) const;
        String Substr (unsigned n, unsigned len) const;

        String& Append (const StringSegment& str);
        String& Append (const char* s);
        String& Append (const char* s, unsigned n);
        String& Append (char c, unsigned n = 1);

        String& operator+= (const String& str);
        String& operator+= (const char* s);
        String& operator+= (char c);

        unsigned Find (const char* s, unsigned pos = 0) const;
        unsigned Find (const StringSegment& str, unsigned pos = 0) const;
        unsigned Find (const char* s, unsigned pos, unsigned n) const;
        unsigned Find (const StringSegment& str, unsigned pos, unsigned n) const;

        unsigned RFind (const char* s, unsigned pos = 0) const;
        unsigned RFind (const StringSegment& str, unsigned pos = 0) const;
        unsigned RFind (const char* s, unsigned pos, unsigned n) const;
        unsigned RFind (const StringSegment& str, unsigned pos, unsigned n) const;

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
        int Compare (const StringSegment& str, unsigned pos = 0) const;
        int Compare (const char* s, unsigned pos, unsigned n) const;
        int Compare (const StringSegment& str, unsigned pos, unsigned n) const;

    public:
        static unsigned Npos;

    private:
        StringSegment TreatAsStringSegment () const;

    private:
        Vector<char> v;
    };

    std::istream& Get (std::istream& istr, String& str, char delim = '\n');
    std::istream& Getline (std::istream& istr, String& str, char delim = '\n');

    bool operator== (const StringSegment& str1, const StringSegment& str2);
    bool operator== (const StringSegment& str, const char* s);
    bool operator!= (const StringSegment& str1, const StringSegment& str2);
    bool operator!= (const StringSegment& str, const char* s);
    bool operator< (const StringSegment& str1, const StringSegment& str2);
    bool operator> (const StringSegment& str1, const StringSegment& str2);
    bool operator<= (const StringSegment& str1, const StringSegment& str2);
    bool operator>= (const StringSegment& str1, const StringSegment& str2);

    String operator+ (const String& str1, const String& str2);

    unsigned StrlenSafe (const char* s);
};

#endif /* STRING_INCLUDED */
