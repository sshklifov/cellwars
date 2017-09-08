#include "../../src/HieroParser/HieroGlyphParser.cpp" // TODO
#include <logger/logger.h>
using namespace Cellwars;

void first_pass ()
{
    logAssert (EventMaster<HieroGlyphEvent>::GetInstance ().Size () == 8);

    HieroGlyph g;

    HieroOption opt;
    opt.name = "width";
    opt.value = "1366";

    EventMaster<HieroGlyphEvent>::CatchEvent (opt, g);
    logAssert (g.pos.width == 1366);
}

void second_pass ()
{
    HieroGlyph g;

    HieroOption opt;
    opt.name = "xoffset";
    opt.value = "-133";

    EventMaster<HieroGlyphEvent>::CatchEvent (opt, g);
    logAssert (g.offset.x == -133);
}

void print_success ()
{
    logDebug ("Pass");
}

int main ()
{
    first_pass ();
    second_pass ();

    print_success ();
    return 0;
}
