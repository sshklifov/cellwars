#include <Epsilon/Utility.h>

#include <cstdio>

using namespace Cellwars;

void first_pass ()
{
    printf ("Bitcast 3.5=%lf\n", IntBitsToFloat (FloatBitsToInt (3.5)));
    printf ("Bitcast 3=%d\n",  FloatBitsToInt (IntBitsToFloat (3)));

    printf ("\n17.85 is negative: %d\n", IsNegative (17.85));
    printf ("\n-7.85 is negative: %d\n", IsNegative (-7.85));
    printf ("\n0.0 is negative: %d\n", IsNegative (0.0));
    printf ("\n3 is negative: %d\n", IsNegative (3));
    printf ("\n-33 is negative: %d\n", IsNegative (-33));
}

void second_pass ()
{
    printf ("3.7 < 3.6: %d\n", IsLess (3.7, 3.6));
    printf ("-3.7 < 3.6: %d\n", IsLess (-3.7, 3.6));
    printf ("3 < 3: %d\n", IsLess (3, 3));

    printf ("\n3.7 > 3.6: %d\n", IsGreater (3.7, 3.6));
    printf ("-3.7 > 3.6: %d\n", IsGreater (-3.7, 3.6));
    printf ("3 > 3: %d\n", IsGreater (3, 3));

    printf ("\n3.7 == 3.7: %d\n", IsEqual (3.7, 3.7));
    printf ("-3.7 == 3.7: %d\n", IsEqual (-3.7, 3.7));
    printf ("3.0000001 == 3.0: %d\n", IsEqual (3.0000001, 3.0));
    printf ("55 == 55: %d\n", IsEqual (55, 55));

    printf ("\n3.7 != 3.7: %d\n", IsNotEqual (3.7, 3.7));
    printf ("-3.7 != 3.7: %d\n", IsNotEqual (-3.7, 3.7));
    printf ("3 != 3: %d\n", IsNotEqual (3, 3));

    printf ("\n3 >= 3: %d\n", IsGreaterEqual (3, 3));
    printf ("3.7 >= 3.5: %d\n", IsGreaterEqual (3.7, 3.5));
    printf ("3.59 >= 3.6: %d\n", IsGreaterEqual (3.59, 3.6));
}

void third_pass ()
{
    printf ("min (3, 5) = %d\n", Min (3, 5));
    printf ("min (-10, 200) = %d\n", Min (-10, 200));
    printf ("min (10.5, 10.6) = %lf\n", Min (10.5, 10.6));

    printf ("\nmax (3, 5) = %d\n", Max (3, 5));
    printf ("max (-10, 200) = %d\n", Max (-10, 200));
    printf ("max (10.5, 10.6) = %lf\n", Max (10.5, 10.6));

    printf ("\nabs(3) == abs(-3): %d\n", Abs (3) == Abs (-3));
    printf ("abs(3.5)=%lf\n", Abs (3.5));
    printf ("abs(-13.5)=%lf\n", Abs (-13.5));

    printf ("\nsqrt(4.0)=%lf\n", Sqrt (4.0));
    printf ("sqrt(2.0)=%lf\n", Sqrt (2.0));
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
