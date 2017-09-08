#include <Container/StringStream.h>
#include <logger/logger.h>
using namespace Cellwars;

void first_pass ()
{
    InputStringStream ss ("312");
    logAssert (ss.Good ());

    char c;

    ss >> c;
    logAssert (ss && c == '3');

    ss >> c;
    logAssert (ss && c == '1');

    ss >> c;
    logAssert (ss && c == '2');

    InputStringStream ss2 ("312");
    int d;

    ss2 >> d;
    logAssert (ss2 && d == 312);

    InputStringStream ss3 ("3.25");
    float flt;

    ss3 >> flt;
    logAssert (ss3 && flt == 3.25);
}

void second_pass ()
{
    InputStringStream ss ("3 5 1.5 a");

    unsigned three, five;
    double one_and_half;
    char a;

    /* ss >> three >> five >> one_and_half >> a; */
    ss.ScanFmt ("%u %u %lf%c", &three, &five, &one_and_half, &a);

    logAssert (ss);
    logAssert (three == 3 && five == 5);
    logAssert (one_and_half == 1.5);
    logAssert (a == ' ');
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
