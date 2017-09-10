#include "Events.h"
#include <Misc/NewPtr.h>

template <typename Watcher>
Cellwars::EventRegisterer<Watcher>::EventRegisterer ()
{
    using EventType = typename Watcher::EventType;
    typename EventMaster<EventType>::ValueType& v = EventMaster<EventType>::GetInstance ();

    v.PushBack (new Watcher);
}

template <typename Watcher>
Cellwars::EventRegisterer<Watcher>::~EventRegisterer ()
{
    using EventType = typename Watcher::EventType;
    typename EventMaster<EventType>::ValueType& v = EventMaster<EventType>::GetInstance ();

    //TODO delete v.Front ();
    delete v.Back ();
    v.Resize (v.Size () - 1);
}

template <typename Event>
typename Cellwars::EventMaster<Event>::ValueType& Cellwars::EventMaster<Event>::GetInstance ()
{
    static ValueType instance;
    return instance;
}

template <typename Event>
void Cellwars::EventMaster<Event>::CatchEvent (const typename Event::Type& e, typename Event::Context& ctx)
{
    for (unsigned i = 0; i < GetInstance().Size (); ++i)
    {
        if (GetInstance()[i]->Catch (e, ctx))
        {
            EventMaster<Event>::RegisteredEventCallback (e, ctx);
            return;
        }
    }

    EventMaster<Event>::UnregisteredEventCallback (e, ctx);
}

template <typename Event>
void Cellwars::EventMaster<Event>::RegisteredEventCallback (const typename Event::Type&, typename Event::Context&)
{
}

template <typename Event>
void Cellwars::EventMaster<Event>::UnregisteredEventCallback (const typename Event::Type&, typename Event::Context&)
{
}
