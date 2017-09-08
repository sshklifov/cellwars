#ifndef BOT_INCLUDED
#define BOT_INCLUDED

#include "RenderGeometry.h"

namespace Cellwars
{
    class Bot
    {
    public:
        Bot ();
        Bot (const Bot&) = delete;
        void operator= (const Bot&) = delete;
        ~Bot ();

        void UpdatePosition (float elapsed_time);

    private:
        void GenerateRandomDirection ();

    private:
        RenderCircle* p_bot;
        FVec2 direction;
        float total_time;

        static constexpr float velocity = 150.f;
    };
};

#endif /* BOT_INCLUDED */
