#include "Program.h"
#include "Shader.h"
#include <logger/logger.h>
#include <glad/glad.h>
#include <Container/StringStream.h>
#include <Container/String.h>

#include <cstring>
#include <stdexcept>

using Cellwars::Program;
using Cellwars::Shader;
using Cellwars::OutputStringStream;
using Cellwars::String;

Program::Program ()
{
    id = 0;
}

Program::Program (GLuint id)
{
    this->id = id;
}

Program::Program (const char* name, const char* shaders) : id (0)
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

void Program::Load (const char* name, const char* shaders)
{
    try
    {
        Load_Impl (name, shaders);
    }
    catch (...)
    {
        Clear ();
        throw;
    }
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


static Shader ParseShader (const char* name, char ext)
{
    String ext_str;
    GLenum type;

    switch (ext)
    {
    case 'v':
        ext_str += "vert";
        type = GL_VERTEX_SHADER;
        break;

    case 'g':
        ext_str += "geom";
        type = GL_GEOMETRY_SHADER;
        break;

    case 'f':
        ext_str += "frag";
        type = GL_FRAGMENT_SHADER;
        break;

    default:
        OutputStringStream ss;
        ss << "invalid shader type passed (" << ext << ")";
        throw std::runtime_error (ss.CStr ());
    }

    OutputStringStream ss;
    ss << name << "." << ext_str;

    return Shader (ss.CStr (), type);
}

static void VerifyProgramLinked (GLuint program)
{
    GLint success;
    glGetProgramiv (program, GL_LINK_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLint info_log_len;
        glGetProgramiv (program, GL_INFO_LOG_LENGTH, &info_log_len);

        if (info_log_len > 4095)
        {
            logWarnStr ("insufficient buffer size of 4096, truncating");
        }

        char buf[4096];
        glGetProgramInfoLog (program, 4096, NULL, buf);

        throw std::runtime_error (buf);
    }
}

void Program::Load_Impl (const char* name, const char* shaders)
{
    id = glCreateProgram ();

    constexpr unsigned MAX_SHADERS = 5;
    Shader s[MAX_SHADERS];
    unsigned idx;

    try
    {
        for (idx = 0; shaders[idx] != '\0'; ++idx)
        {
            s[idx] = ParseShader (name, shaders[idx]);
            glAttachShader (id, s[idx]);
        }

        glLinkProgram (id);
        VerifyProgramLinked (id);
    }
    catch (std::exception& e)
    {
        for (unsigned i = 0; i < idx; ++i)
        {
            glDetachShader (id, s[i]);
            s[i].Clear ();
        }

        OutputStringStream ss;
        ss << "failed to create program \'" << name << "\':" << e.what ();

        throw std::runtime_error (ss.CStr ());
    }

    for (unsigned i = 0; shaders[i] != '\0'; ++i)
    {
        glDetachShader (id, s[i]);
    }
}
