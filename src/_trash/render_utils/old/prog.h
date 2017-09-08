#ifndef _PROG_H
#define _PROG_H

#include <glad.h>
#include <logger.h>
#include "shader.h"

namespace cellwars
{
    /*! @brief Represents OpenGL programmes.
     *
     *  This class will be responsible for loading GLSL programmes and
     *  automatically cleaning up.
     */
    class prog
    {
    public:
        /*! @brief Default ctor.
         *
         *  As a type-safe measure, the programme id will be initialized to 0.
         */
        prog ()
        {
            prog_id = 0;
        }

        /*! @brief Construct on object from an existing programme id
         */
        explicit prog (GLuint prog_id)
        {
            this->prog_id = prog_id;
        }

        /*! @brief No copy ctor
         *
         *  To implement copy ctors properly, one must introcude additional overhead (akin to smart pointers).
         *  Since it also includes code complexity, it is best avoided.
         */
        prog (const prog&) = delete;

        /*! @brief Move ctor
         *
         *  Change ownership of the programme id.
         */
        prog (prog&& rhs)
        {
            prog_id = rhs.prog_id;
            rhs.prog_id = 0;
        }

        /*! @brief Conveniently change ownership of programme
         *
         *  @remark Does not return (*this)
         */
        void operator= (prog&& rhs)
        {
            prog_id = rhs.prog_id;
            rhs.prog_id = 0;
        }

        /*! @brief Destructor.
         *
         *  Performes cleanup as promised when object goes out-of-scope.
         */
        ~prog ()
        {
            glDeleteProgram (prog_id);
        }

        /*! @brief Load programme from disk.
         *
         *  Attempts to load in binary form a programme. There is
         *  a standard method to search for shaders. First, @param name
         *  specifies the name of the shader group that forms a logical
         *  unit (programme). @param shaders specifies which shader types
         *  to search for. Available values are:
         *  -'v' for '*.vert'
         *  -'e' for '*.tese'
         *  -'c' for '*.tesc'
         *  -'g' for '*.geom'
         *  -'f' for '*.frag'
         *  -'c' for '*.comp'
         *
         *  @param name Path to shaders without their extensions
         *  @param shaders String of shaders to load.
         *  @return True/false on success/failure respectively.
         */
        bool load (const char* name, const char* shaders)
        {
            bool retval = impl_load (name, shaders);
            if (!retval)
            {
                free ();
            }

            return retval;
        }

        /*! @brief Check if loading the programme succeeded.
         *
         *  @remark If @ref load has not been called, then this function will return false.
         */
        bool is_loaded () const
        {
            return prog_id != 0;
        }

        /*! @brief Release resources early (before going out-of-scope)
         */
        void free ()
        {
            glDeleteProgram (prog_id);
            prog_id = 0;
        }

        /*! @brief Allow casting to GLuint
         *
         *  Handy as you'd need only pass the name of the object.
         */
        operator GLuint ()
        {
            return prog_id;
        }

    private:
        bool impl_load (const char* name, const char* shaders)
        {
            prog_id = glCreateProgram ();

            /* NOTE: maximum amount of shaders that compose a programme is 5
             */
            shader s[5];
            for (unsigned i = 0; shaders[i] != '\0'; ++i)
            {
                s[i] = get_shader (name, shaders[i]);

                if (!s[i].is_loaded ())
                {
                    return false;
                }

                glAttachShader (prog_id, s[i]);
            }

            glLinkProgram (prog_id);

#ifndef NDEBUG
            /* NOTE: no need to check if linking went OK every time.
             * This is useful only in 'pre-release' when you will still
             * be writing your shaders.
             */
            GLint success;
            glGetProgramiv (prog_id, GL_LINK_STATUS, &success);

            if (success == GL_FALSE)
            {
                GLint info_log_len;
                glGetProgramiv (prog_id, GL_INFO_LOG_LENGTH, &info_log_len);

                if (info_log_len > 4096)
                {
                    logWarn ("insufficient buffer suze of 4096, truncating");
                }

                char log[4096];
                glGetProgramInfoLog (prog_id, 4096, nullptr, log);

                logError ("failed to link %s: %s", name, log);
                return false;
            }
#endif

            for (unsigned i = 0; shaders[i] != '\0'; ++i)
            {
                glDetachShader (prog_id, s[i]);
            }

            return true;
        }

        static shader get_shader (const char* name, char ext)
        {
            char buf[4096];
            shader s (0);

            switch (ext)
            {
            case 'v':
                if (snprintf (buf, 4096, "%s.vert", name) == 4095)
                {
                    logError ("insufficient buffer size of 4096 for snprintf(3)");
                }
                else
                {
                    s.load (buf, GL_VERTEX_SHADER);
                }
                return s;

            case 'g':
                if (snprintf (buf, 4096, "%s.geom", name) == 4095)
                {
                    logError ("insufficient buffer size of 4096 for snprintf(3)");
                }
                else
                {
                    s.load (buf, GL_GEOMETRY_SHADER);
                }
                return s;

            case 'f':
                if (snprintf (buf, 4096, "%s.frag", name) == 4095)
                {
                    logError ("insufficient buffer size of 4096 for snprintf(3)");
                }
                else
                {
                    s.load (buf, GL_FRAGMENT_SHADER);
                }
                return s;

            default:
                logError ("invalid shader type passed (%c)", ext);
                return s;
            }
        }

    private:
        GLuint prog_id;
    };
};

#endif /* _PROG_H */
