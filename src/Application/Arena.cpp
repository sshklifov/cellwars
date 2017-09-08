#include "Arena.h"
#include <RenderUtils/GlfwInit.h>
#include <glm/common.hpp>

using Cellwars::Arena;
using Singleton = Arena::Singleton;

Singleton& Arena::GetInstance ()
{
    float arena_width = GlfwInit().GetInstance().GetWidth() * 4.f;
    float arena_height = GlfwInit().GetInstance().GetHeight() * 4.f;

    static Singleton instance (arena_width, arena_height);
    return instance;
}


Singleton::Singleton (float width, float height) : width (width), height (height)
{
}

float Singleton::GetWidth () const
{
    return width;
}

float Singleton::GetHeight () const
{
    return height;
}

void Singleton::Clamp (Cellwars::FPoint2& p) const
{
    p.x = glm::clamp (p.x, 0.f, GetWidth ());
    p.y = glm::clamp (p.y, 0.f, GetHeight ());
}
