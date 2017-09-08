#ifndef HIERO_EVENTS_INCLUDED
#define HIERO_EVENTS_INCLUDED

#include "Events.h"

#include <glad/glad.h>
#include <Container/String.h>
#include <Container/Iterator.h>
#include <Container/Algorithm.h>
#include <Epsilon/Box.h>
#include <Epsilon/Vec.h>

namespace Cellwars
{
    struct HieroOption
    {
        Cellwars::String name;
        Cellwars::String value;
    };

    struct HieroHeader
    {
        Cellwars::String tex_name;
        unsigned glyph_padding;
        unsigned tex_width;
        unsigned tex_height;
        GLenum tex_format;
        GLenum tex_type;
    };

    struct HieroHeaderEvent
    {
        using Type = HieroOption;
        using Context = HieroHeader;
    };

    struct HieroGlyph
    {
        UBox pos;
        IVec2 offset;
        unsigned xadvance;
        unsigned id;
    };

    struct HieroGlyphEvent
    {
        using Type = HieroOption;
        using Context = HieroGlyph;
    };

    struct HieroCharCount
    {
        unsigned cnt;
    };

    struct HieroCharCountEvent
    {
        using Type = HieroOption;
        using Context = HieroCharCount;
    };

    struct HieroContents
    {
        HieroHeader header;
        HieroCharCount chars;
        Vector<HieroGlyph> v_glyphs;
    };

    struct HieroContentsEvent
    {
        using Type = Cellwars::String;
        using Context = HieroContents;
    };

    void ThrowIfUnregisteredOption (const HieroOption& e);
    unsigned ParseSectionName (String& res, const String& str, unsigned pos = 0);
    unsigned ParseOption (HieroOption& res, const String& str, unsigned pos = 0);

    template <typename Pair, size_t N>
    int FindFirstOfInPair (const Pair (&arr)[N], const typename Pair::first_type& key)
    {
        RandomAccessIterator<const Pair> first = CBegin (arr);
        RandomAccessIterator<const Pair> last = CEnd (arr);
        RandomAccessIterator<const Pair> it = Find (first, last, key,
                [](const Pair& elem, const typename Pair::first_type& key)
                {
                    return key == elem.first;
                });

        return it != last ? it - first : -1;
    }

    template <typename Event>
    void CatchTokensForEvent (const String& str, typename Event::Context& ctx)
    {
        HieroOption opt;
        unsigned pos = ParseOption (opt, str);

        while (!opt.name.Empty ())
        {
            EventMaster<Event>::CatchEvent (opt, ctx);

            pos = ParseOption (opt, str, pos);
        }
    }
};

#endif /* HIERO_EVENTS_INCLUDED */
