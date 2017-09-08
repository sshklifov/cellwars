/*! @file ClipWindow.h
 *
 *  Defines the ClipWindow class. A clip window is a rectangle (box),
 *  which can check if some port of a geometric figure lays inside the
 *  rectangle. The reason for naming it a clipping window is clear
 *  then -- it will be used (mostly) for clipping.
 *
 *  This class does not define a geometric figure and
 *  is not part of the "core" epsilon library.
 */

#ifndef CLIP_WINDOW_INCLUDED
#define CLIP_WINDOW_INCLUDED

/* #include "Point.h" */
/* #include "Vec.h" */
/* #include "Line.h" */
/* #include "Box.h" */
/* #include "Circle.h" */

namespace Cellwars
{
    class ClipWindow
    {
    public:
        ClipWindow (float x = 0, float y = 0, float width = 0, float height = 0) : clip_box (x, y, width, height)
        {
        }

        ClipWindow (const FBox& rhs) : clip_box (rhs)
        {
        }

        ClipWindow (const ClipWindow& rhs) : clip_box (rhs.clip_box)
        {
        }
        
        const ClipWindow& operator= (const ClipWindow& rhs)
        {
            clip_box = rhs.clip_box;

            return (*this);
        }

        template <typename T>
        bool IsInside (const Point2<T>& p)
        {
            return _XClipBound (p.x) && _YClipBound (p.y);
        }

        template<typename T>
        bool IsInside (const Box<T>& b)
        {
            bool overlap = clip_box.GetLowerX () > b.GetLowerX () && clip_box.GetUpperX () < b.GetUpperX () &&
                clip_box.GetLowerY () > b.GetLowerY () && clip_box.GetUpperY () < b.GetUpperY ();

            return overlap || ((_XClipBound (b.GetLowerX ()) || _XClipBound (b.GetUpperX ())) &&
                (_YClipBound (b.GetLowerY ()) || _YClipBound (b.GetUpperY ())));
        }

        template <typename T>
        bool IsInside (const LineSegment<T> l)
        {
            if (IsInside (l.start) || IsInside (l.end)) return true;

            return LineSegmentIntersect (l, clip_box.GetLeft ()) ||
                LineSegmentIntersect (l, clip_box.GetRight ()) ||
                LineSegmentIntersect (l, clip_box.GetTop ()) ||
                LineSegmentIntersect (l, clip_box.GetBot ());
        }

        template <typename T>
        bool IsInsideApprox (const LineSegment<T> l)
        {
            auto width = Abs (l.end.x - l.start.x);
            auto height = Abs (l.end.y - l.start.y);

            return IsInside (Box<T> (l.start, width, height));
        }

        template <typename T>
        bool IsInside (const Line<T>& l)
        {
            logAssert (!IsDegenerate (l));

            if (IsEqual (l.b, (T)0))
            {
                return _XClipBound (-l.c / l.a);
            }

            Point2<T> intersect;

            LineIntersect (l, LineEquation (clip_box.GetLeft ()), intersect);
            T y1 = intersect.y;

            LineIntersect (l, LineEquation (clip_box.GetRight ()), intersect);
            T y2 = intersect.y;

            return InsideClosedInterval (clip_box.GetLowerY (), y1, y2) ||
                InsideClosedInterval (clip_box.GetUpperY (), y1, y2);
        }

        template <typename T>
        bool IsInside (const Circle<T>& c)
        {
            logAssert (!IsDegenerate (c));

            if (IsInside (c.center)) return true;

            T rad2 = c.rad * c.rad;
            return IsLess (Distance2 (c.center, clip_box.GetLeft ()), rad2) ||
                IsLess (Distance2 (c.center, clip_box.GetRight ()), rad2) ||
                IsLess (Distance2 (c.center, clip_box.GetBot ()), rad2) ||
                IsLess (Distance2 (c.center, clip_box.GetTop ()), rad2);
        }

        template <typename T>
        bool IsInsideApprox (const Circle<T>& c)
        {
            Point2<T> botleft (c.center.x - c.rad, c.center.y - c.rad);
            T diam = c.rad * (T)2;

            return IsInside (Box<T> (botleft, diam, diam));
        }

    private:
        template <typename T>
        bool _XClipBound (T x)
        {
            return InsideClosedInterval (x, clip_box.GetLowerX (), clip_box.GetUpperX ());
        }

        template <typename T>
        bool _YClipBound (T y)
        {
            return InsideClosedInterval (y, clip_box.GetLowerY (), clip_box.GetUpperY ());
        }

    private:
        FBox clip_box;
    };
};

#endif /* _CLIP_WINDOW_H */
