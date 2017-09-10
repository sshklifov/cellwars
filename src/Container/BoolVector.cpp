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

BoolVector::BoolVector (std::initializer_list<bool> l) : BoolVector ()
{
    logAssert (l.size () <= MaxSize ());

    Resize (l.size ());
    Copy (ReverseForwardIterator<const bool> (l.end () - 1),
            ReverseForwardIterator<const bool> (l.begin () - 1),
            Begin ());
}

BoolVector::BoolVector (unsigned req_size) : BoolVector ()
{
    Resize (req_size);
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

void BoolVector::PushBack (bool val)
{
    logAssert (MaxSize () - 1 >= Size ());

    RelativeResize (1);
    Back () = val;
}

void BoolVector::PushBack (bool val, unsigned n)
{
    logAssert (MaxSize () - n >= Size ());

    RelativeResize (n);
    Fill (RBegin (), val, n);
}

void BoolVector::Resize (unsigned req_bits)
{
    v.Resize (BitsToBuckets (req_bits));
    bits = req_bits;
}

void BoolVector::RelativeResize (unsigned req_bits)
{
    logAssert (req_bits <= MaxSize () - Size ());
    Resize (req_bits);
}

void BoolVector::ClosestRelativeResize (unsigned req_bits)
{
    logAssert (Size () != MaxSize () || req_bits != 0);

    if (MaxSize () - req_bits < Size ())
    {
        Resize (MaxSize ());
    }
    else
    {
        Resize (Size () + req_bits);
    }
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
    return Iterator (v.Data (), Size ());
}

ConstIterator BoolVector::CBegin () const
{
    return ConstIterator (v.Data (), 0);
}

ConstIterator BoolVector::CEnd () const
{
    return ConstIterator (v.Data (), Size ());
}

ReverseIterator BoolVector::RBegin ()
{
    return ReverseIterator (v.Data (), Size () - 1);
}

ReverseIterator BoolVector::REnd ()
{
    return ReverseIterator (v.Data (), -1);
}

ConstReverseIterator BoolVector::CRBegin () const
{
    return ConstReverseIterator (v.Data (), Size () - 1);
}

ConstReverseIterator BoolVector::CREnd () const
{
    return ConstReverseIterator (v.Data (), -1);
}

bool BoolVector::Back () const
{
    return *CRBegin ();
}

Proxy BoolVector::Back ()
{
    return *RBegin ();
}

bool BoolVector::Front () const
{
    return *CBegin ();
}

Proxy BoolVector::Front ()
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
    return Begin ()[idx];
}

bool BoolVector::operator[] (unsigned idx) const
{
    logAssert (idx < Size ());
    return CBegin ()[idx];
}

Proxy::Proxy (BoolVector::ValueType* p, unsigned offset)
{
    this->p = p + (offset >> BoolVector::Shift);
    this->offset = offset & BoolVector::Mask;
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
