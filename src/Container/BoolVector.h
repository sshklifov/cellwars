#ifndef BOOL_VECTOR_INCLUDED
#define BOOL_VECTOR_INCLUDED

#include "Vector.h"
#include <logger/logger.h>

#include <cstdint>

namespace Cellwars
{
    template <typename T>
    class BoolVectorIterator;

    template <typename T>
    class BoolVectorReverseIterator;

    class BoolVector
    {
    public:
        using ValueType = uint64_t;
        static constexpr unsigned Mask = 0x0000003F;
        static constexpr unsigned Shift = 6;
        static constexpr unsigned Bits = 64;

    public:
        class Proxy;
        class ConstProxy;

    public:
        using Iterator = BoolVectorIterator<ValueType>;
        using ConstIterator = BoolVectorIterator<const ValueType>;
        using ReverseIterator = BoolVectorReverseIterator<ValueType>;
        using ConstReverseIterator = BoolVectorReverseIterator<const ValueType>;

    public:
        BoolVector ();
        BoolVector (std::initializer_list<bool> l);
        explicit BoolVector (unsigned req_size);
        ~BoolVector () = default;

        BoolVector (const BoolVector& rhs) = default;
        BoolVector (BoolVector&& rhs) = default;

        BoolVector& operator= (const BoolVector& rhs) = default;
        BoolVector& operator= (BoolVector&& rhs) = default;

        static constexpr unsigned MaxSize ();
        unsigned Capacity () const;
        unsigned Size () const;
        unsigned Buckets () const;

        void PushBack (bool val);
        void PushBack (bool val, unsigned n);

        void Reserve (unsigned req_bits);
        void Resize (unsigned req_bits);
        void RelativeResize (unsigned req_bits);
        void ShrinkToFit ();
        void Clear ();
        void Swap (BoolVector& rhs);

        ConstIterator CBegin () const;
        ConstIterator CEnd () const;
        Iterator Begin ();
        Iterator End ();
        ReverseIterator RBegin ();
        ReverseIterator REnd ();
        ConstReverseIterator CRBegin () const;
        ConstReverseIterator CREnd () const;

        const ValueType* Data () const;
        ValueType* Data ();
        bool Front () const;
        Proxy Front ();
        bool Back () const;
        Proxy Back ();
        bool Empty () const;

        void Set (unsigned idx);
        void Clear (unsigned idx);
        void Flip (unsigned idx);

        Proxy operator[] (unsigned idx);
        bool operator[] (unsigned idx) const;

    private:
        static constexpr bool NotMultipleOfBucket (unsigned val);
        static constexpr unsigned BucketsToBits (unsigned val);
        static constexpr unsigned BitsToBuckets (unsigned val);

    private:
        Vector<ValueType> v;
        unsigned bits;
    };

    class BoolVector::Proxy
    {
        friend BoolVector::ConstProxy;

    public:
        explicit Proxy (BoolVector::ValueType* p, unsigned offset);
        Proxy (const Proxy& rhs) = default;
        void operator= (const Proxy&) = delete;

        Proxy& operator= (bool val);
        Proxy& operator^= (bool val);
        Proxy& operator&= (bool val);
        Proxy& operator|= (bool val);

        operator bool () const;

    private:
        BoolVector::ValueType* p;
        unsigned offset;
    };

    class BoolVector::ConstProxy
    {
    public:
        explicit ConstProxy (const BoolVector::ValueType* p, unsigned offset);
        ConstProxy (const ConstProxy& rhs) = default;
        ConstProxy (const Proxy& rhs);
        void operator= (const Proxy&) = delete;

        operator bool () const;

    private:
        const BoolVector::ValueType* p;
        unsigned offset;
    };
};

#include "BoolVectorIterator.h"
#include "BoolVectorReverseIterator.h"

#endif /* BOOL_VECTOR_INCLUDED */
