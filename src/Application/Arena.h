#ifndef ARENA_INCLUDED
#define ARENA_INCLUDED

#include <Epsilon/Point.h>

namespace Cellwars
{
    class Arena
    {
    public:
        class Singleton;
        static Singleton& GetInstance ();
    };

    class Arena::Singleton
    {
    public:
        Singleton (float width, float height);

        float GetWidth () const;
        float GetHeight () const;

        void Clamp (FPoint2& p) const;

    private:
        const float width;
        const float height;
    };
};

#endif /* ARENA_INCLUDED */
