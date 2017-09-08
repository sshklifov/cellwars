#include "Shader.h"
#include <Container/StringStream.h>
#include <Misc/NewPtr.h>
#include <Misc/SourceFile.h>
#include <logger/logger.h>
#include <glad/glad.h>

#include <stdexcept>

using Cellwars::Shader;
using Cellwars::NewPtr;
using Cellwars::OutputStringStream;

Shader::Shader () : id (0)
{
}

Shader::Shader (GLuint id)
{
    this->id = id;
}

Shader::Shader (const char* file, GLenum type) : id (0)
{
    Load (file, type);
}

Shader::Shader (Shader&& rhs)
{
    id = rhs.id;
    rhs.id = 0;
}

Shader::~Shader ()
{
    glDeleteShader (id);
}

Shader& Shader::operator= (Shader&& rhs)
{
    id = rhs.id;
    rhs.id = 0;

    return (*this);
}

bool Shader::IsLoaded () const
{
    return id != 0;
}

void Shader::Clear ()
{
    glDeleteShader (id);
    id = 0;
}

Shader::operator GLuint () const
{
    return id;
}

void Shader::Load (const char* file, GLenum type)
{
    try
    {
        Load_Impl (file, type);
    }
    catch (...)
    {
        Clear ();
        throw;
    }
}

static void VerifyShaderCompiled (GLuint shader)
{
    GLint success;
    glGetShaderiv (shader, GL_COMPILE_STATUS, &success);

    if (success != GL_TRUE)
    {
        GLint info_log_len;
        glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &info_log_len);

        if (info_log_len > 4095)
        {
            logWarnStr ("insufficient buffer size of 4096, truncating");
        }

        char buf[4096];
        glGetShaderInfoLog (shader, 4096, NULL, buf);
        throw std::runtime_error (buf);
    }
}

void Shader::Load_Impl (const char* file, GLenum type)
{
    logAssert (!IsLoaded ());

    NewPtr<char> buf = SourceFile (file);
    GLchar* strings[1] = {buf.GetPtr ()};

    id = glCreateShader (type);
    glShaderSource (id, 1, strings, NULL);
    glCompileShader (id);

#ifndef NDEBUG
    try
    {
        VerifyShaderCompiled (id);
    }
    catch (std::exception& e)
    {
        OutputStringStream ss;
        ss << "Failed to compile shader \'" << file << "\': " << e.what ();

        throw std::runtime_error (ss.CStr ());
    }
#endif
}
