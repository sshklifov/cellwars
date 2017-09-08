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
        unsigned pos = 0;
        while (pos != String::Npos)
        {
            HieroOption opt;
            pos = ParseOption (opt, str, pos);

            if (opt.name.Empty ())
            {
                break;
            }

            EventMaster<Event>::CatchEvent (opt, ctx);
        }
    }

#if 1
    class A
    {
    public:
        A ();
        int Get () const;

    private:
        int three = 3;
    };
    extern A a;
#endif
};

#endif /* HIERO_EVENTS_INCLUDED */
