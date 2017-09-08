#include <Container/StringStream.h>
using namespace Cellwars;

void first_pass ()
{
    String str ("easy peasy");
    OutputStringStream ss (std::move (str));

    logAssert (ss && str.Empty () && String ("easy peasy") == ss.CStr ());

    ss.Clear ();
    ss << 5;
    logAssert (ss && String ("5") == ss.CStr ());

    ss << 123;
    logAssert (ss && String ("5123") == ss.CStr ());

    ss << " squeezy";
    logAssert (ss && String ("5123 squeezy") == ss.CStr ());
}

void second_pass ()
{
    String str ("easy peasy");
    OutputStringStream ss (std::move (str));

    ss << 5 << ' ' << "lemon squeezy";
    logAssert (ss && String ("easy peasy5 lemon squeezy") == ss.CStr ());
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
