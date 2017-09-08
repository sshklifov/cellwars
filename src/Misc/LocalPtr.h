#ifndef LOCAL_PTR_INCLUDED
#define LOCAL_PTR_INCLUDED

#include <cstddef>
#include <type_traits>

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

#include "LocalPtr.inl"

#endif /* LOCAL_PTR_INCLUDED */
