#ifndef SHADER_INCLUDED
#define SHADER_INCLUDED

#include <glad/glad.h>

/*! @file Shader.h
 *
 *  Represents OpenGL shaders.
 *  Should not be used in most of the times. It's purpose is to
 *  lay the ground for the Program class.
 */

namespace Cellwars
{
    class Shader
    {
    public:
        Shader ();
        explicit Shader (GLuint id);
        explicit Shader (const char* file, GLenum type);
        ~Shader ();

        Shader (Shader&& rhs);
        Shader& operator= (Shader&& rhs);

        Shader (const Shader&) = delete;
        void operator= (const Shader& rhs) = delete;

        void Load (const char* file, GLenum type);
        bool IsLoaded () const;
        void Clear ();

        operator GLuint () const;

    private:
        GLuint id;
    };
};

#endif /* SHADER_INCLUDED */
