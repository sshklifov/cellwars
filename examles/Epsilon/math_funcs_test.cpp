#include <Epsilon/MathFuncs.h>

#include <cstdio>

using namespace Cellwars;

void first_pass ()
{
    printf ("1 < 5 < 6: %d\n", InsideOpenInterval (5, 1, 6));
    printf ("1 < 1 < 6: %d\n", InsideOpenInterval (1, 1, 6));
    printf ("1 < 5 < 5: %d\n", InsideOpenInterval (1, 1, 6));
    printf ("1.2 < -3.5 < 6.0: %d\n", InsideOpenInterval (-3.5, 1.2, 6.0));
    printf ("-5.0 < 1.0 < 6.3: %d\n", InsideOpenInterval (1.0, -5.0, 6.3));

    printf ("\n1 <= 5 <= 6: %d\n", InsideClosedInterval (5, 1, 6));
    printf ("\n1 <= 1 <= 6: %d\n", InsideClosedInterval (1, 1, 6));
    printf ("\n1 <= 5 <= 5: %d\n", InsideClosedInterval (1, 1, 6));
    printf ("\n1.2 <= -3.5 <= 6.0: %d\n", InsideClosedInterval (-3.5, 1.2, 6.0));
    printf ("\n-5.0 <= 1.0 <= 6.3: %d\n", InsideClosedInterval (1.0, -5.0, 6.3));
}

void second_pass ()
{
    printf ("(0, 0) is degenerate: %d\n", IsDegenerate (IVec2 (0, 0)));
    printf ("(0.1, 0.1) is degenerate: %d\n", IsDegenerate (DVec2 (0.1, 0.1)));
    printf ("(16, 32) is degenerate: %d\n", IsDegenerate (IVec2 (16, 32)));

    printf ("\n0x + 0y + 1 = 0 is degenerate: %d\n", IsDegenerate (ILine (0, 0, 1)));
    printf ("1x + 5y + 0 = 0 is degenerate: %d\n", IsDegenerate (ILine (1, 5, 0)));
    printf ("1/3x + 2/5y + 3.14 = 0 is degenerate: %d\n", IsDegenerate (DLine (1.0/3.0, 2.0/5.0, 3.14)));

    printf ("\nline segment: point (3, 3) and (3, 3) is degenerate: %d\n", IsDegenerate (ILineSegment (IPoint2 (3, 3), IPoint2 (3, 3))));
    printf ("line segment: point (3.5, 3.0) and (3.0, 3.5) is degenerate: %d\n", IsDegenerate (DLineSegment (DPoint2 (3.5, 3.0), DPoint2 (3.0, 3.5))));

    printf ("\ncircle with rad 5.0 is degeneate: %d\n", IsDegenerate (DCircle (DPoint2 (0.0, 0.0), 5.0)));
    printf ("\ncircle with rad 0.0000001 is degeneate: %d\n", IsDegenerate (DCircle (DPoint2 (0.0, 0.0), 0.0000001)));
}

void third_pass ()
{
    IVec2 v1 = Direction (IPoint2 (0, 0), IPoint2 (3, 5));
    printf ("direction (0, 0) and (3, 5): (%d, %d)\n", v1.x, v1.y);

    DVec2 v2 = Direction (DPoint2 (3, 5), DPoint2 (1, -1));
    printf ("direction (3.0, 5.0) and (1.0, -1.0): (%lf, %lf)\n", v2.x, v2.y);

    DVec2 v3 = Direction (DLineSegment (DPoint2 (3, 5), DPoint2 (1, -1)));
    printf ("direction of line segment (3.0, 5.0) and (1.0, -1.0): (%lf, %lf)\n", v3.x, v3.y);

    DVec2 v4 = Direction (DLine (3, 5, 0));
    printf ("direction of line 3x + 5y + 0 = 0: (%lf, %lf)\n", v4.x, v4.y);

    DPoint2 p1 = Translate (DPoint2 (1, 1), v4);
    printf ("translating point (1, 1) with last vector: (%lf %lf)\n", p1.x, p1.y);
}

