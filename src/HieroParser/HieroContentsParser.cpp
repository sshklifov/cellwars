#include "HieroEvents.h"
#include <Container/String.h>
#include <Container/StringStream.h>

#include <stdexcept>

using Cellwars::HieroContentsEvent;
using Cellwars::String;
using Cellwars::InputStringStream;
using Cellwars::OutputStringStream;

class HieroContentsInfoWatcher : public Cellwars::EventWatcher<HieroContentsEvent>
{
public:
    virtual bool Catch (const HieroContentsEvent::Type& e, HieroContentsEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroContentsInfoWatcher> reg;
};

bool HieroContentsInfoWatcher::Catch (const HieroContentsEvent::Type& e, HieroContentsEvent::Context& ctx)
{
    String name;
    unsigned pos = ParseSectionName (name, e);

    if (name != "info") return false;

    Cellwars::CatchTokensForEvent<Cellwars::HieroHeaderEvent> (e.Substr (pos), ctx.header);
    return true;
}

Cellwars::EventRegisterer<HieroContentsInfoWatcher> HieroContentsInfoWatcher::reg;

class HieroContentsCharWatcher : public Cellwars::EventWatcher<HieroContentsEvent>
{
public:
    virtual bool Catch (const HieroContentsEvent::Type& e, HieroContentsEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroContentsCharWatcher> reg;
};

bool HieroContentsCharWatcher::Catch (const HieroContentsEvent::Type& e, HieroContentsEvent::Context& ctx)
{
    String name;
    unsigned pos = ParseSectionName (name, e);

    if (name != "char") return false;

    // MAJOR TODO
    ctx.v_glyphs.RelativeResize (1);

    //TODO Cellwars::CatchTokensForEvent<Cellwars::HieroGlyphEvent> (e.Substr (pos), ctx.v_glyphs.Front ());
    Cellwars::CatchTokensForEvent<Cellwars::HieroGlyphEvent> (e.Substr (pos), ctx.v_glyphs.Back ());

    return true;
}

Cellwars::EventRegisterer<HieroContentsCharWatcher> HieroContentsCharWatcher::reg;

class HieroContentsCharCountWatcher : public Cellwars::EventWatcher<HieroContentsEvent>
{
public:
    virtual bool Catch (const HieroContentsEvent::Type& e, HieroContentsEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroContentsCharCountWatcher> reg;
};

bool HieroContentsCharCountWatcher::Catch (const HieroContentsEvent::Type& e, HieroContentsEvent::Context& ctx)
{
    String name;
    unsigned pos = ParseSectionName (name, e);

    if (name != "chars") return false;

    Cellwars::CatchTokensForEvent<Cellwars::HieroCharCountEvent> (e.Substr (pos), ctx.chars);
    return true;
}

Cellwars::EventRegisterer<HieroContentsCharCountWatcher> HieroContentsCharCountWatcher::reg;

class HieroContentsEmptyLineWatcher : public Cellwars::EventWatcher<HieroContentsEvent>
{
public:
    virtual bool Catch (const HieroContentsEvent::Type& e, HieroContentsEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroContentsEmptyLineWatcher> reg;
};

bool HieroContentsEmptyLineWatcher::Catch (const HieroContentsEvent::Type& e, HieroContentsEvent::Context&)
{
    String name;
    ParseSectionName (name, e);

    return name.Empty ();
}

Cellwars::EventRegisterer<HieroContentsEmptyLineWatcher> HieroContentsEmptyLineWatcher::reg;

template <>
void Cellwars::EventMaster<HieroContentsEvent>::UnregisteredEventCallback (const HieroContentsEvent::Type& e, HieroContentsEvent::Context&)
{
    OutputStringStream ss;
    ss << "Nobody listening on HieroContentsEvent with name=" << e;

    throw std::runtime_error (ss.CStr ());
}
