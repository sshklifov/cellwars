#include "../../src/HieroParser/HieroHeaderParser.cpp" // TODO
#include "../../src/HieroParser/HieroGlyphParser.cpp" // TODO
#include "../../src/HieroParser/HieroCharCountParser.cpp" // TODO
#include "../../src/HieroParser/HieroContentsParser.cpp" // TODO
#include <logger/logger.h>
using namespace Cellwars;

void first_pass ()
{
    String str ("\"x y z\" ===  13    y=\"daum son\"");
    HieroOption opt1;
    HieroOption opt2;

    unsigned pos = ParseOption (opt1, str);
    ParseOption (opt2, str, pos);
    logAssert (opt1.name == String ("x y z") && opt1.value == String ("13"));
    logAssert (opt2.name == String ("y") && opt2.value == String ("daum son"));
}

void second_pass ()
{
    String str ("info name=\"Calibri.png\" width=1024 height=1024 format=rgba type=byte");

    HieroContents hiero;
    EventMaster<HieroContentsEvent>::CatchEvent (str, hiero);

    logAssert (hiero.header.tex_name == String ("Calibri.png"));
    logAssert (hiero.header.tex_width == 1024);
    logAssert (hiero.header.tex_height == 1024);
    logAssert (hiero.header.tex_format == GL_RGBA);
    logAssert (hiero.header.tex_type == GL_UNSIGNED_BYTE);
}

void third_pass ()
{
    String str ("chars count=65");

    HieroContents hiero;
    EventMaster<HieroContentsEvent>::CatchEvent (str, hiero);

    logAssert (hiero.chars.cnt == 65);
}

void forth_pass ()
{
    String str1 ("char id=32      x=0    y=0    width=0    height=0    xoffset=-14  yoffset=0    xadvance=44");
    String str2 ("char id=10      x=0    y=0    width=0    height=0    xoffset=-14  yoffset=0    xadvance=28");

    HieroContents hiero;
    EventMaster<HieroContentsEvent>::CatchEvent (str1, hiero);
    EventMaster<HieroContentsEvent>::CatchEvent (str2, hiero);

    logAssert (hiero.v_glyphs[0].id == 32);
    logAssert (hiero.v_glyphs[0].pos.botleft.x == 0);
    logAssert (hiero.v_glyphs[0].pos.botleft.y == 0);
    logAssert (hiero.v_glyphs[0].pos.width == 0);
    logAssert (hiero.v_glyphs[0].pos.height == 0);
    logAssert (hiero.v_glyphs[0].offset.x == -14);
    logAssert (hiero.v_glyphs[0].offset.y == 0);
    logAssert (hiero.v_glyphs[0].xadvance == 44);

    logAssert (hiero.v_glyphs[1].id == 10);
    logAssert (hiero.v_glyphs[1].pos.botleft.x == 0);
    logAssert (hiero.v_glyphs[1].pos.botleft.y == 0);
    logAssert (hiero.v_glyphs[1].pos.width == 0);
    logAssert (hiero.v_glyphs[1].pos.height == 0);
    logAssert (hiero.v_glyphs[1].offset.x == -14);
    logAssert (hiero.v_glyphs[1].offset.y == 0);
    logAssert (hiero.v_glyphs[1].xadvance == 28);
}

void fifth_pass ()
{
    String str ("\n");

    HieroContents hiero;
    EventMaster<HieroContentsEvent>::CatchEvent (str, hiero);
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
    fifth_pass ();

    print_success ();
    return 0;
}
