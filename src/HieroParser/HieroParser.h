#ifndef HIEARO_PARSER_INCLUDED
#define HIEARO_PARSER_INCLUDED

#include "HieroEvents.h"
#include <RenderUtils/Font.h>
#include <Misc/LocalPtr.h>

namespace Cellwars
{
    class HieroParser : public Font::Builder
    {
    public:
        HieroParser () = default;
        HieroParser (const char* path);

        HieroParser (const Builder&) = delete;
        void operator= (const Builder&) = delete;

        virtual void Load (const char* path) override;
        virtual bool IsLoaded () override;
        virtual unsigned GetTexWidth () override;
        virtual unsigned GetTexHeight () override;
        virtual GLenum GetTexFormat () override;
        virtual GLenum GetTexType () override;
        virtual LocalPtr<unsigned char> ReleaseTexData () override;
        virtual Vector<Font::Glyph> ReleaseGlyphVector () override;
        virtual Vector<unsigned> ReleaseIndicesVector () override;

    private:
        void LoadImpl (const char* path);
        void Clear ();

        void InterpretHieroContents (HieroContents& ctx);
        void InterpretHieroHeader (HieroHeader& header);
        void InterpretHieroCharCount (HieroCharCount& chars);
        void InterpretHieroVGlyphs (Vector<HieroGlyph>& v_glyph);

        void FlipImage ();
        void FlipTexCoord ();
        void FixXAdvance (unsigned padding);

    private:
        unsigned tex_width;
        unsigned tex_height;
        GLenum tex_format;
        GLenum tex_type;
        LocalPtr<unsigned char> tex_data;
        Vector<Font::Glyph> v_glyph;
        Vector<unsigned> v_indices;
    };
};

#endif /* HIERO_PARSER_INCLUDED */
