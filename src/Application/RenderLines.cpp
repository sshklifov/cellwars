#include "RenderGeometry.h"
#include "Arena.h"

#include <RenderUtils/GlfwInit.h>
#include <RenderUtils/Matrices.h>
#include <Epsilon/Utility.h>
#include <cstring>

using Cellwars::RenderLines;
using Cellwars::GlfwInit;

constexpr float RenderLines::line_spacing;
constexpr float RenderLines::min_line_spacing;
constexpr char RenderLines::string_id[];

static constexpr unsigned CalculateMaxVertices ()
{
    constexpr unsigned max_width = 1980; // TODO
    constexpr unsigned max_height = 1080; // TODO

    constexpr unsigned max_lines_vert = max_height / RenderLines::min_line_spacing + 1;
    constexpr unsigned max_lines_horz = max_width / RenderLines::min_line_spacing + 1;
    constexpr unsigned max_vertices = (max_lines_vert + max_lines_horz) * 2;

    return max_vertices;
}

RenderLines::RenderLines ()
{
    const char* LINES_PROG_NAME = "res/shaders/gamefield";
    const char* LINES_PROG_SHADERS = "vf";

    vao.Load ();
    vbo.Load ();

    glBindVertexArray (vao[VAO_LINES]);
    glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_LINES]);
    glBufferData (GL_ARRAY_BUFFER, CalculateMaxVertices () * sizeof (FPoint2), NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (FPoint2), (GLvoid*)0);
    glEnableVertexAttribArray (0);

    prog.Load (LINES_PROG_NAME, LINES_PROG_SHADERS);
}

void RenderLines::Render ()
{
    // Inverse transformation:
    float view_width = GlfwInit().GetInstance().GetWidth() / Matrices::GetInstance().GetScaleMatrix()[0][0];
    float view_height = GlfwInit().GetInstance().GetHeight() / Matrices::GetInstance().GetScaleMatrix()[1][1];
    FVec2 v (view_width / 2.f, view_height / 2.f);

    FPoint2 player_pos = RenderGeometryContainer::GetPlayer()->GetCenter();
    
    FPoint2 lower_left = Translate (player_pos, -v);
    Arena::GetInstance().Clamp (lower_left);

    FPoint2 upper_right = Translate (player_pos, v);
    Arena::GetInstance().Clamp (upper_right);

    lower_left.x = line_spacing * glm::floor (lower_left.x / line_spacing);
    lower_left.y = line_spacing * glm::floor (lower_left.y / line_spacing);

    glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_LINES]);
    FPoint2* buf = (FPoint2*)glMapBuffer (GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    logAssert (buf != NULL);
    unsigned size = 0;

    for (float vert_x = lower_left.x; IsLess (vert_x, upper_right.x); vert_x+=line_spacing)
    {
        logAssert (size != CalculateMaxVertices ());
        buf[size++] = FPoint2 (vert_x, lower_left.y);
        logAssert (size != CalculateMaxVertices ());
        buf[size++] = FPoint2 (vert_x, upper_right.y);
    }
    for (float horz_y = lower_left.y; IsLess (horz_y, upper_right.y); horz_y+=line_spacing)
    {
        logAssert (size != CalculateMaxVertices ());
        buf[size++] = FPoint2 (lower_left.x, horz_y);
        logAssert (size != CalculateMaxVertices ());
        buf[size++] = FPoint2 (upper_right.x, horz_y);
    }

    glUnmapBuffer (GL_ARRAY_BUFFER);
    glBindVertexArray (vao[VAO_LINES]);
    glUseProgram (prog);
    glDrawArrays (GL_LINES, 0, size);
}

bool RenderLines::Identify (const char* s) const
{
    return strcmp (s, string_id) == 0;
}

float RenderLines::Priority () const
{
    return 0.f;
}
