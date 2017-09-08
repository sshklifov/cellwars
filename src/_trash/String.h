#ifndef STRING_INCLUDED
#define STRING_INCLUDED

#include "Vector.h"
#include <iosfwd>

namespace Cellwars
{
    class StringBase
    {
    public:
        using ConstIterator = Vector<char>::ConstIterator;
        using ConstReverseIterator = Vector<char>::ConstReverseIterator;

    public:
        static unsigned MaxSize ();
        static unsigned Npos;

    public:
        virtual ~StringBase () {};

        virtual unsigned Size () const = 0;
        virtual unsigned Length () const = 0;
        virtual const char* CStr () const = 0;

        virtual ConstIterator CBegin () const = 0;
        virtual ConstIterator CEnd () const = 0;
        virtual ConstReverseIterator CRBegin () const = 0;
        virtual ConstReverseIterator CREnd () const = 0;

        virtual char Front () const = 0;
        virtual char Back () const = 0;
        virtual bool Empty () const = 0;
        virtual char operator[] (unsigned idx) const = 0;

        virtual unsigned Find (const char* s, unsigned pos = 0) const = 0;
        virtual unsigned Find (const StringBase& str, unsigned pos = 0) const = 0;
        virtual unsigned Find (const char* s, unsigned pos, unsigned n) const = 0;
        virtual unsigned Find (const StringBase& str, unsigned pos, unsigned n) const = 0;

        virtual unsigned RFind (const char* s, unsigned pos = 0) const = 0;
        virtual unsigned RFind (const StringBase& str, unsigned pos = 0) const = 0;
        virtual unsigned RFind (const char* s, unsigned pos, unsigned n) const = 0;
        virtual unsigned RFind (const StringBase& str, unsigned pos, unsigned n) const = 0;

        virtual unsigned FindFirstOf (const char* s, unsigned pos = 0) const = 0;
        virtual unsigned FindFirstOf (const char* s, unsigned pos, unsigned n) const = 0;
        virtual unsigned FindFirstOf (char c, unsigned pos = 0) const = 0;
        virtual unsigned FindFirstOf (char c, unsigned pos, unsigned n) const = 0;

        virtual unsigned FindLastOf (const char* s, unsigned pos = 0) const = 0;
        virtual unsigned FindLastOf (const char* s, unsigned pos, unsigned n) const = 0;
        virtual unsigned FindLastOf (char c, unsigned pos = 0) const = 0;
        virtual unsigned FindLastOf (char c, unsigned pos, unsigned n) const = 0;

        virtual unsigned FindFirstNotOf (const char* s, unsigned pos = 0) const = 0;
        virtual unsigned FindFirstNotOf (const char* s, unsigned pos, unsigned n) const = 0;
        virtual unsigned FindFirstNotOf (char c, unsigned pos = 0) const = 0;
        virtual unsigned FindFirstNotOf (char c, unsigned pos, unsigned n) const = 0;

        virtual unsigned FindLastNotOf (const char* s, unsigned pos = 0) const = 0;
        virtual unsigned FindLastNotOf (const char* s, unsigned pos, unsigned n) const = 0;
        virtual unsigned FindLastNotOf (char c, unsigned pos = 0) const = 0;
        virtual unsigned FindLastNotOf (char c, unsigned pos, unsigned n) const = 0;

        virtual int Compare (const char* s, unsigned pos = 0) const = 0;
        virtual int Compare (const StringBase& str, unsigned pos = 0) const = 0;
        virtual int Compare (const char* s, unsigned pos, unsigned n) const = 0;
        virtual int Compare (const StringBase& str, unsigned pos, unsigned n) const = 0;

    protected:
        static unsigned StrlenSafe (const char* s);
    };

    class StringSegment : public StringBase
    {
    public:
        explicit StringSegment (const char* begin = NULL, unsigned size = 0);
        StringSegment (const StringSegment& rhs);
        StringSegment& operator= (const StringSegment& rhs);
        virtual ~StringSegment () override;

        virtual unsigned Size () const override;

        virtual unsigned Length () const override;
        virtual const char* CStr () const override;

        virtual ConstIterator CBegin () const override;
        virtual ConstIterator CEnd () const override;
        virtual ConstReverseIterator CRBegin () const override;
        virtual ConstReverseIterator CREnd () const override;

        virtual char Front () const override;
        virtual char Back () const override;
        virtual bool Empty () const override;
        virtual char operator[] (unsigned idx) const override;

