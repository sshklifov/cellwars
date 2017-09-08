#ifndef ARRAY_OBJECTS_INCLUDED
#define ARRAY_OBJECTS_INCLUDED

#include <Container/Algorithm.h>
#include <glad/glad.h>
#include <logger/logger.h>

namespace Cellwars
{
    template <unsigned N>
    class BufferObject
    {
    public:
        BufferObject ();
        BufferObject (BufferObject&& rhs);
        BufferObject& operator= (BufferObject&&);

        BufferObject (const BufferObject&) = delete;
        void operator= (const BufferObject&) = delete;

        virtual ~BufferObject ();
        virtual void Load () = 0;
        virtual bool IsLoaded () const = 0;
        virtual void Clear () = 0;
        virtual GLuint operator[] (unsigned index) const = 0;

    protected:
        GLuint objs[N];
    };

    template <unsigned N>
    class VboArray : public BufferObject<N>
    {
    public:
        VboArray ();
        VboArray (VboArray&& rhs) = default;
        VboArray& operator= (VboArray&&) = default;
        virtual ~VboArray() override;

        virtual void Load () override;
        virtual bool IsLoaded () const override;
        virtual void Clear () override;
        virtual GLuint operator[] (unsigned index) const override;
    };

    template <unsigned N>
    class VaoArray : public BufferObject<N>
    {
    public:
        VaoArray ();
        VaoArray (VaoArray&& rhs) = default;
        VaoArray& operator= (VaoArray&&) = default;
        virtual ~VaoArray() override;

        virtual void Load () override;
        virtual bool IsLoaded () const override;
        virtual void Clear () override;
        virtual GLuint operator[] (unsigned index) const override;
    };

    template <unsigned N>
    class TexArray : public BufferObject<N>
    {
    public:
        TexArray ();
        TexArray (TexArray&& rhs) = default;
        TexArray& operator= (TexArray&&) = default;
        virtual ~TexArray() override;

        virtual void Load () override;
        virtual bool IsLoaded () const override;
        virtual void Clear () override;
        virtual GLuint operator[] (unsigned index) const override;
    };
};

#include "ArrayObjects.inl"

#endif /* ARRAY_OBJECTS_INCLUDED */
