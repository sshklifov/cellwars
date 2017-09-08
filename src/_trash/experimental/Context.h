#ifndef _CONTEXT_H
#define _CONTEXT_H

#include "PlayerUnit.h"
#include "BlobUnit.h"
#include "GameFieldUnit.h"

namespace Cellwars
{
    class PlayerContext
    {
    public:
        virtual const Player* RequestPlayers () const;
        virtual void DonePlayers () const;
        virtual unsigned GetPlayerCnt () const;
        virtual const ClipWindow& GetClipWindow () const;
    };

    class BlobContext
    {
    public:
        virtual const Blob* RequestBlobs () const;
        virtual void DoneBlobs () const;
        virtual unsigned GetBlobCnt () const;
        virtual const ClipWindow& GetClipWindow () const;
    };

    /* class GameFieldContext */
    /* { */
    /* public: */
    /*     virtual const ClipWindow& GetClipWindow () const; */

    /*     float GetAspectRatio () const */
    /*     { */
    /*         FBox box = GetClipWindow (); */

    /*         logAssert (!IsEqual (box.GetHeight (), 0.f)); */
    /*         return box.GetWidth () / box.GetHeight (); */
    /*     } */
    /* }; */

    class StageMainContext : public PlayerContext, public BlobContext //, public GameFieldsContext
    {
    public:
        Player* RequestPlayers () const final
        {
            return players;
        }

        void DonePlayers () const final
        {
        }

        unsigned GetPlayerCnt () const final
        {
            return num_players;
        }

        Blob* RequestBlobs () const final
        {
            return blobs;
        }

        void DoneBlobs () const final
        {
        }

        unsigned GetBlobCnt () const final
        {
            return num_blobs;
        }

        const ClipWindow& GetClipWindow () const final
        {
            return clip_w;
        }

    private:
        ClipWindow clip_w;
        Player* players;
        Blob* blobs;
        unsigned num_players;
        unsigned num_blobs;
    };
};

#endif /* _CONTEXT_H */