        virtual unsigned Find (const char* s, unsigned pos = 0) const override;
        virtual unsigned Find (const StringBase& str, unsigned pos = 0) const override;
        virtual unsigned Find (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned Find (const StringBase& str, unsigned pos, unsigned n) const override;

        virtual unsigned RFind (const char* s, unsigned pos = 0) const override;
        virtual unsigned RFind (const StringBase& str, unsigned pos = 0) const override;
        virtual unsigned RFind (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned RFind (const StringBase& str, unsigned pos, unsigned n) const override;

        virtual unsigned FindFirstOf (const char* s, unsigned pos = 0) const override;
        virtual unsigned FindFirstOf (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned FindFirstOf (char c, unsigned pos = 0) const override;
        virtual unsigned FindFirstOf (char c, unsigned pos, unsigned n) const override;

        virtual unsigned FindLastOf (const char* s, unsigned pos = 0) const override;
        virtual unsigned FindLastOf (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned FindLastOf (char c, unsigned pos = 0) const override;
        virtual unsigned FindLastOf (char c, unsigned pos, unsigned n) const override;

        virtual unsigned FindFirstNotOf (const char* s, unsigned pos = 0) const override;
        virtual unsigned FindFirstNotOf (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned FindFirstNotOf (char c, unsigned pos = 0) const override;
        virtual unsigned FindFirstNotOf (char c, unsigned pos, unsigned n) const override;

        virtual unsigned FindLastNotOf (const char* s, unsigned pos = 0) const override;
        virtual unsigned FindLastNotOf (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned FindLastNotOf (char c, unsigned pos = 0) const override;
        virtual unsigned FindLastNotOf (char c, unsigned pos, unsigned n) const override;

        virtual int Compare (const char* s, unsigned pos = 0) const override;
        virtual int Compare (const StringBase& str, unsigned pos = 0) const override;
        virtual int Compare (const char* s, unsigned pos, unsigned n) const override;
        virtual int Compare (const StringBase& str, unsigned pos, unsigned n) const override;

    private:
        unsigned Position (ConstIterator it) const;
        unsigned Position (ConstReverseIterator it) const;

    private:
        const char* begin;
        unsigned size;
    };

    class String : public StringBase
    {
    public:
        using Iterator = Vector<char>::Iterator;
        using ReverseIterator = Vector<char>::ReverseIterator;

    public:
        String ();
        explicit String (unsigned n);
        explicit String (const char* s);
        explicit String (const char* s, unsigned n);
        explicit String (const StringBase& s);
        virtual ~String ();

        String (const String& rhs);
        String (String&& rhs);

        String& operator= (const String& rhs);
        String& operator= (String&& rhs);
        String& operator= (const char* s);

        unsigned Capacity () const;
        void Reserve (unsigned req_size);
        void Resize (unsigned req_size);
        void ShrinkToFit ();
        void Clear ();
        void Swap (String& rhs);

        virtual unsigned Length () const override;
        virtual unsigned Size () const override;
        virtual const char* CStr () const override;
        char* Str ();

        virtual ConstIterator CBegin () const override;
        virtual ConstIterator CEnd () const override;
        virtual ConstReverseIterator CRBegin () const override;
        virtual ConstReverseIterator CREnd () const override;
        Iterator Begin ();
        Iterator End ();
        ReverseIterator RBegin ();
        ReverseIterator REnd ();

        virtual char Front () const override;
        virtual char Back () const override;
        virtual bool Empty () const override;
        virtual char operator[] (unsigned idx) const override;
        char& operator[] (unsigned idx);

        String& Append (const StringBase& str);
        String& Append (const char* s);
        String& Append (const char* s, unsigned n);
        String& Append (char c, unsigned n);

        String& operator+= (const String& str);
        String& operator+= (const char* s);
        String& operator+= (char c);

        virtual unsigned Find (const char* s, unsigned pos = 0) const override;
        virtual unsigned Find (const StringBase& str, unsigned pos = 0) const override;
        virtual unsigned Find (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned Find (const StringBase& str, unsigned pos, unsigned n) const override;

        virtual unsigned RFind (const char* s, unsigned pos = 0) const override;
        virtual unsigned RFind (const StringBase& str, unsigned pos = 0) const override;
        virtual unsigned RFind (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned RFind (const StringBase& str, unsigned pos, unsigned n) const override;

        virtual unsigned FindFirstOf (const char* s, unsigned pos = 0) const override;
        virtual unsigned FindFirstOf (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned FindFirstOf (char c, unsigned pos = 0) const override;
        virtual unsigned FindFirstOf (char c, unsigned pos, unsigned n) const override;

        virtual unsigned FindLastOf (const char* s, unsigned pos = 0) const override;
        virtual unsigned FindLastOf (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned FindLastOf (char c, unsigned pos = 0) const override;
        virtual unsigned FindLastOf (char c, unsigned pos, unsigned n) const override;

        virtual unsigned FindFirstNotOf (const char* s, unsigned pos = 0) const override;
        virtual unsigned FindFirstNotOf (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned FindFirstNotOf (char c, unsigned pos = 0) const override;
        virtual unsigned FindFirstNotOf (char c, unsigned pos, unsigned n) const override;

        virtual unsigned FindLastNotOf (const char* s, unsigned pos = 0) const override;
        virtual unsigned FindLastNotOf (const char* s, unsigned pos, unsigned n) const override;
        virtual unsigned FindLastNotOf (char c, unsigned pos = 0) const override;
        virtual unsigned FindLastNotOf (char c, unsigned pos, unsigned n) const override;

        virtual int Compare (const char* s, unsigned pos = 0) const override;
        virtual int Compare (const StringBase& str, unsigned pos = 0) const override;
        virtual int Compare (const char* s, unsigned pos, unsigned n) const override;
        virtual int Compare (const StringBase& str, unsigned pos, unsigned n) const override;

    private:
        StringSegment TreatAsStringSegment () const;

    private:
        Vector<char> v;
    };

    std::istream& Get (std::istream& istr, String& str, char delim = '\n');
    std::istream& Getline (std::istream& istr, String& str, char delim = '\n');

    StringSegment MakeStringSegment (const StringBase& s, unsigned n, unsigned len);
    StringSegment MakeStringSegment (const StringBase& s, unsigned n);
    String MakeString (const StringBase& s, unsigned n, unsigned len);
    String MakeString (const StringBase& s, unsigned n);

    bool operator== (const StringBase& str1, const StringBase& str2);
    bool operator== (const StringBase& str, const char* s);
    bool operator< (const StringBase& str1, const StringBase& str2);
    bool operator> (const StringBase& str1, const StringBase& str2);
    bool operator<= (const StringBase& str1, const StringBase& str2);
    bool operator>= (const StringBase& str1, const StringBase& str2);
};

#endif /* STRING_INCLUDED */