void forth_pass ()
{
    printf ("Dot (1, 2) (3, 4): %d\n", Dot (IVec2 (1, 2), IVec2 (3, 4)));
    printf ("Dot (-2, 2) (4, 5): %d\n", Dot (IVec2 (-2, 2), IVec2 (4, 5)));
    printf ("Distance2 vec (1, 3): %d\n", Distance2 (IVec2 (1, 3)));
    printf ("Distance vec (3, 4): %f\n", Distance (DVec2 (3, 4)));
    printf ("Distance2 points (3, 4) (8, 9): %f\n", Distance2 (DPoint2 (3, 4), DPoint2 (8, 9)));
    printf ("Distance y = 0 and (8, 9): %f\n", Distance (DPoint2 (8, 9), DLine (0, 1, 0)));
    printf ("Distance 1x + 3y - 3 = 0 and (5, 5): %f\n", Distance (DPoint2 (5, 5), DLine (1, 3, -3))); // 5.375872
    printf ("Distance 101x + 33y - 3 = 0 and (20, -199): %f\n", Distance (DPoint2 (20, -199), DLine (101, 33, -3))); // approx 42.82357
    printf ("Distance LineSeg (1, 1) and (5, 5) and (4, 2): %lf\n", Distance (DPoint2(4, 2), DLineSegment (DPoint2 (1, 1), DPoint2 (5, 5)))); // sqrt (2)
    printf ("Distance LineSeg (1, 1) and (5, 5) and (0, -2): %lf\n", Distance (DPoint2 (0, -2), DLineSegment (DPoint2 (1, 1), DPoint2 (5, 5)))); // sqrt (10)
    printf ("Distance LineSeg (1, 1) and (5, 5) and (6, 7): %lf\n", Distance (DPoint2 (6, 7), DLineSegment (DPoint2 (1, 1), DPoint2 (5, 5)))); // sqrt (5)
    printf ("Distance LineSeg (1, 1) and (5, 5) and (3, 3): %lf\n", Distance (DPoint2 (3, 3), DLineSegment (DPoint2 (1, 1), DPoint2 (5, 5)))); // 0
    printf ("Distance LineSeg (1, 1) and (5, 5) and (8, 8): %lf\n", Distance (DPoint2 (8, 8), DLineSegment (DPoint2 (1, 1), DPoint2 (5, 5)))); // sqrt (18)
}

void fifth_pass ()
{
    DVec2 v1 = Normalize (DVec2 (1, 1));
    printf ("Normalizing vec (1, 1): %f %f\n", v1.x, v1.y);
    v1 = Normalize (DVec2 (3, 4));
    printf ("Normalizing vec (3, 4): %f %f\n", v1.x, v1.y);

    DLine l1 = Normalize (DLine (5, 5, 3));
    printf ("\nNormalizing 5x + 5y + 3 = 0: %f %f %f\n", l1.a, l1.b, l1.c);

    printf ("\nCross vec (1, 2) (5, 10): %f\n", Determinant (DVec2 (1, 2), DVec2 (5, 10)));
    printf ("Cross vec (5, 7) (4, 2): %f\n", Determinant (DVec2 (5, 7), DVec2 (4, 2)));
    printf ("Dot vec (1, 2) (5, 10): %f\n", Dot (DVec2 (1, 2), DVec2 (5, 10)));
    printf ("Dot vec (5, 7) (4, 2): %f\n", Dot (DVec2 (5, 7), DVec2 (4, 2)));

    printf ("\nIs perpendicular vec (5, 7) (4, 2): %d\n", IsPerpendicular (DVec2 (5, 7), DVec2 (4, 2)));
    printf ("Is perpendicular vec (1, 1) (-2, 2): %d\n", IsPerpendicular (DVec2 (1, 1), DVec2 (-2, 2)));
    printf ("Is parallel vec (5, 7) (4, 2): %d\n", IsParallel (DVec2 (5, 7), DVec2 (4, 2)));
    printf ("Is parallel vec (1, 1) (2, 2): %d\n", IsParallel (DVec2 (1, 1), DVec2 (2, 2)));

    IVec2 v2 = Normal (IVec2 (1, 1));
    printf ("\nNormal of vec (1, 1): %d %d\n", v2.x, v2.y);
    v2 = Normal (IVec2 (2, 3));
    printf ("\nNormal of vec (1, 1): %d %d\n", v2.x, v2.y);
    v2 = Normal (ILine (5, 3, 4));
    printf ("\nNormal of line 5x+3y+4=0: (%d %d)\n", v2.x, v2.y);
}

