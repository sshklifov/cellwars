#include <Epsilon/Types.h>

#include <cstdio>

using namespace Cellwars;

char* to_binary (unsigned d)
{
    static char buf[33];

    unsigned bytes = 32 - __builtin_clz (d);

    for (unsigned i = 0; i < bytes; ++i)
    {
        unsigned mask = 1 << (bytes - i - 1);
        buf[i] = d & mask ? '1' : '0';
    }

    buf[bytes] = '\0';
    return buf;
}

void first_pass ()
{
    printf ("sizeof IntWithSize<1>: %lu\n", sizeof (IntWithSize<1>::type));
    printf ("sizeof IntWithSize<2>: %lu\n", sizeof (IntWithSize<2>::type));
    printf ("sizeof IntWithSize<4>: %lu\n", sizeof (IntWithSize<4>::type));
    printf ("sizeof IntWithSize<8>: %lu\n", sizeof (IntWithSize<8>::type));
}

void second_pass ()
{
    Double d (-7.0);

    printf ("Inspecting -7.0 as double...\n");
    printf ("Sign: %d\n", d.Sign ());
    printf ("Exponent: %d\n", d.Exp () - d.Bias ());
    printf ("Mantissa: %s\n", to_binary (d.Mantissa ()));

    Single s (4.875);
    printf ("\nInspecting 4.875 as float...\n");
    printf ("Sign: %d\n", s.Sign ());
    printf ("Exponent: %d\n", s.Exp () - s.Bias ());
    printf ("Mantissa: %s\n", to_binary (s.Mantissa ()));
}

void third_pass ()
{
    printf ("4.7 > 4.7: %d\n", Double(4.7) > Double(4.7));
    printf ("-4.7 > 5.8: %d\n", Double(-4.7) > Double(5.8));
    printf ("14.7 > 5.3: %d\n", Double(14.7) > Double(5.3));

    printf ("\n4.7 < 4.7: %d\n", Double(4.7) < Double(4.7));
    printf ("-4.7 < 5.8: %d\n", Double(-4.7) < Double(5.8));
    printf ("14.7 < 5.3: %d\n", Double(14.7) < Double(5.3));

    printf ("\n1.0000001 == 1.0: %d\n", Double(1.0000001) == Double(1.0));
    printf ("1.0000001 > 1.0: %d\n", Double(1.0000001) > Double(1.0));
    printf ("1.0000001 < 1.0: %d\n", Double(1.0000001) < Double(1.0));
}

void print_delim ()
{
    printf ("--------------------------------------------------\n");
}

int main ()
{
    first_pass ();
    print_delim ();

    second_pass ();
    print_delim ();

    third_pass ();
    print_delim ();

    return 0;
}
