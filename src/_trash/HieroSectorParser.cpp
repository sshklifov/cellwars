#include "Events.h"
#include <Container/Iterator.h>
#include <Container/String.h>
#include <Container/StringStream.h>

#include <stdexcept>
#include <utility>

using Cellwars::String;
using Cellwars::StringStream;
using Cellwars::RandomAccessIterator;

struct HieroOption
{
    String name;
    String value;
};

struct HieroSector
{
    String name;
};

struct HieroSectorEvent
{
    using Type = HieroOption;
    using Context = HieroSector;
};

template <typename Watcher>
struct HieroSectorWatcherRegisterer
{
    HieroSectorWatcherRegisterer ()
    {
        PushWatcher<HieroSectorEvent> (new Watcher);
    }
};

class HieroSectorInfoWatcher : public EventWatcher<HieroSectorEvent>
{
public:
    virtual bool Catch (const HieroSectorEvent::Type& e, HieroSectorEvent::Context& ctx);

private:
    static HieroSectorWatcherRegisterer<HieroSectorInfoWatcher> reg;
};

bool Catch (const HieroSectorEvent::Type& e, HieroSectorEvent::Context& ctx)
{
    if (e.name != String ("info")) return false;

    /* Catch<> (); */
}

class HieroSectorCharsWatcher : public EventWatcher<HieroSectorEvent>
{
public:
    virtual bool Catch (const HieroSectorEvent::Type& e, HieroSectorEvent::Context& ctx);

private:
    static HieroSectorWatcherRegisterer<HieroSectorInfoWatcher> reg;
};

bool HieroSectorCharsWatcher::Catch (const HieroSectorEvent::Type& e, HieroSectorEvent::Context& ctx)
{
    if (e.name != String ("info")) return false;

    ctx.name = e.value;
    return true;
}
