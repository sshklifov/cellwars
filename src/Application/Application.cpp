#include "Application.h"
#include <glad/glad.h>

Cellwars::Application::Singleton& Cellwars::Application::GetInstance ()
{
    static Singleton instance;
    return instance;
}

void Cellwars::Application::Singleton::Load ()
{
    StageLogin ();
}

void Cellwars::Application::Singleton::ClearScreen ()
{
    float white[] = {1.f, 1.f, 1.f, 1.f};
    glClearBufferfv (GL_COLOR, 0, white);

    float one = 1.f;
    glClearBufferfv (GL_DEPTH, 0, &one);
}
