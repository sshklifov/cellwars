#include <logger/logger.h>
#include <glad/glad.h>

#include "Program.h"
#include "Shader.h"

#include <cstring>
#include <cstdio>

using Cellwars::Program;
using Cellwars::Shader;

Program::Program ()
{
    id = 0;
}

Program::Program (GLuint id)
{
    this->id = id;
}

Program::Program (const char* name, const char* shaders) : Program ()
{
    Load (name, shaders);
}

Program::Program (Program&& rhs)
{
    id = rhs.id;
    rhs.id = 0;
}

Program::~Program ()
{
    glDeleteProgram (id);
}

Program& Program::operator= (Program&& rhs)
{
    id = rhs.id;
    rhs.id = 0;

    return (*this);
}

bool Program::Load (const char* name, const char* shaders)
{
    bool retval = _Impl_Load (name, shaders);
    if (!retval)
    {
        Clear ();
    }

    return retval;
}

bool Program::IsLoaded () const
{
    return id != 0;
}

void Program::Clear ()
{
    glDeleteProgram (id);
    id = 0;
}

Program::operator GLuint () const
{
    return id;
}


static Shader _ParseShader (const char* name, char ext)
{
    char ext_str[5];
    GLenum type;

    switch (ext)
    {
    case 'v':
        strncpy (ext_str, "vert", 5);
        type = GL_VERTEX_SHADER;
        break;

    case 'g':
        strncpy (ext_str, "geom", 5);
        type = GL_GEOMETRY_SHADER;
        break;

    case 'f':
        strncpy (ext_str, "frag", 5);
        type = GL_FRAGMENT_SHADER;
        break;

    default:
        logError ("invalid shader type passed (%c)", ext);
        return Shader ();
    }

    char buf[4096];
    if (snprintf (buf, 4096, "%s.%s", name, ext_str) >= 4096)
    {
        logError ("insufficient buffer size of 4096 for snprintf(3)");
        return Shader ();
    }

    return Shader (buf, type);
}

static bool _ProgramLinked (GLuint program, const char* name)
{
    /* NOTE: no need to check if linking went OK every time.
     * This is useful only in 'pre-release' when you will still
     * be writing your shaders.
     */
#ifdef NDEBUG
    return true;
#else
    GLint success;
    glGetProgramiv (program, GL_LINK_STATUS, &success);

    if (success == GL_TRUE)
    {
        return true;
    }

    GLint info_log_len;
    glGetProgramiv (program, GL_INFO_LOG_LENGTH, &info_log_len);

    if (info_log_len > 4095)
    {
        logWarnStr ("insufficient buffer size of 4096, truncating");
    }

    char buf[4096];
    glGetProgramInfoLog (program, 4096, NULL, buf);

    logError ("failed to link programme %s; reason:\n%s", name, buf);
    return false;
#endif
}

bool Program::_Impl_Load (const char* name, const char* shaders)
{
    id = glCreateProgram ();

    Shader s[5]; // NOTE: no more than 5 shaders can compose a programme
    for (unsigned i = 0; shaders[i] != '\0'; ++i)
    {
        s[i] = _ParseShader (name, shaders[i]);

        if (!s[i].IsLoaded ())
        {
            return false;
        }

        glAttachShader (id, s[i]);
    }

    glLinkProgram (id);
    bool success = _ProgramLinked (id, name);

    for (unsigned i = 0; shaders[i] != '\0'; ++i)
    {
        glDetachShader (id, s[i]);
    }

    return success;
}
