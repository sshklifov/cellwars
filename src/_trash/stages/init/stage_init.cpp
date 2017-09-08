#include "render_handle.h"

#include <logger.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>

using namespace cellwars;

constexpr float font::sizes[font::layers];

/* Whenever there is an internal GLFW error, this function will be
 * called with information on what caused the problem and an error
 * code. Used only in debug mode.
 */
#ifndef NDEBUG
void glfw_err_callback (int errcode, const char* str)
{
    logWarn ("caught glfw error %d: %s", errcode, str);
}
#endif

bool render_handle::init ()
{
    /* Initialize GLFW
     */
    if (!glfwInit())
    {
        logError ("glfw failed to initialize");
        return false;
    }

    /* Set error callback
     */
#ifndef NDEBUG
    glfwSetErrorCallback (glfw_err_callback);
#endif

    /* Get primary monitor (in order to create a fullscreen window)
     */
    GLFWmonitor* monitor = glfwGetPrimaryMonitor ();
    if (monitor == nullptr)
    {
        logError ("cout not get primary monitor");
        return false;
    }

    const GLFWvidmode* vidmode = glfwGetVideoMode (monitor);
    if (vidmode == nullptr)
    {
        logError ("could not get vide mode of primary monitor");
        return false;
    }

    glfwWindowHint (GLFW_RED_BITS, vidmode->redBits);
    glfwWindowHint (GLFW_GREEN_BITS, vidmode->greenBits);
    glfwWindowHint (GLFW_BLUE_BITS, vidmode->blueBits);
    glfwWindowHint (GLFW_REFRESH_RATE, vidmode->refreshRate);

    glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create window
     */
    window = glfwCreateWindow (vidmode->width, vidmode->height, "Cellwars", monitor, nullptr);
    if (window == nullptr)
    {
        logError ("could not create a rendering window");
        return false;
    }

    glfwMakeContextCurrent (window);
    glfwSwapInterval (1);

    /* Set appropriate width and height (class member variables)
     */
    width = vidmode->width;
    height = vidmode->height;

    /* Initialzie glad
     */
    if (!gladLoadGL())
    {
        logError ("glad failed to load OpenGL library");
        return false;
    }

    logDebug ("using OpenGL version %d.%d", GLVersion.major, GLVersion.minor);

    /* 2D OpenGL defaults
     */
    glDisable (GL_CULL_FACE);
    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth (1.3f);
    glViewport (0, 0, vidmode->width, vidmode->height);

    /* Get dpi and load font
     */
    int monitor_width, monitor_height;
    glfwGetMonitorPhysicalSize (monitor, &monitor_width, &monitor_height);

    double dpi_horz = vidmode->width / (monitor_width / 25.4);
    double dpi_vert = vidmode->height / (monitor_height / 25.4);

    if (!font.load (vidmode->width, vidmode->height, dpi_horz, dpi_vert))
    {
        return false;
    }

    return true;
}
