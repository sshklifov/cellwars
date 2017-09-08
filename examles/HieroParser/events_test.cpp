#include <HieroParser/Events.h>
#include <Container/String.h>
#include <Container/StringStream.h>
#include <iostream>

using namespace Cellwars;
using namespace std;

struct EventType
{
    String str;
};

struct EventContext
{
    int d;
};

struct Event
{
    using Type = EventType;
    using Context = EventContext;
};

class ThreeWatcher : public EventWatcher<Event>
{
    virtual bool Catch (const typename Event::Type& e, typename Event::Context&)
    {
        InputStringStream ss (e.str);
        
        int three;
        ss >> three;

        if (three == 3)
        {
            cout << "Caught three" << endl;
            return true;
        }

        cout << "Tried to catch three" << endl;
        return false;
    }

private:
    static EventRegisterer<ThreeWatcher> reg;
};

EventRegisterer<ThreeWatcher> ThreeWatcher::reg;

class FourWatcher : public EventWatcher<Event>
{
    virtual bool Catch (const typename Event::Type& e, typename Event::Context&)
    {
        InputStringStream ss (e.str);
        
        int four;
        ss >> four;

        if (four == 4)
        {
            cout << "Caught four" << endl;
            return true;
        }

        cout << "Tried to catch four" << endl;
        return false;
    }

private:
    static EventRegisterer<FourWatcher> reg;
};

EventRegisterer<FourWatcher> FourWatcher::reg;

struct Event2
{
    using Type = String;
    using Context = int;
};

class Watcher2 : public EventWatcher<Event2>
{
    virtual bool Catch (const String& e, int&) override
    {
        cout << "Caught " << e.CStr () << endl;
        return true;
    }

private:
    static EventRegisterer<Watcher2> reg;
};

EventRegisterer<Watcher2> Watcher2::reg;

int main ()
{
    EventType e_type;
    e_type.str = String ("3");

    EventContext e_ctx;
    EventMaster<Event>::CatchEvent (e_type, e_ctx);

    e_type.str = String ("4");
    EventMaster<Event>::CatchEvent (e_type, e_ctx);

    int dummy;
    EventMaster<Event2>::CatchEvent (String ("Event2"), dummy);

    return 0;
}
