#include "../../src/HieroParser/HieroHeaderParser.cpp" // TODO
#include <logger/logger.h>
using namespace Cellwars;

void first_pass ()
{
    logAssert (EventMaster<HieroHeaderEvent>::GetInstance ().Size () == 5);

    HieroHeader hh;

    HieroOption opt;
    opt.name = "width";
    opt.value = "1366";

    EventMaster<HieroHeaderEvent>::CatchEvent (opt, hh);
    logAssert (hh.tex_width == 1366);
}

void second_pass ()
{
    HieroHeader hh;

    HieroOption opt;
    opt.name = "height";
    opt.value = "abc";

    try
    {
        EventMaster<HieroHeaderEvent>::CatchEvent (opt, hh);
    }
    catch (std::exception& e)
    {
        logDebug ("%s", e.what ());
    }
}

void third_pass ()
{
    HieroHeader hh;

    HieroOption opt;
    opt.name = "haigt";
    opt.value = "133";

    try
    {
        EventMaster<HieroHeaderEvent>::CatchEvent (opt, hh);
    }
    catch (std::exception& e)
    {
        logDebug ("%s", e.what ());
    }
}

void forth_pass ()
{
    HieroHeader hh;

    HieroOption opt;
    opt.name = "format";
    opt.value = "rgba";

    EventMaster<HieroHeaderEvent>::CatchEvent (opt, hh);
    logAssert (hh.tex_format == GL_RGBA);
}

void print_success ()
{
    logDebug ("Pass");
}

int main ()
{
    first_pass ();
    second_pass ();
    third_pass ();
    forth_pass ();

    print_success ();
    return 0;
}
