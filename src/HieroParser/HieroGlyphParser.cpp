#include "HieroEvents.h"
#include <Container/String.h>
#include <Container/StringStream.h>

#include <stdexcept>

using Cellwars::HieroGlyphEvent;
using Cellwars::String;
using Cellwars::InputStringStream;
using Cellwars::OutputStringStream;

class HieroGlyphXWatcher : public Cellwars::EventWatcher<HieroGlyphEvent>
{
public:
    virtual bool Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroGlyphXWatcher> reg;
};

bool HieroGlyphXWatcher::Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx)
{
    if (e.name != "x") return false;

    InputStringStream ss (e.value);
    ss >> ctx.pos.botleft.x;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroGlyphParser: Failed to parse " << e.value << " as x position of glyph";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroGlyphXWatcher> HieroGlyphXWatcher::reg;

class HieroGlyphYWatcher : public Cellwars::EventWatcher<HieroGlyphEvent>
{
public:
    virtual bool Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroGlyphYWatcher> reg;
};

bool HieroGlyphYWatcher::Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx)
{
    if (e.name != "y") return false;

    InputStringStream ss (e.value);
    ss >> ctx.pos.botleft.y;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroGlyphParser: Failed to parse " << e.value << " as y position of glyph";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroGlyphYWatcher> HieroGlyphYWatcher::reg;

class HieroGlyphWidthWatcher : public Cellwars::EventWatcher<HieroGlyphEvent>
{
public:
    virtual bool Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroGlyphWidthWatcher> reg;
};

bool HieroGlyphWidthWatcher::Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx)
{
    if (e.name != "width") return false;

    InputStringStream ss (e.value);
    ss >> ctx.pos.width;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroGlyphParser: Failed to parse " << e.value << " as width of glyph";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroGlyphWidthWatcher> HieroGlyphWidthWatcher::reg;

class HieroGlyphHeightWatcher : public Cellwars::EventWatcher<HieroGlyphEvent>
{
public:
    virtual bool Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroGlyphHeightWatcher> reg;
};

bool HieroGlyphHeightWatcher::Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx)
{
    if (e.name != "height") return false;

    InputStringStream ss (e.value);
    ss >> ctx.pos.height;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroGlyphParser: Failed to parse " << e.value << " as height of glyph";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroGlyphHeightWatcher> HieroGlyphHeightWatcher::reg;

class HieroGlyphXOffsetWatcher : public Cellwars::EventWatcher<HieroGlyphEvent>
{
public:
    virtual bool Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroGlyphXOffsetWatcher> reg;
};

bool HieroGlyphXOffsetWatcher::Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx)
{
    if (e.name != "xoffset") return false;

    InputStringStream ss (e.value);
    ss >> ctx.offset.x;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroGlyphParser: Failed to parse " << e.value << " as xoffset of glyph";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroGlyphXOffsetWatcher> HieroGlyphXOffsetWatcher::reg;

class HieroGlyphYOffsetWatcher : public Cellwars::EventWatcher<HieroGlyphEvent>
{
public:
    virtual bool Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroGlyphYOffsetWatcher> reg;
};

bool HieroGlyphYOffsetWatcher::Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx)
{
    if (e.name != "yoffset") return false;

    InputStringStream ss (e.value);
    ss >> ctx.offset.y;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroGlyphParser: Failed to parse " << e.value << " as yoffset of glyph";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroGlyphYOffsetWatcher> HieroGlyphYOffsetWatcher::reg;

class HieroGlyphXAdvanceWatcher : public Cellwars::EventWatcher<HieroGlyphEvent>
{
public:
    virtual bool Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroGlyphXAdvanceWatcher> reg;
};

bool HieroGlyphXAdvanceWatcher::Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx)
{
    if (e.name != "xadvance") return false;

    InputStringStream ss (e.value);
    ss >> ctx.xadvance;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroGlyphParser: Failed to parse " << e.value << " as xadvance of glyph";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroGlyphXAdvanceWatcher> HieroGlyphXAdvanceWatcher::reg;

class HieroGlyphIdWatcher : public Cellwars::EventWatcher<HieroGlyphEvent>
{
public:
    virtual bool Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroGlyphIdWatcher> reg;
};

bool HieroGlyphIdWatcher::Catch (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context& ctx)
{
    if (e.name != "id") return false;

    InputStringStream ss (e.value);
    ss >> ctx.id;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "HieroGlyphParser: Failed to parse " << e.value << " as id of glyph";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroGlyphIdWatcher> HieroGlyphIdWatcher::reg;

template <>
void Cellwars::EventMaster<HieroGlyphEvent>::UnregisteredEventCallback (const HieroGlyphEvent::Type& e, HieroGlyphEvent::Context&)
{
    ThrowIfUnregisteredOption (e);
}
