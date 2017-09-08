#include "HieroEvents.h"
#include <Container/String.h>
#include <Container/StringStream.h>

#include <utility>
#include <stdexcept>

using Cellwars::HieroHeaderEvent;
using Cellwars::String;
using Cellwars::InputStringStream;
using Cellwars::OutputStringStream;

class HieroHeaderNameWatcher : public Cellwars::EventWatcher<HieroHeaderEvent>
{
public:
    virtual bool Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroHeaderNameWatcher> reg;
};

bool HieroHeaderNameWatcher::Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx)
{
    if (e.name != "name") return false;

    ctx.tex_name = e.value;
    return true;
}

Cellwars::EventRegisterer<HieroHeaderNameWatcher> HieroHeaderNameWatcher::reg;

class HieroHeaderPaddingWatcher : public Cellwars::EventWatcher<HieroHeaderEvent>
{
public:
    virtual bool Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroHeaderPaddingWatcher> reg;
};

bool HieroHeaderPaddingWatcher::Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx)
{
    if (e.name != "padding") return false;

    InputStringStream ss (e.value);
    ss >> ctx.glyph_padding;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroHeaderParser: Failed to parse \'" << e.value << "\' as padding for texture";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroHeaderPaddingWatcher> HieroHeaderPaddingWatcher::reg;

class HieroHeaderWidthWatcher : public Cellwars::EventWatcher<HieroHeaderEvent>
{
public:
    virtual bool Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroHeaderWidthWatcher> reg;
};

bool HieroHeaderWidthWatcher::Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx)
{
    if (e.name != "width") return false;

    InputStringStream ss (e.value);
    ss >> ctx.tex_width;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroHeaderParser: Failed to parse \'" << e.value << "\' as width for texture";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroHeaderWidthWatcher> HieroHeaderWidthWatcher::reg;

class HieroHeaderHeightWatcher : public Cellwars::EventWatcher<HieroHeaderEvent>
{
public:
    virtual bool Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroHeaderHeightWatcher> reg;
};

bool HieroHeaderHeightWatcher::Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx)
{
    if (e.name != "height") return false;

    InputStringStream ss (e.value);
    ss >> ctx.tex_height;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroHeaderParser: Failed to parse \'" << e.value << "\' as height for texture";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroHeaderHeightWatcher> HieroHeaderHeightWatcher::reg;

class HieroHeaderFormatWatcher : public Cellwars::EventWatcher<HieroHeaderEvent>
{
public:
    virtual bool Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroHeaderFormatWatcher> reg;
};

bool HieroHeaderFormatWatcher::Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx)
{
    if (e.name != "format") return false;

    std::pair<String, GLenum> available_formats[] = 
    {
        std::make_pair (String ("rgba"), GL_RGBA)
    };
    int idx = Cellwars::FindFirstOfInPair (available_formats, e.value);

    if (idx == -1)
    {
        OutputStringStream ss;
        ss << "HieroHeaderParser: Unrecognized format " << e.value;

        throw std::runtime_error (ss.CStr ());
    }

    ctx.tex_format = available_formats[idx].second;
    return true;
}

Cellwars::EventRegisterer<HieroHeaderFormatWatcher> HieroHeaderFormatWatcher::reg;

class HieroHeaderTypeWatcher : public Cellwars::EventWatcher<HieroHeaderEvent>
{
public:
    virtual bool Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroHeaderTypeWatcher> reg;
};

bool HieroHeaderTypeWatcher::Catch (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context& ctx)
{
    if (e.name != "type") return false;

    std::pair<String, GLenum> available_types[] = 
    {
        std::make_pair (String ("byte"), GL_UNSIGNED_BYTE)
    };
    int idx = Cellwars::FindFirstOfInPair (available_types, e.value);

    if (idx == -1)
    {
        OutputStringStream ss;
        ss << "HieroHeaderParser: Unrecognized type " << e.value;

        throw std::runtime_error (ss.CStr ());
    }

    ctx.tex_type = available_types[idx].second;
    return true;
}

Cellwars::EventRegisterer<HieroHeaderTypeWatcher> HieroHeaderTypeWatcher::reg;

template <>
void Cellwars::EventMaster<HieroHeaderEvent>::UnregisteredEventCallback (const HieroHeaderEvent::Type& e, HieroHeaderEvent::Context&)
{
    ThrowIfUnregisteredOption (e);
}