void sixth_pass ()
{
    DPoint2 p;

    LineIntersect (DLine (1, 2, 3), DLine (7, 6, 5), p);
    printf ("intersecting lines 1x+2y+3=0 and 7x+6y+5=0: (%f %f)\n", p.x, p.y);

    LineIntersect (DLine (10, 5, -3), DLine (-7, -16, 8), p);
    printf ("intersecting lines 10x+5y-3=0 and -7x-16y+8=0: (%f %f)\n", p.x, p.y);

    printf ("intersecting lines 10x+5y-3=0 and 20x+10y+8=0: %d\n", LineIntersect (DLine (10, 5, -3), DLine (20, 10, 8), p));
    //printf ("intersecting lines 10x+5y-3=0 and 20x+10y-6=0: %d\n", LineIntersect (DLine (10, 5, -3), DLine (20, 10, -6), p));
    
    ILine l = LineEquation (IVec2 (1, 1), IPoint2 (0, 0));
    printf ("\nline equation of vec(1, 1) and point (0, 0): %dx+%dy+%d=0\n", l.a, l.b, l.c);
    l = LineEquation (IVec2 (2, 4), IPoint2 (3, 3));
    printf ("line equation of vec(2, 4) and point (3, 3): %dx+%dy+%d=0\n", l.a, l.b, l.c);
    l = LineEquation (ILineSegment (IPoint2 (2, 4), IPoint2 (3, 3)));
    printf ("line equation of points (2, 4) and (3, 3): %dx+%dy+%d=0\n", l.a, l.b, l.c);

    printf ("\nline segments (1, 1) (2, 2) and (1, 2) (2, 1) intersect: %d\n",
            LineSegmentIntersect (ILineSegment (IPoint2 (1, 1), IPoint2 (2, 2)),
                ILineSegment (IPoint2 (1, 2), IPoint2 (2, 1))));
    printf ("line segments (1, 1) (2, 2) and (1, 2) (2, 3) intersect: %d\n",
            LineSegmentIntersect (ILineSegment (IPoint2 (1, 1), IPoint2 (2, 2)),
                ILineSegment (IPoint2 (1, 2), IPoint2 (2, 3))));
    printf ("line segments (1, 1) (2, 2) and (2.5, 1.5) (1.5, 2.4) intersect: %d\n",
            LineSegmentIntersect (DLineSegment (DPoint2 (1, 1), DPoint2 (2, 2)),
                DLineSegment (DPoint2 (2.5, 1.5), DPoint2 (1.5, 2.4))));

    /* printf ("line segments (1, 1) (2, 2) and (1.5, 1.5) (2, 2) intersect: %d\n", */
    /*         LineSegmentIntersect (DLineSegment (DPoint2 (1, 1), DPoint2 (2, 2)), */
    /*             DLineSegment (DPoint2 (1.5, 1.5), DPoint2 (5, 5)))); */
    /* printf ("line segments (1, 1) (2, 2) and (1.5, 1.5) (5, 5) intersect: %d\n", */
    /*         LineSegmentIntersect (DLineSegment (DPoint2 (1, 1), DPoint2 (2, 2)), */
    /*             DLineSegment (DPoint2 (1.5, 1.5), DPoint2 (5, 5)))); */
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
