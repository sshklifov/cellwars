#include "RenderGeometry.h"
#include <RenderUtils/Matrices.h>

#include <cstring>

using Cellwars::RenderBlob;
using Cellwars::Circle;
using Cellwars::FPoint2;
using Cellwars::FVec3;
using Cellwars::FVec2;

constexpr char RenderBlob::string_id[];
constexpr unsigned RenderBlob::max_blobs;
constexpr unsigned RenderBlob::blob_rad;

RenderBlob::RenderBlob (const FPoint2& pos, const FVec3& colour) : pos (pos), colour (colour)
{
    const char* CIRCLE_PROG_NAME = "res/shaders/blob";
    const char* CIRCLE_PROG_SHADERS = "vfg";

    vao.Load ();
    vbo.Load ();

    glBindVertexArray (vao[VAO_BLOB]);
    glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_BLOB]);
    glBufferData (GL_ARRAY_BUFFER, sizeof (VertexShaderData) * max_blobs, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof (VertexShaderData), (GLvoid*)0);
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, sizeof (VertexShaderData), (GLvoid*)12);
    glEnableVertexAttribArray (1);
    glVertexAttribPointer (2, 1, GL_FLOAT, GL_FALSE, sizeof (VertexShaderData), (GLvoid*)20);
    glEnableVertexAttribArray (2);

    prog.Load (CIRCLE_PROG_NAME, CIRCLE_PROG_SHADERS);
    Matrices::RegisterProgram (prog);
}

void RenderBlob::Render ()
{
    glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_BLOB]);
    VertexShaderData* buf = (VertexShaderData*)glMapBuffer (GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    logAssert (buf != NULL);

    buf->colour = colour;
    buf->pos = pos;
    buf->rad = blob_rad;

    glUnmapBuffer (GL_ARRAY_BUFFER);
    glBindVertexArray (vao[VAO_BLOB]);
    glUseProgram (prog);
    glDrawArrays (GL_POINTS, 0, 1);
}

const FPoint2& RenderBlob::GetPos () const
{
    return pos;
}

void RenderBlob::SetPos (const FPoint2& pos)
{
    this->pos = pos;
}

const FVec3& RenderBlob::GetColour () const
{
    return colour;
}

void RenderBlob::SetColour (const FVec3& colour)
{
    this->colour = colour;
}

bool RenderBlob::Identify (const char* s) const
{
    return strcmp (s, "blob") == 0;
}

float RenderBlob::Priority () const
{
    return blob_rad;
}
