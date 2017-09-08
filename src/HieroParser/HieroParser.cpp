#include "HieroParser.h"
#include <Container/Algorithm.h>
#include <Container/String.h>
#include <Container/StringStream.h>
#include <Misc/SourceFile.h>
#include <logger/logger.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "HieroHeaderParser.cpp"
#include "HieroGlyphParser.cpp"
#include "HieroCharCountParser.cpp"
#include "HieroContentsParser.cpp"

#include <fstream>

using Cellwars::HieroParser;
using Cellwars::Vector;
using Cellwars::OutputStringStream;
using Cellwars::LocalPtr;
using Cellwars::Font;

HieroParser::HieroParser (const char* path)
{
    Load (path);
}

bool HieroParser::IsLoaded ()
{
    return tex_data && !v_glyph.Empty () && !v_indices.Empty ();
}

unsigned HieroParser::GetTexWidth ()
{
    return tex_width;
}

unsigned HieroParser::GetTexHeight ()
{
    return tex_height;
}

GLenum HieroParser::GetTexFormat ()
{
    return tex_format;
}

GLenum HieroParser::GetTexType ()
{
    return tex_type;
}

LocalPtr<unsigned char> HieroParser::ReleaseTexData ()
{
    return std::move (tex_data);
}

Vector<Font::Glyph> HieroParser::ReleaseGlyphVector ()
{
    return std::move (v_glyph);
}

Vector<unsigned> HieroParser::ReleaseIndicesVector ()
{
    return std::move (v_indices);
}

void HieroParser::Load (const char* path)
{
    try
    {
        Load_Impl (path);
    }
    catch (...)
    {
        Clear ();
        throw;
    }
}

void HieroParser::Clear ()
{
    tex_data.Clear ();
    v_glyph.Clear ();
    v_indices.Clear ();
}

void HieroParser::Load_Impl (const char* path)
{
    HieroContents contents;

    std::ifstream file (path);
    if (!file)
    {
        OutputStringStream ss;
        ss << "Error while opening " << path << " for writing";

        throw std::runtime_error (ss.CStr ());
    }

    while (file)
    {
        String line;
        Getline (file, line);
        if (file.rdstate () == std::ios_base::failbit) file.clear ();

        EventMaster<HieroContentsEvent>::CatchEvent (line, contents);
    }

    if (!file.eof ())
    {
        OutputStringStream ss;
        ss << "HerioParser: did not finish reading file " << path;

        throw std::runtime_error (ss.CStr ());
    }

    String tex_name (path);
    tex_name = tex_name.Substr (0, tex_name.FindLastOf ('/') + 1);
    tex_name += contents.header.tex_name;
    contents.header.tex_name.Swap (tex_name);

    InterpretHieroContents (contents);

    FlipImage ();
    FlipTexCoord ();
    FixXAdvance (contents.header.glyph_padding);
}

void HieroParser::FlipImage () // TODO: only 4 channel support
{
    unsigned char* img = tex_data.GetPtr ();
    unsigned mid_rol = GetTexHeight () / 2;

    for (unsigned rol = 0; rol < mid_rol; ++rol)
    {
        unsigned sym_rol = GetTexHeight () - 1 - rol;
        for (unsigned col = 0; col < GetTexWidth (); ++col)
        {
            unsigned up_idx = (rol * GetTexWidth () + col) * 4;
            unsigned down_idx = (sym_rol * GetTexWidth () + col) * 4;

            Swap (img[up_idx], img[down_idx]);
            Swap (img[up_idx + 1], img[down_idx + 1]);
            Swap (img[up_idx + 2], img[down_idx + 2]);
            Swap (img[up_idx + 3], img[down_idx + 3]);
        }
    }
}

void HieroParser::FlipTexCoord ()
{
    for (unsigned i = 0; i < v_glyph.Size (); ++i)
    {
        v_glyph[i].pos.botleft.y += v_glyph[i].pos.height;
        v_glyph[i].pos.botleft.y = GetTexHeight () - v_glyph[i].pos.botleft.y;
        v_glyph[i].offset.y = -v_glyph[i].offset.y - v_glyph[i].pos.height;
    }
}

void HieroParser::FixXAdvance (unsigned padding)
{
    for (unsigned i = 0; i < v_glyph.Size (); ++i)
    {
        v_glyph[i].xadvance -= padding * 2;
    }
}

void HieroParser::InterpretHieroContents (HieroContents& contents)
{
    if (contents.v_glyphs.Size () < contents.chars.cnt)
    {
        OutputStringStream ss;
        ss << "HieroParser: char_count is " << contents.chars.cnt << " but only ";
        ss << contents.v_glyphs.Size () << " glyphs sources";

        throw std::runtime_error (ss.CStr ());
    }
    contents.v_glyphs.Resize (contents.chars.cnt);

    InterpretHieroHeader (contents.header);
    InterpretHieroVGlyphs (contents.v_glyphs);
}

void HieroParser::InterpretHieroHeader (HieroHeader& header)
{
    tex_width = header.tex_width;
    tex_height = header.tex_height;
    tex_format = header.tex_format;
    tex_type = header.tex_type;

    int x, y, channels;
    tex_data = stbi_load (header.tex_name.CStr (), &x, &y, &channels, 0);
    if (!tex_data)
    {
        throw std::runtime_error (stbi_failure_reason ());
    }
    tex_data.SetDeleter (stbi_image_free);

    logAssert ((unsigned)x == GetTexWidth ());
    logAssert ((unsigned)y == GetTexHeight ());
    logAssert (channels == 4); // TODO Only RGBA supported
}

void HieroParser::InterpretHieroVGlyphs (Vector<HieroGlyph>& v)
{
    unsigned max_id = v[0].id;
    for (unsigned i = 1; i < v.Size (); ++i)
    {
        max_id = Max (v[i].id, max_id);
    }

    v_indices.Resize (max_id + 1);
    Fill (v_indices.Begin (), v_indices.MaxSize (), v_indices.Size ());
    v_glyph.Resize (v.Size ());

    for (unsigned i = 0; i < v.Size (); ++i)
    {
        v_glyph[i].pos = v[i].pos;
        v_glyph[i].offset = v[i].offset;
        v_glyph[i].xadvance = v[i].xadvance;

        logAssert (v_indices[v[i].id] == v_indices.MaxSize ());
        v_indices[v[i].id] = i;
    }
}
