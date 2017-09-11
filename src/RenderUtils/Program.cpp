#include "Program.h"
#include "Shader.h"
#include <logger/logger.h>
#include <glad/glad.h>
#include <Container/StringStream.h>
#include <Container/String.h>
#include <Container/Vector.h>

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

void Program::LoadImpl (const char* name, const char* shaders)
{
    id = glCreateProgram ();
    Vector<GLuint> shader_storage;

    try
    {
        LoadShaders (shader_storage, name, shaders);
        AttachShadersAndLink (shader_storage, id);
    }
    catch (std::exception& e)
    {
        DetachShaders (id, shader_storage);

        OutputStringStream ss;
        ss << "failed to create program \'" << name << "\':" << e.what ();
        throw std::runtime_error (ss.CStr ());
    }

    DetachShaders (id, shader_storage);
}

static Vector<GLuint> LoadShaders (Vector<GLuit>& storage, const char* name, const char* shaders)
{
    for (unsigned idx = 0; shaders[idx]; ++idx)
    {
        storage.PushBack (ParseShader (name, shaders[idx]));
    }
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

static AttachShadersAndLink (GLuint program, Vector<GLuint>& shaders)
{
    for (unsigned i = 0; i < shaders.Size (); ++i)
    {
        glAttachShader (program, shaders[i]);
    }

    glLinkProgram (program);
#ifndef NDEBUG
    ThrowIfProgramLinkFailed (program);
#endif
}

static void ThrowIfProgramLinkFailed (GLuint program)
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

static void DetachShaders (GLuint program, Vector<GLuint>& shaders)
{
    for (unsigned idx = 0; idx < shaders.Size (); ++i)
    {
        glDetachShader (program, shaders[i]);
    }
}