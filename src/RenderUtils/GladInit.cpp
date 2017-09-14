#include "GladInit.h"
#include <glad/glad.h>
#include "GlfwInit.h"
#include <logger/logger.h>

#include <stdexcept>

using Cellwars::GladInit;
using Singleton = Cellwars::GladInit::Singleton;

static void GladInitHooks ()
{
    glViewport (0, 0, GlfwInit::GetInstance().GetWidth (), GlfwInit::GetInstance().GetHeight ());
    glDisable (GL_CULL_FACE);
    glLineWidth (1.3f);
}

Singleton& GladInit::GetInstance ()
{
    static Singleton instance;
    return instance;
}

Singleton::Singleton ()
{
    logAssert (GlfwInit::GetInstance().IsLoaded ());

    if (!gladLoadGL())
    {
        throw std::runtime_error ("glad failed to load OpenGL library");
    }

    GladInitHooks ();

    logDebug ("using OpenGL version %d.%d", GLVersion.major, GLVersion.minor);
}

Singleton::~Singleton ()
{
}

bool Singleton::IsLoaded () const
{
    return true;
}
