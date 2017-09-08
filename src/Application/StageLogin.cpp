#include "Application.h"
#include "CalibriFont.h"
#include "RenderGeometry.h"

#include <RenderUtils/GlfwInit.h>
#include <RenderUtils/GladInit.h>
#include <Container/String.h>
#include <Epsilon/Utility.h>
#include <cctype>
using namespace Cellwars;

constexpr unsigned MAX_NAME_LEN = 15;

enum {STATUS_PENDING = 0, STATUS_DONE = 1, STATUS_EXIT = 2}; 

static void KeyCallback (GLFWwindow* window, int key, int, int action, int mods)
{
    if (action != GLFW_PRESS) return;

    String* pstr = (String*)glfwGetWindowUserPointer (window);

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose (window, STATUS_EXIT);
        break;

    case GLFW_KEY_ENTER:
        glfwSetWindowShouldClose (window, STATUS_DONE);
        break;

    case GLFW_KEY_BACKSPACE:
        if (!pstr->Empty ())
            pstr->Resize (pstr->Size () - 1);
        break;
    }

    if (std::isalpha (key) && !(mods & GLFW_MOD_SHIFT))
    {
        key = std::tolower (key);
    }

    if (CalibriFont::GetInstance().HasGlyph (key) && pstr->Length () < MAX_NAME_LEN)
    {
        pstr->Append ((char)key);
    }
}

void Application::Singleton::StageLogin ()
{
    logAssert (GlfwInit::GetInstance().IsLoaded ());
    logAssert (GladInit::GetInstance().IsLoaded ());
    logAssert (CalibriFont::GetInstance().IsLoaded ());

    GLFWwindow* window = GlfwInit::GetInstance().GetWindow ();
    glfwSetKeyCallback (window, KeyCallback);

    NewPtr<String> p_name = new String (MAX_NAME_LEN);
    glfwSetWindowUserPointer (window, p_name.GetPtr ());

    while (!glfwWindowShouldClose (window))
    {
        glfwPollEvents ();

        String text ("Enter name: ");
        text += *p_name;

        ClearScreen ();
        FVec2 origin (0.05f, 0.9f);
        CalibriFont::GetInstance().RenderText (origin, text.CStr ());
        glfwSwapBuffers (window);
    }

    RenderGeometryContainer::GetPlayer()->SetName (p_name->CStr ());

    int status = glfwWindowShouldClose (window);
    glfwSetWindowShouldClose (window, 0);
    if (status != STATUS_EXIT) StageMain ();
}
