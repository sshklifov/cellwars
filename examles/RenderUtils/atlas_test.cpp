#include <RenderUtils/Atlas.h>
#include <HieroParser/HieroParser.h>
#include <logger/logger.h>
using namespace Cellwars;

void first_pass ()
{
    Atlas atlas (new HieroParser ("Calibri.fnt"));

    logAssert (atlas.GetTexType () == GL_UNSIGNED_BYTE);
    logAssert (atlas.GetTexFormat () == GL_RGBA);
    logAssert (atlas.GetTexWidth () == 1024);
    logAssert (atlas.GetTexHeight () == 1024);

    for (unsigned i = 48; i <= 57; ++i)
    {
        logAssert (atlas.HasGlyph (i));
    }
    for (unsigned i = 65; i <= 90; ++i)
    {
        logAssert (atlas.HasGlyph (i));
    }
    for (unsigned i = 97; i <= 122; ++i)
    {
        logAssert (atlas.HasGlyph (i));
    }

    Atlas::Glyph g = atlas[48];
    logAssert (g.pos.botleft.x == 58 && g.pos.botleft.y == 87);
    logAssert (g.pos.width == 60 && g.pos.height == 75);
    logAssert (g.offset.x == -12 && g.offset.y == 0);
    logAssert (g.xadvance == 63);
}

void print_success ()
{
    logDebug ("Pass");
}

int main ()
{
    first_pass ();

    print_success ();
    return 0;
}
