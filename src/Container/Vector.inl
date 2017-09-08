#include <logger/logger.h>

#include "Vector.h"
#include "Algorithm.h"

#include <climits>
#include <utility>

template <typename T>
Cellwars::Vector<T>::Vector ()
{
    arr = NULL;
    size = 0;
    capacity = 0;
}
template <typename T>
Cellwars::Vector<T>::Vector (std::initializer_list<T> l) : Vector ()
{
    logAssert (l.size () < MaxSize ());

    DeepCopy (l.begin (), l.size ());
}

template <typename T>
Cellwars::Vector<T>::Vector (unsigned n) : Vector ()
{
    Reserve (n);
}

template <typename T>
template <typename InputIterator>
Cellwars::Vector<T>::Vector (InputIterator it, unsigned n) : Vector ()
{
    DeepCopy (it, n);
}

template <typename T>
template <typename InputIterator>
Cellwars::Vector<T>::Vector (InputIterator first, InputIterator last) : Vector ()
{
    logAssert (Distance (first, last) < MaxSize ());

    DeepCopy (first, Distance (first, last));
}

template <typename T>
Cellwars::Vector<T>::~Vector ()
{
    Clear ();
}

template <typename T>
Cellwars::Vector<T>::Vector (const Vector& rhs) : Vector ()
{
    DeepCopy (rhs.CBegin (), rhs.Size ());
}

template <typename T>
Cellwars::Vector<T>::Vector (Vector&& rhs) : Vector ()
{
    ShallowCopy (std::move (rhs));
}

template <typename T>
Cellwars::Vector<T>& Cellwars::Vector<T>::operator= (const Vector& rhs)
{
    Vector<T> tmp (rhs);
    Swap (tmp);

    return (*this);
}

template <typename T>
Cellwars::Vector<T>& Cellwars::Vector<T>::operator= (Vector&& rhs)
{
    Vector<T> tmp (std::move (rhs));
    Swap (tmp);
    return (*this);
}

template <typename T>
constexpr unsigned Cellwars::Vector<T>::MaxSize ()
{
    return UINT_MAX;
}

template <typename T>
unsigned Cellwars::Vector<T>::Capacity () const
{
    return capacity;
}

template <typename T>
unsigned Cellwars::Vector<T>::Size () const
{
    return size;
}

template <typename T>
template <typename... Args>
void Cellwars::Vector<T>::EmplaceBack (Args&&... val)
{
    logAssert (MaxSize () - 1 >= Size ());

    Resize (Size () + 1);
    T res = T (std::forward<Args> (val)...);
    /* Front () = T (std::forward<Args> (val)...); */
}

template <typename T>
void Cellwars::Vector<T>::PushBack (const T& val)
{
    logAssert (MaxSize () - 1 >= Size ());

    Resize (Size () + 1);
    Front () = val;
}

template <typename T>
void Cellwars::Vector<T>::PushBack (const T& val, unsigned n)
{
    logAssert (MaxSize () - n >= Size ());

    Resize (Size () + n);
    Fill (RBegin (), val, n);
}

template <typename T>
template <typename InputIt>
void Cellwars::Vector<T>::PushBack (InputIt first, InputIt last)
{
    PushBack (first, Distance (first, last));
}

template <typename T>
template <typename InputIt>
void Cellwars::Vector<T>::PushBack (InputIt it, unsigned n)
{
    logAssert (MaxSize () - n >= Size ());

    Resize (Size () + n);
    Copy (it, n, End () - n);
}

template <typename T>
void Cellwars::Vector<T>::Resize (unsigned req_size)
{
    if (req_size > Size ())
    {
        Reserve (req_size);
    }

    size = req_size;
}

template <typename T>
void Cellwars::Vector<T>::RelativeResize (unsigned req_size)
{
    logAssert (Size () != MaxSize () || req_size != 0);

    if (MaxSize () - req_size < Size ())
    {
        Resize (MaxSize ());
    }
    else
    {
        Resize (Size () + req_size);
    }
}

template <typename T>
void Cellwars::Vector<T>::ShrinkToFit ()
{
    ChangeCapacity (Size ());
}

template <typename T>
void Cellwars::Vector<T>::Reserve (unsigned req_capacity)
{
    if (req_capacity <= Capacity ()) return;

    ChangeCapacity (CalculateCapacity (req_capacity));
}

