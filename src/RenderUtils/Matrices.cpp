#include "Matrices.h"
#include "GlfwInit.h"
#include "GladInit.h"

#include <Epsilon/Utility.h>
#include <glad/glad.h>
#include <logger/logger.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using Cellwars::Matrices;
using Singleton = Matrices::Singleton;

constexpr unsigned Matrices::binding_point;
constexpr char Matrices::block_name[];

constexpr unsigned Singleton::matrix_total;
constexpr unsigned Singleton::matrix_sizeof;

Singleton& Matrices::GetInstance ()
{
    static Singleton instance;
    return instance;
}

#include <cstring>
void Matrices::RegisterProgram (GLuint prog)
{
    logAssert (GetInstance().IsLoaded ());

    GLint ubo_prog_loc = glGetUniformBlockIndex (prog, block_name);
    glUniformBlockBinding (prog, ubo_prog_loc, binding_point);
}

Singleton::Singleton () : update_bitfield (0)
{
    logAssert (GlfwInit::GetInstance().IsLoaded ());
    logAssert (GladInit::GetInstance().IsLoaded ());

    glGenBuffers (1, &ubo);
    glBindBufferBase (GL_UNIFORM_BUFFER, binding_point, ubo);
    glBufferData (GL_UNIFORM_BUFFER, matrix_sizeof * matrix_total, NULL, GL_DYNAMIC_DRAW);

    float width = GlfwInit::GetInstance().GetWidth ();
    float height = GlfwInit::GetInstance().GetHeight ();

    SetProjectionMatrix (glm::ortho (0.f, width, 0.f, height));
    SetScaleMatrix (glm::mat4 (1.f));
    SetTranslateMatrix (glm::mat4 (1.f));

    CoherentUpdate ();
}

Singleton::~Singleton ()
{
    glDeleteBuffers (1, &ubo);
    ubo = 0;
}

const glm::mat4& Singleton::GetProjectionMatrix () const
{
    return projection;
}

const glm::mat4& Singleton::GetScaleMatrix () const
{
    return scale;
}

const glm::mat4& Singleton::GetTranslateMatrix () const
{
    return translate;
}

void Singleton::SetProjectionMatrix (const glm::mat4& m)
{
    projection = m;
    update_bitfield |= PROJECTION;
    update_bitfield |= MVP;
}

void Singleton::SetScaleMatrix (const glm::mat4& m)
{
    scale = m;
    update_bitfield |= SCALE;
    update_bitfield |= MVP;
}

void Singleton::SetTranslateMatrix (const glm::mat4& m)
{
    translate = m;
    update_bitfield |= TRANSLATE;
    update_bitfield |= MVP;
}

void Singleton::CoherentUpdate ()
{
    if (!update_bitfield) return;

    glBindBufferBase (GL_UNIFORM_BUFFER, Matrices::binding_point, ubo);
    float* buf = (float*)glMapBuffer (GL_UNIFORM_BUFFER, GL_WRITE_ONLY);

    if (update_bitfield & SCALE)
    {
        constexpr unsigned offset = 0;
        memcpy (buf + offset, glm::value_ptr (scale), matrix_sizeof);
    }
    if (update_bitfield & PROJECTION)
    {
        constexpr unsigned offset = 16;
        memcpy (buf + offset, glm::value_ptr (projection), matrix_sizeof);
    }
    if (update_bitfield & TRANSLATE)
    {
        constexpr unsigned offset = 32;
        memcpy (buf + offset, glm::value_ptr (translate), matrix_sizeof);
    }
    if (update_bitfield & MVP)
    {
        glm::mat4 mvp = GetScaleMatrix () * GetProjectionMatrix () * GetTranslateMatrix ();

        constexpr unsigned offset = 48;
        memcpy (buf + offset, glm::value_ptr (mvp), matrix_sizeof);
    }

    glUnmapBuffer (GL_UNIFORM_BUFFER);
    update_bitfield = 0;
}

bool Singleton::IsLoaded () const
{
    return ubo != 0;
}
