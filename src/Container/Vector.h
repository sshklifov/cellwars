#ifndef VECTOR_INCLUDED
#define VECTOR_INCLUDED

#include "Iterator.h"
#include "ReverseIterator.h"

#include <initializer_list>

namespace Cellwars
{
    template <typename T>
    class Vector
    {
    public:
        using Iterator = RandomAccessIterator<T>;
        using ReverseIterator = ReverseRandomAccessIterator<T>;
        using ConstIterator = RandomAccessIterator<const T>;
        using ConstReverseIterator = ReverseRandomAccessIterator<const T>;

    public:
        Vector ();
        Vector (std::initializer_list<T> l);
        explicit Vector (unsigned req_size);

        template <typename InputIterator>
        explicit Vector (InputIterator it, unsigned n);

        template <typename InputIterator>
        explicit Vector (InputIterator first, InputIterator last);
        ~Vector ();

        Vector (const Vector& rhs);
        Vector (Vector&& rhs);

        Vector& operator= (const Vector& rhs);
        Vector& operator= (Vector&& rhs);

        static constexpr unsigned MaxSize ();
        unsigned Capacity () const;
        unsigned Size () const;

        template <typename... Args>
        void EmplaceBack (Args&&... val);

        void PushBack (const T& val);
        void PushBack (const T& val, unsigned n);

        template <typename InputIt>
        void PushBack (InputIt first, InputIt last);

        template <typename InputIt>
        void PushBack (InputIt it, unsigned n);

        void Reserve (unsigned req_size);
        void Resize (unsigned req_size);
        void RelativeResize (unsigned req_size);
        void ClosestRelativeResize (unsigned req_size);
        void ShrinkToFit ();
        void Clear ();
        void Swap (Vector& rhs);

        ConstIterator CBegin () const;
        ConstIterator CEnd () const;
        Iterator Begin ();
        Iterator End ();
        ReverseIterator RBegin ();
        ReverseIterator REnd ();
        ConstReverseIterator CRBegin () const;
        ConstReverseIterator CREnd () const;

        const T* Data () const;
        T* Data ();
        T& Front ();
        const T& Front () const;
        T& Back ();
        const T& Back () const;
        bool Empty () const;

        T& operator[] (unsigned idx);
        const T& operator[] (unsigned idx) const;

    private:
        static unsigned CalculateCapacity (unsigned size);

        void ChangeCapacity (unsigned new_capacity);

        template <typename InputIterator>
        void DeepCopy (InputIterator it, unsigned n);

        void ShallowCopy (Vector&& rhs);

    protected:
        T* arr;
        unsigned size;
        unsigned capacity;
    };
};

#include "Vector.inl"

#endif /* VECTOR_INCLUDED */
