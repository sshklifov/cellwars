#include "Font.h"
#include "Matrices.h"
#include "GlfwInit.h"
#include <logger/logger.h>

#include <cstring>

using Cellwars::Font;
using Glyph = Font::Glyph;
using Builder = Font::Builder;

constexpr unsigned Font::max_text_len;

Font::Font (NewPtr<Builder> p)
{
    Load (p.Release ());
}

void Font::Load (NewPtr<Builder> p)
{
    try
    {
        Load_Impl (p.Release ());
    }
    catch (...)
    {
        Clear ();
        throw;
    }

    logDebug ("successfully loaded font");
    ClearTex ();
}

void Font::Load_Impl (NewPtr<Builder> p)
{
    logAssert (!IsLoaded ());
    logAssert (p->IsLoaded ());
        
    v_glyph = p->ReleaseGlyphVector ();
    v_indices = p->ReleaseIndicesVector ();
    tex_data = p->ReleaseTexData ();

    tex_width = p->GetTexWidth ();
    tex_height = p->GetTexHeight ();
    tex_format = p->GetTexFormat ();
    tex_type = p->GetTexType ();

    LoadOpenGLSpecifics ();
}

void Font::LoadOpenGLSpecifics ()
{
    const char* FONT_PROG_NAME = "res/shaders/text"; // TODO: put in parser
    const char* FONT_PROG_SHADERS = "vgf"; // TODO: put in parser

    prog.Load (FONT_PROG_NAME, FONT_PROG_SHADERS);
    Matrices::RegisterProgram (prog);

    vao.Load ();
    vbo.Load ();
    tex.Load ();

    glBindVertexArray (vao[VAO_TEXT]);
    glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_TEXT]);
    glBufferData (GL_ARRAY_BUFFER, max_text_len * sizeof (VertexShaderData), NULL, GL_DYNAMIC_DRAW);

    glVertexAttribIPointer (0, 2, GL_UNSIGNED_INT, sizeof (VertexShaderData), (GLvoid*)offsetof (VertexShaderData, texture_box.botleft));
    glEnableVertexAttribArray (0);
    glVertexAttribIPointer (1, 1, GL_UNSIGNED_INT, sizeof (VertexShaderData), (GLvoid*)offsetof (VertexShaderData, texture_box.width));
    glEnableVertexAttribArray (1);
    glVertexAttribIPointer (2, 1, GL_UNSIGNED_INT, sizeof (VertexShaderData), (GLvoid*)offsetof (VertexShaderData, texture_box.height));
    glEnableVertexAttribArray (2);

    glVertexAttribPointer (3, 2, GL_FLOAT, GL_FALSE, sizeof (VertexShaderData), (GLvoid*)offsetof (VertexShaderData, screen_box.botleft));
    glEnableVertexAttribArray (3);
    glVertexAttribPointer (4, 1, GL_FLOAT, GL_FALSE, sizeof (VertexShaderData), (GLvoid*)offsetof (VertexShaderData, screen_box.width));
    glEnableVertexAttribArray (4);
    glVertexAttribPointer (5, 1, GL_FLOAT, GL_FALSE, sizeof (VertexShaderData), (GLvoid*)offsetof (VertexShaderData, screen_box.height));
    glEnableVertexAttribArray (5);

    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_2D, tex[TEX_TEXT]);
    logAssert (GetTexFormat () == GL_RGBA); // TODO: Only RGBA supported
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, GetTexWidth (), GetTexHeight (), 0, GetTexFormat (), GetTexType (), GetTex ());

    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

bool Font::IsLoaded () const
{
    return prog.IsLoaded (); // any of the OpenGL objects will suffice
}

void Font::Clear ()
{
    ClearTex ();
    ClearMetadata ();

    vbo.Clear ();
    vao.Clear ();
    tex.Clear ();
    prog.Clear ();
}

bool Font::HasGlyph (unsigned id) const
{
    logAssert (IsLoaded ());
    return (id < v_indices.Size ()) && (v_indices[id] != v_glyph.MaxSize ());
}

const Glyph& Font::operator[] (unsigned id) const
{
    logAssert (HasGlyph (id));
    return v_glyph[v_indices[id]];
}

unsigned Font::GetTexWidth () const
{
    return tex_width;
}

unsigned Font::GetTexHeight () const
{
    return tex_height;
}

GLenum Font::GetTexType () const
{
    return tex_type;
}

GLenum Font::GetTexFormat () const
{
    return tex_format;
}

const unsigned char* Font::GetTex () const
{
    return tex_data.GetCPtr ();
}

void Font::ClearTex ()
{
    tex_data.Clear ();
}

void Font::ClearMetadata ()
{
    v_glyph.Clear ();
    v_indices.Clear ();
}

Cellwars::FVec2 Font::RenderText (Cellwars::FVec2 origin, const char* text) const
{
    logAssert (text && (strlen (text) <= max_text_len));

    origin.x *= GlfwInit::GetInstance().GetWidth ();
    origin.y *= GlfwInit::GetInstance().GetHeight ();

    glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_TEXT]);
    VertexShaderData* buf = (VertexShaderData*)glMapBuffer (GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    logAssert (buf != NULL);

    unsigned cnt;
    for (cnt = 0; text[cnt]; ++cnt)
    {
        unsigned id = text[cnt];
        const Glyph& curr_g = operator[] (id);

        buf[cnt].texture_box = curr_g.pos;

        buf[cnt].screen_box.botleft.x = origin.x + curr_g.offset.x;
        buf[cnt].screen_box.botleft.y = origin.y + curr_g.offset.y;
        buf[cnt].screen_box.width = curr_g.pos.width;
        buf[cnt].screen_box.height = curr_g.pos.height;

        origin.x += curr_g.xadvance;
    }

    glUnmapBuffer (GL_ARRAY_BUFFER);
    glBindVertexArray (vao[VAO_TEXT]);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram (prog);
    glActiveTexture (GL_TEXTURE0);
    glBindTexture (GL_TEXTURE_2D, tex[TEX_TEXT]);
    glDrawArrays (GL_POINTS, 0, cnt);
    glDisable (GL_BLEND);

    origin.x /= GlfwInit::GetInstance().GetWidth ();
    origin.y /= GlfwInit::GetInstance().GetHeight ();

    return origin;
}
