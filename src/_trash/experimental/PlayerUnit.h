#ifndef _PLAYER_UNIT_H
#define _PLAYER_UNIT_H

#include <logger.h>

#include "ClipWindow.h"
#include "Circle.h"
#include "Context.h"

#include <cstring>

namespace Cellwars
{
    class Player : public Blob
    {
    public:
        Player ()
        {
        }

        Player (const FCircle& c, const FVec3& colour, const char* name)
        {
            _CreatePlayer (c.center, c.rad, colour, name);
        }

        Player (const Player& rhs)
        {
            _CreatePlayer (rhs.center, rhs.rad, rhs.colour, rhs.name);
        }

        const Player& operator= (const Player& rhs)
        {
            _CreatePlayer (rhs.center, rhs.rad, rhs.colour, rhs.name);

            return (*this);
        }

        const char* GetName () const
        {
            return name;
        }

        void SetName (const char* name)
        {
#ifndef NDEBUG
            if (strlen (name) > NAME_SIZE)
            {
                logWarn ("truncating name \'%s\' (exceeds limit of %u size)", name, NAME_SIZE);
            }
#endif
            strncpy (this->name, name, NAME_SIZE);
        }

    private:
        void _CreatePlayer (const FPoint2& center, float rad, const FVec3& colour, const char* name)
        {
            this->SetCenter (center);
            this->SetRad (rad);
            this->SetColour (colour);

            SetName (name);
        }

    private:
        static constexpr unsigned NAME_SIZE = 15;

    private:
        char name[NAME_SIZE + 1];
    };

    class PlayerUnit
    {
    public:
        void Render (const Context& ctx)
        {
            unsigned indices[MAX_BATCH_SIZE];
            unsigned num_indices = 0;

            const Player* players = ctx.RequestPlayers ();
            ClipWindow clip = ctx.GetClipWindow ();

            for (unsigned i = 0; i < ctx.GetPlayerCnt (); ++i)
            {
                if (clip.IsInsideApprox (players[i].GetCircle ()))
                {
                    indices[++num_indices] = i;
                }
            }

            //! RenderIndirect
            ctx.DonePlayers ();
        }
    };
};

#endif /* _PLAYER_UNIT_H */
