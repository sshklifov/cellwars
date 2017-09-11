#ifndef PROGRAM_INCLUDED
#define PROGRAM_INCLUDED

#include <glad/glad.h>

/*! @file Program.h
 *
 *  Represents OpenGL programmes.
 *  This class will be responsible for loading GLSL programmes and
 *  automatically cleaning up.
 */

namespace Cellwars
{
    class Program
    {
    public:
        Program ();
        explicit Program (GLuint id);
        explicit Program (const char* name, const char* shaders);
        ~Program ();

        Program (const Program&) = delete;
        void operator= (const Program& rhs) = delete;

        Program (Program&& rhs);
        Program& operator= (Program&& rhs);

        void Load (const char* name, const char* shaders);
        bool IsLoaded () const;
        void Clear ();

        operator GLuint () const;

    private:
        void LoadImpl (const char* name, const char* shaders);

    private:
        GLuint id;
    };
};

#endif /* PROGRAM_INCLUDED */
