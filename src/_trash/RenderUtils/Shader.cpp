#include "Shader.h"
#include "MallocPtr.h"
#include "FilePtr.h"

#include <logger/logger.h>
#include <glad/glad.h>

#include <cstdio>
#include <cstdlib>
#include <utility>

using Cellwars::Shader;
using Cellwars::MallocPtr;
using Cellwars::FilePtr;

Shader::Shader ()
{
    id = 0;
}

Shader::Shader (GLuint id)
{
    this->id = id;
}

Shader::Shader (const char* file, GLenum type) : Shader ()
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

bool Shader::Load (const char* file, GLenum type)
{
    bool retval = _Impl_Load (file, type);
    if (!retval)
    {
        Clear ();
    }

    return retval;
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

static long _TellBytesAndRewind (FILE* fp)
{
    if (fseek (fp, 0, SEEK_END) == -1)
    {
        logError ("failed to seek inside file pointer");
        return -1;
    }

    long bytes = ftell (fp);
    if (bytes == -1)
    {
        logError ("failed to tell position of file pointer");
        return -1;
    }

    rewind (fp);

    return bytes;
}

static char* _SourceFile (const char* file, size_t& size)
{
    FilePtr fp = fopen (file, "rb");

    if (!fp)
    {
        logError ("cannot open for reading file %s", file);
        return NULL;
    }

    long bytes = _TellBytesAndRewind (fp.GetPtr ());
    if (bytes == -1)
    {
        logError ("unable to tell bytes of file %s", file);
        return NULL;
    }

    MallocPtr<char> buf = (char*)malloc (bytes + 1);

    if (!buf)
    {
        logError ("malloc(3) failed");
        return NULL;
    }

    size_t num_read = fread (buf.GetPtr (), 1, bytes, fp.GetPtr ());
    if (num_read != (size_t)bytes)
    {
        logError ("partial/failed read on %s", file);
        return NULL;
    }

    buf.GetPtr ()[bytes] = '\0';
    size = num_read;

    return buf.Release ();
}

static bool _ShaderCompiled (GLuint shader, const char* file)
{
    /* NOTE: no need to check if compiled went OK every time.
     * This is useful only in 'pre-release' when you will still
     * be writing your shaders.
     */

#ifdef NDEBUG
    return true;
#else
    GLint success;
    glGetShaderiv (shader, GL_COMPILE_STATUS, &success);

    if (success == GL_TRUE)
    {
        return true;
    }

    GLint info_log_len;
    glGetShaderiv (shader, GL_INFO_LOG_LENGTH, &info_log_len);

    if (info_log_len > 4095)
    {
        logWarnStr ("insufficient buffer size of 4096, truncating");
    }

    char buf[4096];
    glGetShaderInfoLog (shader, 4096, NULL, buf);

    logError ("failed to compile shader %s; reason:\n%s", file, buf);
    return false;
#endif
}

bool Shader::_Impl_Load (const char* file, GLenum type)
{
    size_t bytes;
    MallocPtr<char> buf = _SourceFile (file, bytes);

    if (!buf)
    {
        return false;
    }

    GLint len = bytes;
    GLchar* strings[1] = {buf.GetPtr ()};

    id = glCreateShader (type);
    glShaderSource (id, 1, strings , &len);
    glCompileShader (id);


    if (!_ShaderCompiled (id, file))
    {
        return false;
    }

    return true;
}
