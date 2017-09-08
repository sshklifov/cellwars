#include "Bot.h"
#include "Arena.h"
#include <glm/gtc/random.hpp>

using Cellwars::Bot;

constexpr float Bot::velocity;

Bot::Bot () : total_time (0.f)
{
    GenerateRandomDirection ();

    FPoint2 position;
    position.x = glm::linearRand (0.f, Arena::GetInstance().GetWidth ());
    position.y = glm::linearRand (0.f, Arena::GetInstance().GetHeight ());

    FVec3 colour;
    colour.x = glm::linearRand (0.f, 1.f);
    colour.y = glm::linearRand (0.f, 1.f);
    colour.z = glm::linearRand (0.f, 1.f);

    p_bot = new RenderCircle (FCircle (position, 200.f), colour, "");
    RenderGeometryContainer().GetInstance().PushBack (p_bot);
}

Bot::~Bot ()
{
    RenderGeometryContainer::GetInstance().Remove (p_bot);
}

void Bot::UpdatePosition (float elapsed_time)
{
    total_time += elapsed_time;
    if (IsGreater (total_time, 5.f))
    {
        GenerateRandomDirection ();
        total_time = 0.f;
    }

    FPoint2 pos = p_bot->GetCenter ();
    pos = Translate (pos, direction * velocity * elapsed_time);
    Arena::GetInstance().Clamp(pos);
    p_bot->SetCenter (pos);
}

void Bot::GenerateRandomDirection ()
{
    direction.x = glm::linearRand (0.f, 100.f);
    direction.y = glm::linearRand (0.f, 100.f);

    direction.Normalize ();
}
