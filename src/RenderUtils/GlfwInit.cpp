#include "GlfwInit.h"
#include <logger/logger.h>

#include <stdexcept>

using Cellwars::GlfwInit;
using Singleton = GlfwInit::Singleton;

Singleton& GlfwInit::GetInstance ()
{
    static Singleton instance;
    return instance;
}

static void InitializeGlfw ()
{
    if (!glfwInit())
    {
        throw std::runtime_error ("glfw failed to initialize");
    }

#ifndef NDEBUG
    glfwSetErrorCallback (GlfwErrorCallback);
#endif
}

static void GlfwErrorCallback (int errcode, const char* str)
{
    logWarn ("caught glfw error %d: %s", errcode, str);
}

static GLFWwindow* CreateFullscreenWindow ()
{
    GLFWmonitor* monitor = glfwGetPrimaryMonitor ();
    if (monitor == NULL)
    {
        throw std::runtime_error ("cout not get primary monitor");
    }

    const GLFWvidmode* vidmode = glfwGetVideoMode (monitor);
    if (vidmode == NULL)
    {
        throw std::runtime_error ("could not get vide mode of primary monitor");
    }

    SetWindowHints (vidmode);

    window = glfwCreateWindow (vidmode->width, vidmode->height, "Cellwars", monitor, NULL);
    if (window == NULL)
    {
        throw std::runtime_error ("could not create a rendering window");
    }

    return window;
}

static void SetWindowHints (const GLFWvidmode* vidmode)
{
    glfwWindowHint (GLFW_RED_BITS, vidmode->redBits);
    glfwWindowHint (GLFW_GREEN_BITS, vidmode->greenBits);
    glfwWindowHint (GLFW_BLUE_BITS, vidmode->blueBits);
    glfwWindowHint (GLFW_REFRESH_RATE, vidmode->refreshRate);

    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Singleton::Singleton ()
{
    InitializeGlfw ();

    window = CreateFullscreenWindow ();
    glfwMakeContextCurrent (window);
    glfwSwapInterval (1);

    glfwGetWindowSize (window, &width, &height);
}

Singleton::~Singleton ()
{
    Clear ();
}

bool Singleton::IsLoaded () const
{
    return window;
}

void Singleton::Clear ()
{
    if (IsLoaded ())
    {
        glfwDestroyWindow (window);
        window = NULL;
        glfwTerminate ();
    }
}

GLFWwindow* Singleton::GetWindow ()
{
    return window;
}

unsigned Singleton::GetWidth ()
{
    return width;
}

unsigned Singleton::GetHeight ()
{
    return height;
}