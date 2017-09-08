#ifndef _ARRAY_OBJECTS_H
#define _ARRAY_OBJECTS_H

#include <glad/glad.h>
#include <logger/logger.h>

namespace Cellwars
{
    template <unsigned N>
    class BufferObject
    {
    public:
        BufferObject () : objs {0}
        {
        }

        BufferObject (const BufferObject&) = delete;

        BufferObject (BufferObject&&) = delete;

        virtual ~BufferObject ()
        {
        }

        virtual void DeferredInit () = 0;

        GLuint operator[] (unsigned index) const
        {
            logAssert (index < N);

            return objs[index];
        }

    protected:
        GLuint objs[N];
    };

    template <unsigned N>
    class VboArray : public BufferObject<N>
    {
    public:
        VboArray ()
        {
            glGenBuffers (N, this->objs);
        }

        virtual ~VboArray() override
        {
            glDeleteBuffers (N, this->objs);
        }

        virtual void DeferredInit () override
        {
            glGenBuffers (N, this->objs);
        }
    };

    template <unsigned N>
    class VaoArray : public BufferObject<N>
    {
    public:
        VaoArray ()
        {
            glGenVertexArrays (N, this->objs);
        }

        virtual ~VaoArray() override
        {
            glDeleteVertexArrays (N, this->objs);
        }

        virtual void DeferredInit () override
        {
            glGenVertexArrays (N, this->objs);
        }
    };

    template <unsigned N>
    class TexArray : public BufferObject<N>
    {
    public:
        TexArray ()
        {
            glGenTextures (N, this->objs);
        }

        virtual ~TexArray() override
        {
            glDeleteTextures (N, this->objs);
        }

        virtual void DeferredInit () override
        {
            glGenTextures (N, this->objs);
        }
    };
};

#endif /* _ARRAY_OBJECTS_H */
