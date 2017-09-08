#include <Epsilon/ClipWindow.h>

#include <cstdio>

using namespace Cellwars;

void first_pass ()
{
    ClipWindow clip (0, 0, 1000, 1000);

    printf ("Using box with start (0, 0) width: 1000, height: 1000\n");
    printf ("IsInside point (5, 5): %d\n", clip.IsInside (FPoint2 (5, 5)));
    printf ("IsInside point (512, 30): %d\n", clip.IsInside (FPoint2 (512, 30)));
    printf ("IsInside point (1001, 30): %d\n", clip.IsInside (FPoint2 (1001, 30)));
    printf ("IsInside point (-2, 30): %d\n", clip.IsInside (FPoint2 (-2, 30)));
}

void second_pass ()
{
    ClipWindow clip (0, 0, 1000, 1000);

    printf ("Using box with start (0, 0) width: 1000, height: 1000\n");
    printf ("IsInside botleft (5, 5), width: 100, height: 100: %d\n", clip.IsInside (FBox (5, 5, 100, 100)));
    printf ("IsInside botleft (5, 5), width: 996, height: 100: %d\n", clip.IsInside (FBox (5, 5, 996, 100)));
    printf ("IsInside botleft (5, 5), width: 996, height: 996: %d\n", clip.IsInside (FBox (5, 5, 996, 996)));
    printf ("IsInside botleft (-20, 500), width: 200, height: 200: %d\n", clip.IsInside (FBox (-20, 500, 200, 200)));
    printf ("IsInside botleft (-50, -50), width: 1100, height: 1100: %d\n", clip.IsInside (FBox (-50, -50, 1100, 1100)));
    printf ("IsInside botleft (1100, 1100), width: 1100, height: 1100: %d\n", clip.IsInside (FBox (1100, 1100, 1100, 1100)));
    printf ("IsInside botleft (-500, -200), width: 50, height: 20: %d\n", clip.IsInside (FBox (-500, -200, 50, 20)));
}

void third_pass ()
{
    ClipWindow clip (0, 0, 1000, 1000);

    printf ("Using box with start (0, 0) width: 1000, height: 1000\n");
    printf ("IsInside segment (1, 1) and (3, 3): %d\n", clip.IsInside (FLineSegment (FPoint2 (1, 1), FPoint2 (3, 3))));
    printf ("IsInside segment (-1, -1) and (3, 3): %d\n", clip.IsInside (FLineSegment (FPoint2 (1, 1), FPoint2 (3, 3))));
    printf ("IsInside segment (-3, -3) and (-3, 3): %d\n", clip.IsInside (FLineSegment (FPoint2 (-3, -3), FPoint2 (-3, 3))));
    printf ("IsInside segment (50, 50) and (-50, 70): %d\n", clip.IsInside (FLineSegment (FPoint2 (50, 50), FPoint2 (-50, 70))));
    printf ("IsInside segment (-3, 100) and (-5, 170): %d\n", clip.IsInside (FLineSegment (FPoint2 (-3, 100), FPoint2 (-5, 170))));
}

void forth_pass ()
{
    ClipWindow clip (0, 0, 100, 100);

    printf ("Using box with start (0, 0) width: 100, height: 100\n");
    printf ("IsInside 5x+7y-100=0: %d\n", clip.IsInside (FLine (5, 7, -100)));
    printf ("IsInside x+y-3=0: %d\n", clip.IsInside (FLine (1, 1, -3)));
    printf ("IsInside x-110=0: %d\n", clip.IsInside (FLine (1, 0, -1100)));
    printf ("IsInside 5x-7y-800=0: %d\n", clip.IsInside (FLine (5, -7, -800)));
}

void fifth_pass ()
{
    ClipWindow clip (0, 0, 100, 100);

    printf ("Using box with start (0, 0) width: 100, height: 100\n");
    printf ("IsInside start (5, 5) and rad 20: %d\n", clip.IsInside (FCircle (FPoint2 (5, 5), 20)));
    printf ("IsInside start (-5, -5) and rad 200: %d\n", clip.IsInside (FCircle (FPoint2 (5, 5), 200)));
    printf ("IsInside start (-5, 50) and rad 50: %d\n", clip.IsInside (FCircle (FPoint2 (-5, 50), 50)));
    printf ("IsInside start (-5, -5) and rad 20: %d\n", clip.IsInside (FCircle (FPoint2 (-5, -5), 20)));
    printf ("IsInside start (-5, 20) and rad 2: %d\n", clip.IsInside (FCircle (FPoint2 (-5, 20), 2)));
    printf ("IsInside start (200, 200) and rad 50: %d\n", clip.IsInside (FCircle (FPoint2 (200, 200), 50)));
}

void sixth_pass ()
{
    ClipWindow clip (0, 0, 100, 100);

    printf ("Using box with start (0, 0) width: 100, height: 100\n");
    printf ("IsInsideApprox segment (1, 1) and (3, 3): %d\n", clip.IsInsideApprox (FLineSegment (FPoint2 (1, 1), FPoint2 (3, 3))));
    printf ("IsInsideApprox segment (-1, -1) and (3, 3): %d\n", clip.IsInsideApprox (FLineSegment (FPoint2 (1, 1), FPoint2 (3, 3))));
    printf ("IsInsideApprox segment (-3, -3) and (-3, 3): %d\n", clip.IsInsideApprox (FLineSegment (FPoint2 (-3, -3), FPoint2 (-3, 3))));
    printf ("IsInsideApprox segment (-5, 2) and (5, -5): %d\n", clip.IsInsideApprox (FLineSegment (FPoint2 (-5, 2), FPoint2 (5, -5))));

    printf ("\nIsInsideApprox start (5, 5) and rad 20: %d\n", clip.IsInsideApprox (FCircle (FPoint2 (5, 5), 20)));
    printf ("IsInsideApprox start (-5, -5) and rad 200: %d\n", clip.IsInsideApprox (FCircle (FPoint2 (-5, -5), 200)));
    printf ("IsInsideApprox start (-5, 50) and rad 50: %d\n", clip.IsInsideApprox (FCircle (FPoint2 (-5, 50), 50)));
    printf ("IsInsideApprox start (-5, -5) and rad 20: %d\n", clip.IsInsideApprox (FCircle (FPoint2 (-5, -5), 20)));
    printf ("IsInsideApprox start (-5, 20) and rad 2: %d\n", clip.IsInsideApprox (FCircle (FPoint2 (-5, 20), 2)));
    printf ("IsInsideApprox start (120, 120) and rad 50: %d\n", clip.IsInsideApprox (FCircle (FPoint2 (120, 120), 50)));
    printf ("IsInsideApprox start (200, 200) and rad 50: %d\n", clip.IsInsideApprox (FCircle (FPoint2 (200, 200), 50)));
    printf ("IsInsideApprox start (-3, -3) and rad 4: %d\n", clip.IsInsideApprox (FCircle (FPoint2 (-3, -3), 4)));
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

    forth_pass ();
    print_delim ();

    fifth_pass ();
    print_delim ();

    sixth_pass ();
    print_delim ();

    return 0;
}
