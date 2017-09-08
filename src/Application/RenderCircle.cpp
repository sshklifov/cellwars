#include "RenderGeometry.h"
#include <RenderUtils/Matrices.h>

#include <cstring>

using Cellwars::RenderCircle;
using Cellwars::Circle;
using Cellwars::FPoint2;
using Cellwars::FVec3;
using Cellwars::FVec2;

constexpr char RenderCircle::string_id[];
constexpr unsigned RenderCircle::max_circles;

RenderCircle::RenderCircle (const FCircle& c, const FVec3& colour, const char* s) : c (c), colour (colour), name (s)
{
    const char* CIRCLE_PROG_NAME = "res/shaders/circle";
    const char* CIRCLE_PROG_SHADERS = "vfg";

    vao.Load ();
    vbo.Load ();

    glBindVertexArray (vao[VAO_CIRCLE]);
    glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_CIRCLE]);
    glBufferData (GL_ARRAY_BUFFER, sizeof (VertexShaderData) * max_circles, NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, sizeof (VertexShaderData), (GLvoid*)0);
    glEnableVertexAttribArray (0);
    glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, sizeof (VertexShaderData), (GLvoid*)12);
    glEnableVertexAttribArray (1);
    glVertexAttribPointer (2, 1, GL_FLOAT, GL_FALSE, sizeof (VertexShaderData), (GLvoid*)20);
    glEnableVertexAttribArray (2);

    prog.Load (CIRCLE_PROG_NAME, CIRCLE_PROG_SHADERS);
    Matrices::RegisterProgram (prog);
}

void RenderCircle::Render ()
{
    glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_CIRCLE]);
    VertexShaderData* buf = (VertexShaderData*)glMapBuffer (GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    logAssert (buf != NULL);

    buf->colour = colour;
    buf->center = c.center;
    buf->rad = c.rad;

    glUnmapBuffer (GL_ARRAY_BUFFER);
    glBindVertexArray (vao[VAO_CIRCLE]);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram (prog);
    glDrawArrays (GL_POINTS, 0, 1);
}


float RenderCircle::GetRad () const
{
    return c.rad;
}

void RenderCircle::SetRad (float rad)
{
    c.rad = rad;
}

const FPoint2& RenderCircle::GetCenter () const
{
    return c.center;
}

void RenderCircle::SetCenter (const FPoint2& center)
{
    c.center = center;
}

const FVec3& RenderCircle::GetColour () const
{
    return colour;
}

void RenderCircle::SetColour (const FVec3& colour)
{
    this->colour = colour;
}

const char* RenderCircle::GetName () const
{
    return name.CStr ();
}

void RenderCircle::SetName (const char* s)
{
    name = s;
}

bool RenderCircle::Identify (const char* s) const
{
    return strcmp (s, string_id) == 0;
}

float RenderCircle::Priority () const
{
    return c.rad;
}
