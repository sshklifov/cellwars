#include "HieroEvents.h"
#include <Container/String.h>
#include <Container/StringStream.h>

#include <stdexcept>

using Cellwars::HieroCharCountEvent;
using Cellwars::String;
using Cellwars::OutputStringStream;
using Cellwars::InputStringStream;

class HieroCharCountWatcher : public Cellwars::EventWatcher<HieroCharCountEvent>
{
public:
    virtual bool Catch (const HieroCharCountEvent::Type& e, HieroCharCountEvent::Context& ctx);

private:
    static Cellwars::EventRegisterer<HieroCharCountWatcher> reg;
};

bool HieroCharCountWatcher::Catch (const HieroCharCountEvent::Type& e, HieroCharCountEvent::Context& ctx)
{
    if (e.name != "count") return false;

    InputStringStream ss (e.value);
    ss >> ctx.cnt;

    if (!ss)
    {
        OutputStringStream ss;
        ss << "Failed to parse " << e.value << "as character count";

        throw std::runtime_error (ss.CStr ());
    }

    return true;
}

Cellwars::EventRegisterer<HieroCharCountWatcher> HieroCharCountWatcher::reg;

template <>
void Cellwars::EventMaster<HieroCharCountEvent>::UnregisteredEventCallback (const HieroCharCountEvent::Type& e, HieroCharCountEvent::Context&)
{
    ThrowIfUnregisteredOption (e);
}