template <typename T>
void Cellwars::Vector<T>::Clear ()
{
    T* old_arr = arr;

    arr = NULL;
    size = 0;
    capacity = 0;

    delete[] old_arr;
}

template <typename T>
void Cellwars::Vector<T>::Swap (Vector<T>& rhs)
{
    Cellwars::Swap (arr, rhs.arr);
    Cellwars::Swap (size, rhs.size);
    Cellwars::Swap (capacity, rhs.capacity);
}

template <typename T>
T& Cellwars::Vector<T>::operator[] (unsigned idx)
{
    logAssert (idx < Size ());

    return arr[idx];
}

template <typename T>
const T& Cellwars::Vector<T>::operator[] (unsigned idx) const
{
    logAssert (idx < Size ());

    return arr[idx];
}

template <typename T>
typename Cellwars::Vector<T>::Iterator Cellwars::Vector<T>::Begin ()
{
    return Vector<T>::Iterator (Data ());
}

template <typename T>
typename Cellwars::Vector<T>::Iterator Cellwars::Vector<T>::End ()
{
    return Vector<T>::Iterator (Data () + Size ());
}

template <typename T>
typename Cellwars::Vector<T>::ConstIterator Cellwars::Vector<T>::CBegin () const
{
    return Vector<T>::ConstIterator (Data ());
}

template <typename T>
typename Cellwars::Vector<T>::ConstIterator Cellwars::Vector<T>::CEnd () const
{
    return Vector<T>::ConstIterator (Data () + Size ());
}

template <typename T>
typename Cellwars::Vector<T>::ReverseIterator Cellwars::Vector<T>::RBegin ()
{
    return Vector<T>::ReverseIterator (Data () + Size () - 1);
}

template <typename T>
typename Cellwars::Vector<T>::ReverseIterator Cellwars::Vector<T>::REnd ()
{
    return Vector<T>::ReverseIterator (Data () - 1);
}

template <typename T>
typename Cellwars::Vector<T>::ConstReverseIterator Cellwars::Vector<T>::CRBegin () const
{
    return Vector<T>::ConstReverseIterator (Data () + Size () - 1);
}

template <typename T>
typename Cellwars::Vector<T>::ConstReverseIterator Cellwars::Vector<T>::CREnd () const
{
    return Vector<T>::ConstReverseIterator (Data () - 1);
}

template <typename T>
const T* Cellwars::Vector<T>::Data () const
{
    return arr;
}

template <typename T>
T* Cellwars::Vector<T>::Data ()
{
    return arr;
}

template <typename T>
T& Cellwars::Vector<T>::Front ()
{
    return *RBegin ();
}

template <typename T>
const T& Cellwars::Vector<T>::Front () const
{
    return *CRBegin ();
}

template <typename T>
T& Cellwars::Vector<T>::Back ()
{
    return *Begin ();
}

template <typename T>
const T& Cellwars::Vector<T>::Back () const
{
    return *CBegin ();
}

template <typename T>
bool Cellwars::Vector<T>::Empty () const
{
    return Size () == 0;
}

template <typename T>
unsigned Cellwars::Vector<T>::CalculateCapacity (unsigned req_capacity)
{
    constexpr unsigned bits = sizeof (unsigned) * CHAR_BIT;
    bool msb = req_capacity >> (bits - 1);

    return msb ? MaxSize () : (req_capacity << 1);
}

template <typename T>
void Cellwars::Vector<T>::ChangeCapacity (unsigned new_capacity)
{
    T* old_arr = arr;
    arr = new T[new_capacity];

    Move (ConstIterator (old_arr), Size (), Begin ());
    capacity = new_capacity;

    delete[] old_arr;
}

template <typename T>
template <typename InputIterator>
void Cellwars::Vector<T>::DeepCopy (InputIterator it, unsigned n)
{
    if (!it)
    {
        Clear ();
        return;
    }

    Reserve (n);
    Copy (it, n, Begin ());
    size = n;
}

template <typename T>
void Cellwars::Vector<T>::ShallowCopy (Vector&& rhs)
{
    arr = rhs.arr;
    size = rhs.size;
    capacity = rhs.capacity;

    rhs.arr = NULL;
    rhs.size = 0;
    capacity = 0;
}

