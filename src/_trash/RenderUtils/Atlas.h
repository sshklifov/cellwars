#ifndef _ATLAS_H
#define _ATLAS_H

#include <glad/glad.h>

#include <Epsilon/Box.h>
#include <Epsilon/Vec.h>

#include "MallocPtr.h"
#include "NewPtr.h"
#include "BoolVector.h"

// TODO: REDO

namespace Cellwars
{

    class Atlas
    {
    public:
        class Builder;

    public:
        struct Glyph
        {
            UBox pos;
            IVec2 offset;
            unsigned xadvance;
        };

    public:
        Atlas ();
        Atlas (Builder* p);
        Atlas (const Atlas&) = delete;
        Atlas (Atlas&& rhs);

        void operator= (const Atlas&) = delete;
        Atlas& operator= (Atlas&& rhs);

        const Builder* GetBuilder () const;
        void SetBuilder (Builder* p);

        bool Load (const char* metadata);
        bool IsLoaded () const;

        void Clear ();

        bool HasGlyph (char ascii) const;
        const Glyph& operator[] (char ascii) const;

        unsigned GetTexWidth () const;
        unsigned GetTexHeight () const;
        GLenum GetTexType () const;
        GLenum GetTexFormat () const;
        const char* GetTex () const;

    private:
        void _ShallowCopy (Atlas&& rhs);

    private:
        NewPtr<Builder> builder;

    private:
        MallocPtr<Glyph> glyph_p;
        BoolVector has_glyph;

        MallocPtr<char> tex_data;
        unsigned tex_width;
        unsigned tex_height;

        GLenum tex_format;
        GLenum tex_type;
    };

    class Atlas::Builder
    {
    public:
        virtual unsigned GetTexWidth () = 0;
        virtual unsigned GetTexHeight () = 0;
        virtual GLenum GetTexFormat () = 0;
        virtual GLenum GetTexType () = 0;
        virtual Vector<Atlas::Glyph> ReleaseGlyphVector () = 0;
        virtual BoolVector> ReleaseHasGlyphVector () = 0;
    };
};

#endif /* _ATLAS_H */
