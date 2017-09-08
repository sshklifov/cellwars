#ifndef _BLOB_UNIT_H
#define _BLOB_UNIT_H

#include "ClipWindow.h"
#include "Circle.h"
#include "Context.h"

namespace Cellwars
{
    class Blob : FCircle
    {
    public:
        Blob ()
        {
        }

        Blob (const FCircle& c, const FVec3& colour)
        {
            _CreateBlob (c.center, c.rad, colour);
        }

        Blob (const Blob& rhs)
        {
            _CreateBlob (rhs.center, rhs.rad, rhs.colour);
        }

        const Player& operator= (const Player& rhs)
        {
            _CreateBlob (rhs.center, rhs.rad, rhs.colour);

            return (*this);
        }

        const FPoint2& GetCenter () const
        {
            return this->center;
        }

        float GetRad () const
        {
            return this->rad;
        }

        const FCircle& GetCircle () const
        {
            return dynamic_cast<const FCircle&> (*this);
        }

        const FVec3& GetColour () const
        {
            return colour;
        }

        void SetCenter (const FPoint2& center)
        {
            this->center = center;
        }

        void SetRad (const float rad)
        {
            this->rad = rad;
        }

        void SetColour (const FVec3& colour)
        {
            this->colour = colour;
        }

    private:
        void _CreateBlob (const FPoint2& center, float rad, const FVec3& colour)
        {
            SetCenter (center);
            SetRad (rad);
            SetColour (colour);
        }

    private:
        FVec3 colour;
    };

    class BlobUnit
    {
    public:
        void Render (const BlobContext& ctx)
        {
            unsigned indices[MAX_BATCH_SIZE];
            unsigned num_indices = 0;
            const Blob* blobs = ctx.RequestBlobs ();
            ClipWindow clip = ctx.GetClipWindow ();

            for (unsigned i = 0; i < ctx.GetBlobCnt (); ++i)
            {
                if (clip.IsInsideApprox (blobs[i].GetCircle ()))
                {
                    indices[++num_indices] = i;
                }
            }

            // RenderIndirect
            ctx.DoneBlobs ();
        }

    private:
        static constexpr unsigned MAX_BATCH_SIZE = 300;
    };
};

#endif /* _BLOB_UNIT */
