#ifndef EVENTS_INCLUDED
#define EVENTS_INCLUDED

#include <Container/Vector.h>
#include <Misc/NewPtr.h>

namespace Cellwars
{
    template <typename Event>
    class EventWatcher
    {
    public:
        using EventType = Event;

    public:
        virtual bool Catch (const typename Event::Type& e, typename Event::Context& ctx) = 0;
        virtual ~EventWatcher () {};
    };

    template <typename Watcher>
    class EventRegisterer
    {
    public:
        EventRegisterer ();
        ~EventRegisterer ();
    };

    template <typename Event>
    class EventMaster
    {
    public:
        using ValueType = Cellwars::Vector<EventWatcher<Event>*>;

    public:
        static void CatchEvent (const typename Event::Type& e, typename Event::Context& ctx);

        static void RegisteredEventCallback (const typename Event::Type&, typename Event::Context&);
        static void UnregisteredEventCallback (const typename Event::Type&, typename Event::Context&);

    public:
        static ValueType& GetInstance ();
    };
};

#include "Events.inl"

#endif /* EVENTS_INCLUDED */
