#include "Atlas.h"
#include "FilePtr.h"

#include <logger/logger.h>

#include <climits>
#include <utility>

using Cellwars::Atlas;
using Glyph = Atlas::Glyph;
using Builder = Atlas::Builder;

Atlas::Atlas ()
{
    has_glyph.Reserve (CHAR_MAX);
    has_glyph.ShrinkToFit ();
}

Atlas::Atlas (Builder* p) : Atlas ()
{
    builder = p;
}

Atlas::Atlas (Atlas&& rhs)
{
    _ShallowCopy (std::move (rhs));
}

Atlas& Atlas::operator= (Atlas&& rhs)
{
    if (this == &rhs) return (*this);

    Clear ();
    _ShallowCopy (std::move (rhs));

    return (*this);
}

const Builder* Atlas::GetBuilder () const
{
    return builder.GetCPtr ();
}

void Atlas::SetBuilder (Builder* p)
{
    builder = p;
}

bool Atlas::Load (const char* metadata)
{
    if (!builder)
    {
        return false;
    }

    // try-catch // TODO
    return builder->Build (metadata, *this);
}

bool Atlas::IsLoaded () const
{
    return glyph_p && tex_data;
}

void Atlas::Clear ()
{
    glyph_p.Release ();
    tex_data.Release ();
}

bool Atlas::HasGlyph (char ascii) const
{
    logAssert (IsLoaded ());

    return has_glyph[(unsigned)ascii];
}

const Glyph& Atlas::operator[] (char ascii) const
{
    return glyph_p[(unsigned)ascii];
}

unsigned Atlas::GetImageWidth () const
{
    return tex_width;
}

unsigned Atlas::GetImageHeight () const
{
    return tex_height;
}

GLenum Atlas::GetTexType () const
{
    return tex_type;
}

GLenum Atlas::GetTexFormat () const
{
    return tex_format;
}

const char* Atlas::GetImage () const
{
    return tex_data.GetCPtr ();
}

void Atlas::_ShallowCopy (Atlas&& rhs)
{
    builder = std::move (rhs.builder);
    glyph_p = std::move (rhs.glyph_p);
    has_glyph = std::move (rhs.has_glyph);
    tex_data = std::move (rhs.tex_data);

    tex_width = rhs.tex_width;
    tex_height = rhs.tex_height;

    rhs.tex_width = 0;
    rhs.tex_height = 0;
}
