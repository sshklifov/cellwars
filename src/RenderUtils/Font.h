#ifndef FONT_INCLUDED
#define FONT_INCLUDED

#include "ArrayObjects.h"
#include "Program.h"

#include <glad/glad.h>
#include <Epsilon/Box.h>
#include <Epsilon/Vec.h>
#include <Misc/NewPtr.h>
#include <Container/BoolVector.h>

namespace Cellwars
{
    class Font
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

    private:
        struct VertexShaderData
        {
            UBox texture_box;
            FBox screen_box;
        };

    private:
        enum {VAO_TEXT, VAO_CNT};
        enum {VBO_TEXT, VBO_CNT};
        enum {TEX_TEXT, TEX_CNT};

    public:
        Font () = default;
        Font (NewPtr<Builder> p);
        Font (Font&&) = default;
        Font& operator= (Font&&) = default;

        Font (const Font&) = delete;
        void operator= (const Font&) = delete;

        void Load (NewPtr<Builder> p);
        bool IsLoaded () const;
        void Clear ();

        bool HasGlyph (unsigned id) const;
        const Glyph& operator[] (unsigned id) const;

        unsigned GetTexWidth () const;
        unsigned GetTexHeight () const;
        GLenum GetTexType () const;
        GLenum GetTexFormat () const;
        const unsigned char* GetTex () const;

        void ClearTex ();
        void ClearMetadata ();

        FVec2 RenderText (FVec2 origin, const char* text) const;

    private:
        void LoadImpl (NewPtr<Builder> p);
        void LoadOpenGLSpecifics ();

    private:
        Vector<Glyph> v_glyph;
        Vector<unsigned> v_indices;

        LocalPtr<unsigned char> tex_data;
        unsigned tex_width;
        unsigned tex_height;

        GLenum tex_format;
        GLenum tex_type;

    private:
        Cellwars::VboArray<1> vbo;
        Cellwars::VaoArray<1> vao;
        Cellwars::TexArray<1> tex;
        Cellwars::Program prog;

    public:
        static constexpr unsigned max_text_len = 1024;
    };

    class Font::Builder
    {
    public:
        virtual ~Builder () {}
        virtual void Load (const char* path) = 0;
        virtual bool IsLoaded () = 0;

        virtual unsigned GetTexWidth () = 0;
        virtual unsigned GetTexHeight () = 0;
        virtual GLenum GetTexFormat () = 0;
        virtual GLenum GetTexType () = 0;
        virtual LocalPtr<unsigned char> ReleaseTexData () = 0;
        virtual Vector<Font::Glyph> ReleaseGlyphVector () = 0;
        virtual Vector<unsigned> ReleaseIndicesVector () = 0;
    };
};

#endif /* FONT_INCLUDED */
