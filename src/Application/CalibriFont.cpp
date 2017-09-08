#include "CalibriFont.h"
#include <HieroParser/HieroParser.h>

Cellwars::Font& Cellwars::CalibriFont::GetInstance ()
{
    static Font instance (new HieroParser ("res/font/Calibri.fnt"));
    return instance;
}
