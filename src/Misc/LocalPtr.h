#ifndef LOCAL_PTR_INCLUDED
#define LOCAL_PTR_INCLUDED

#include <cstddef>
#include <type_traits>

/** @file LocalPtr.h
 *
 *  Manage dynamic memory with automatic cleanup.
 *  There can be three types of pointers. The first acts as a regular
 *  one, meaning that no deleter is set. In this case it is presumed
 *  that ownership will be transfered before garbage collection should
 *  be called -- it is for convenience.
 *  
 *  The second and third kind have a valid deleter, it is either a class
 *  or a function. Usually, the class kind is used, as it offers more
 *  functionality. For basic pointers, such as FILE pointers, ones returned
 *  from new[] and malloc, wrapper classes have been declared.
 */

namespace Cellwars
{
    void DefaultDeleter (void* p);

    template <typename T, typename U = void(*)(void*)>
    class LocalPtr
    {
    public:
        template <typename V = U, typename std::enable_if<!std::is_class<V>::value>::type* = nullptr>
        LocalPtr (T* p = nullptr) : ptr (p), Deleter (DefaultDeleter) {}

        template <typename V = U, typename std::enable_if<std::is_class<V>::value>::type* = nullptr>
        LocalPtr (T* p = nullptr) : ptr (p) {}

        explicit LocalPtr (T* ptr, U Deleter);

        LocalPtr (const LocalPtr&) = delete;
        LocalPtr (LocalPtr&& rhs);

        ~LocalPtr ();

        void operator= (const LocalPtr& rhs) = delete;
        LocalPtr& operator= (LocalPtr&& rhs);
        LocalPtr& operator= (T* p);

        void Clear ();
        T* Release ();
        void Swap (LocalPtr& rhs);

        U GetDeleter () const;
        void SetDeleter (U Deleter);

        const T* GetCPtr () const;
        T* GetPtr () const;

        const T& operator[] (unsigned idx) const;
        T& operator[] (unsigned idx);
        T& operator* () const;
        T* operator-> () ;
        const T* operator-> () const;

        bool operator! () const;
        operator bool () const;

    private:
        T* ptr;
        U Deleter;
    };
};

#include "NewPtr.h"
#include "MallocPtr.h"
#include "FilePtr.h"

#include "LocalPtr.inl"

#endif /* LOCAL_PTR_INCLUDED */
