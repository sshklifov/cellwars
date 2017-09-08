#include "BoolVector.h"
#include "Algorithm.h"
#include <utility>

using Cellwars::Vector;
using Cellwars::BoolVector;

using Iterator = BoolVector::Iterator;
using ConstIterator = BoolVector::ConstIterator;
using ReverseIterator = BoolVector::ReverseIterator;
using ConstReverseIterator = BoolVector::ConstReverseIterator;

using Proxy = BoolVector::Proxy;
using ConstProxy = BoolVector::ConstProxy;

constexpr unsigned BoolVector::Mask;
constexpr unsigned BoolVector::Shift;
constexpr unsigned BoolVector::Bits;

constexpr bool BoolVector::NotMultipleOfBucket (unsigned val)
{
    return val & Mask;
}

constexpr unsigned BoolVector::BucketsToBits (unsigned val)
{
    return val << Shift;
}

constexpr unsigned BoolVector::BitsToBuckets (unsigned val)
{
    return (val >> Shift) + NotMultipleOfBucket (val);
}

BoolVector::BoolVector () : bits (0)
{
}

BoolVector::BoolVector (std::initializer_list<bool> l)
{
    logAssert (l.size () <= MaxSize ());

    Resize (l.size ());
    Copy (ReverseForwardIterator<const bool> (l.end () - 1), ReverseForwardIterator<const bool> (l.begin () - 1), Begin ());
}

BoolVector::BoolVector (unsigned req_size)
{
    Reserve (req_size);
}

constexpr unsigned BoolVector::MaxSize ()
{
    return UINT_MAX;
}

unsigned BoolVector::Capacity () const
{
    constexpr ValueType overflow_mask = ((ValueType (1) << 6) - 1) << (Bits - Shift);

    return v.Capacity () & overflow_mask ? MaxSize () : BucketsToBits (v.Capacity ());
}

unsigned BoolVector::Size () const
{
    return bits;
}

unsigned BoolVector::Buckets () const
{
    return v.Size ();
}

void BoolVector::PushBack (bool val)
{
    logAssert (MaxSize () - 1 >= Size ());

    Resize (Size () + 1);
    Front () = val;
}

void BoolVector::PushBack (bool val, unsigned n)
{
    logAssert (MaxSize () - n >= Size ());


    Resize (Size () + n);
    Fill (RBegin (), val, n);
}

void BoolVector::Resize (unsigned req_bits)
{
    v.Resize (BitsToBuckets (req_bits));
    bits = req_bits;
}

void BoolVector::RelativeResize (unsigned req_bits)
{
    unsigned total_bits = (MaxSize () - req_bits) < Size () ? MaxSize () : Size () + req_bits;
    Resize (total_bits);
}

void BoolVector::ShrinkToFit ()
{
    v.ShrinkToFit ();
}

void BoolVector::Reserve (unsigned req_bits)
{
    v.Reserve (BitsToBuckets (req_bits));
}

void BoolVector::Clear ()
{
    v.Clear ();
    bits = 0;
}

void BoolVector::Swap (BoolVector& rhs)
{
    v.Swap (rhs.v);
    Cellwars::Swap (bits, rhs.bits);
}

Iterator BoolVector::Begin ()
{
    return Iterator (v.Data (), 0);
}

Iterator BoolVector::End ()
{
    Iterator res = Begin ();
    res += bits;

    return res;
}

ConstIterator BoolVector::CBegin () const
{
    return ConstIterator (v.Data (), 0);
}

ConstIterator BoolVector::CEnd () const
{
    ConstIterator res = CBegin ();
    res += bits;

    return res;
}

ReverseIterator BoolVector::REnd ()
{
    ReverseIterator res (v.Data (), 0);
    return ++res;
}

ReverseIterator BoolVector::RBegin ()
{
    ReverseIterator res = REnd ();
    res -= bits;

    return res;
}

ConstReverseIterator BoolVector::CREnd () const
{
    ConstReverseIterator res (v.Data (), 0);
    return ++res;
}

ConstReverseIterator BoolVector::CRBegin () const
{
    ConstReverseIterator res = CREnd ();
    res -= bits;

    return res;
}

const BoolVector::ValueType* BoolVector::Data () const
{
    return v.Data ();
}

BoolVector::ValueType* BoolVector::Data ()
{
    return v.Data ();
}

bool BoolVector::Front () const
{
    return *CRBegin ();
}

Proxy BoolVector::Front ()
{
    return *RBegin ();
}

bool BoolVector::Back () const
{
    return *CBegin ();
}

Proxy BoolVector::Back ()
{
    return *Begin ();
}

bool BoolVector::Empty () const
{
    return bits == 0;
}

void BoolVector::Set (unsigned idx)
{
    logAssert (idx < Size ());

    (*this)[idx] = true;
}

void BoolVector::Clear (unsigned idx)
{
    logAssert (idx < Size ());

    (*this)[idx] = false;
}

void BoolVector::Flip (unsigned idx)
{
    logAssert (idx < Size ());

    (*this)[idx] ^= 1;
}

Proxy BoolVector::operator[] (unsigned idx)
{
    logAssert (idx < Size ());

    return Proxy (v.Data () + (idx >> Shift), idx & Mask);
}

bool BoolVector::operator[] (unsigned idx) const
{
    logAssert (idx < Size ());

    ValueType bucket = *(v.Data () + (idx >> Shift));
    return bucket & (1 << (idx & Mask));
}

Proxy::Proxy (BoolVector::ValueType* p, unsigned offset) : p (p), offset (offset)
{
}

Proxy& Proxy::operator= (bool val)
{
    if (val)
    {
        *p |= (BoolVector::ValueType (1) << offset);
    }
    else
    {
        *p &= (~(BoolVector::ValueType (1) << offset));
    }

    return (*this);
}

Proxy& Proxy::operator^= (bool val)
{
    *p ^= (BoolVector::ValueType (val) << offset);

    return (*this);
}

Proxy& Proxy::operator&= (bool val)
{
    val ^= 1;
    *p &= (~((BoolVector::ValueType (val)) << offset));

    return (*this);
}

Proxy& Proxy::operator|= (bool val)
{
    *p |= (BoolVector::ValueType (val) << offset);

    return (*this);
}

Proxy::operator bool () const
{
    return *p & (BoolVector::ValueType (1) << offset);
}

ConstProxy::ConstProxy (const BoolVector::ValueType* p, unsigned offset) : p (p), offset (offset)
{
}

ConstProxy::ConstProxy (const Proxy& proxy) : p (proxy.p), offset (proxy.offset)
{
}

ConstProxy::operator bool () const
{
    return *p & (BoolVector::ValueType (1) << offset);
}
