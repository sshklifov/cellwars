#ifndef _SHADER_H
#define _SHADER_H

#include <glad/glad.h>
#include <logger/logger.h>

#include <cstdio>
#include <cstdlib>

namespace cellwars
{
    /*! @brief Represents OpenGL shaders.
     *
     *  Should not be used in most of the times. It's purpose is to
     *  lay the ground for the Program class.
     */
    class Shader
    {
    public:
        /*! @brief Default ctor.
         *
         *  As a type-safe measure, the shader id will be initialized to 0.
         */
        Shader ()
        {
            id = 0;
        }

        /*! @brief Construct an object from an existing shader id.
         *
         *  @param id OpenGL generated id.
         */
        explicit Shader (GLuint id)
        {
            this->id = id;
        }

        /*! @brief No copy ctor.
         *
         *  To implement copy ctors properly, one must introduce additional overhead (smart pointers).
         *  Since it also includes code complexity, it is best avoided.
         */
        Shader (const Shader&) = delete;

        /*! @brief Move ctor
         *
         *  Change ownership of shader id.
         *
         *  @param rhs Shader class type which is being moved.
         */
        Shader (Shader&& rhs)
        {
            id = rhs.id;
            rhs.id = 0;
        }

        /*! @brief Destructor.
         *
         *  Performes cleanup (glDelete*) when object goes out-of-scope.
         */
        ~Shader ()
        {
            glDeleteShader (id);
        }

        /*! @brief No lvalue assignment operator
         *
         *  Since we do not allow copy ctor, it would make sense to not allow assignment operator as well
         *  (for the very same reason).
         */
        void operator= (const Shader& rhs) = delete;

        /*! @brief Rvalue assignment operator.
         *  
         *  Conveniently set shader id.
         *  
         *  @param rhs Right hand side of assignment.
         *  @return A reference to the left hand side.
         */
        Shader& operator= (Shader&& rhs)
        {
            id = rhs.id;
            rhs.id = 0;

            return (*this);
        }

        /*! @brief Load shader from disk.
         *
         *  Attempts to load in binary form a shader from disk (in text form).
         *
         *  @param file Path to file on file system.
         *  @param type OpenGL constant that determines shader type.
         *  @return True iff call succeeded.
         */
        bool Load (const char* file, GLenum type)
        {
            bool retval = _Impl_Load (file, type);
            if (!retval)
            {
                Clear ();
            }

            return retval;
        }

        /*! @brief Check if loading the shader succeeded.
         *
         *  @remark If @ref Load has not been called, then this function will return false.
         */
        bool IsLoaded () const
        {
            return id != 0;
        }

        /*! @brief Release resources early (before going out-of-scope)
         */
        void Clear ()
        {
            glDeleteShader (id);
            id = 0;
        }

        /*! @brief Allow casting to GLuint
         *
         *  Handy as you'd need only pass the class instance to a gl* call.
         */
        operator GLuint ()
        {
            return id;
        }

    private:
        bool _Impl_Load (const char* path, GLenum type)
        {
            GLint len;
            char* source = get_shader_source (path, &len);
            if (source == nullptr)
            {
                std::free (source);
                return false;
            }

            shader_id = glCreateShader (type);

            glShaderSource (shader_id, 1, &source , &len);
            glCompileShader (shader_id);

#ifndef NDEBUG
            /* NOTE: no need to check if compiled went OK every time.
             * This is useful only in 'pre-release' when you will still
             * be writing your shaders.
             */
            GLint success;
            glGetShaderiv (shader_id, GL_COMPILE_STATUS, &success);

            if (success == GL_FALSE)
            {
                GLint info_log_len;
                glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_len);

                if (info_log_len > 4095)
                {
                    logWarn ("insufficient buffer size of 4096, truncating");
                }

                char log[4096];
                glGetShaderInfoLog (shader_id, 4096, nullptr, log);

                logError ("failed to compile shader %s; reason:\n%s", path, log);

                std::free (source);
                return false;
            }
#endif

            std::free (source);
            return true;
        }

        static char* get_shader_source (const char* path, GLint* len)
        {
            FILE* fp = fopen (path, "rb");
            if (fp == nullptr)
            {
                logError ("cannot open for reading file %s", path);
                return nullptr;
            }

            fseek (fp, 0, SEEK_END);

            unsigned bytes = ftell (fp);
            char* buf = (char*)malloc (bytes);
            if (buf == nullptr)
            {
                logError ("malloc(3) failed");
                return nullptr;
            }

            rewind (fp);
            if (fread (buf, 1, bytes, fp) != bytes)
            {
                logError ("partial/failed read on %s:\n%s", path, buf);
            }

            *len = bytes;
            fclose (fp);
            return buf;
        }

    private:
        GLuint id;
    };
};

#endif /* _SHADER_H */
