#include "../../src/HieroParser/HieroCharCountParser.cpp" // TODO
#include <logger/logger.h>
using namespace Cellwars;

void first_pass ()
{
    logAssert (EventMaster<HieroCharCountEvent>::GetInstance ().Size () == 1);

    HieroCharCount cc;

    HieroOption opt;
    opt.name = "count";
    opt.value = "128";

    EventMaster<HieroCharCountEvent>::CatchEvent (opt, cc);
    logAssert (cc.cnt == 128);
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
