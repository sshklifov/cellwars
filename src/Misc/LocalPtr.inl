#include "LocalPtr.h"
#include <Container/Algorithm.h>

#include <type_traits>

template <typename T, typename U>
Cellwars::LocalPtr<T, U>::LocalPtr (T* ptr, U Deleter) : ptr (ptr), Deleter (Deleter)
{
}

template <typename T, typename U>
Cellwars::LocalPtr<T, U>::LocalPtr (LocalPtr&& rhs) : LocalPtr ()
{
    Swap (rhs);
}

template <typename T, typename U>
Cellwars::LocalPtr<T, U>::~LocalPtr ()
{
    Clear ();
}

template <typename T, typename U>
Cellwars::LocalPtr<T, U>& Cellwars::LocalPtr<T, U>::operator= (LocalPtr&& rhs)
{
    Swap (rhs);
    return (*this);
}

template <typename T, typename U>
Cellwars::LocalPtr<T, U>& Cellwars::LocalPtr<T, U>::operator= (T* p)
{
    if (p == ptr) return (*this);

    Clear ();
    ptr = p;
    
    return (*this);
}

template <typename T, typename U>
void Cellwars::LocalPtr<T, U>::Clear ()
{
    if (ptr)
    {
        Deleter (ptr);
        ptr = NULL;
    }
}

template <typename T, typename U>
T* Cellwars::LocalPtr<T, U>::Release ()
{
    T* res = ptr;
    ptr = NULL;

    return res;
}

template <typename T, typename U>
void Cellwars::LocalPtr<T, U>::Swap (LocalPtr& rhs)
{
    Cellwars::Swap (ptr, rhs.ptr);
    Cellwars::Swap (Deleter, rhs.Deleter);
}

template <typename T, typename U>
U Cellwars::LocalPtr<T, U>::GetDeleter () const
{
    return Deleter;
}

template <typename T, typename U>
void Cellwars::LocalPtr<T, U>::SetDeleter (U Deleter)
{
    this->Deleter = Deleter;
}

template <typename T, typename U>
const T* Cellwars::LocalPtr<T, U>::GetCPtr () const
{
    return ptr;
}

template <typename T, typename U>
T* Cellwars::LocalPtr<T, U>::GetPtr () const
{
    return ptr;
}

template <typename T, typename U>
const T& Cellwars::LocalPtr<T, U>::operator[] (unsigned idx) const
{
    return ptr[idx];
}

template <typename T, typename U>
T& Cellwars::LocalPtr<T, U>::operator[] (unsigned idx)
{
    return ptr[idx];
}

template <typename T, typename U>
T& Cellwars::LocalPtr<T, U>::operator* () const
{
    return *ptr;
}

template <typename T, typename U>
const T* Cellwars::LocalPtr<T, U>::operator-> () const
{
    return GetCPtr ();
}

template <typename T, typename U>
T* Cellwars::LocalPtr<T, U>::operator-> ()
{
    return GetPtr ();
}

template <typename T, typename U>
bool Cellwars::LocalPtr<T, U>::operator! () const
{
    return !ptr;
}

template <typename T, typename U>
Cellwars::LocalPtr<T, U>::operator bool () const
{
    return ptr;
}
