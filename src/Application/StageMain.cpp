#include "Application.h"
#include "Arena.h"
#include "RenderGeometry.h"
#include "CalibriFont.h"
#include "Bot.h"

#include <RenderUtils/GlfwInit.h>
#include <RenderUtils/Matrices.h>
#include <Container/StringStream.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/random.hpp>
using namespace Cellwars;

static void KeyCallback (GLFWwindow* window, int key, int, int, int)
{
    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose (window, 1);
        break;
    }
}

static void ScrollCallback (GLFWwindow*, double, double yoffset)
{
    constexpr float speed = 0.01f;
    constexpr float max_zoom = 1.5f;
    constexpr float min_zoom = 0.3f;

    float zoom_x = Matrices::GetInstance().GetScaleMatrix()[0][0];
    float zoom_y = Matrices::GetInstance().GetScaleMatrix()[1][1];

    zoom_x += speed * yoffset;
    zoom_x = glm::clamp (zoom_x, min_zoom, max_zoom);

    zoom_y += speed * yoffset;
    zoom_y = glm::clamp (zoom_y, min_zoom, max_zoom);

    Matrices::GetInstance().SetScaleMatrix (glm::scale (glm::mat4 (1.f), glm::vec3 (zoom_x, zoom_y, 1.f)));
}

static void UpdatePlayerPos (float elapsed_time)
{
    constexpr float velocity = 150.f;
    constexpr float threshold2 = 100;

    double xpos, ypos;
    glfwGetCursorPos (GlfwInit::GetInstance().GetWindow (), &xpos, &ypos);
    ypos = GlfwInit().GetInstance().GetHeight () - ypos;

    FPoint2 origin (GlfwInit().GetInstance().GetWidth () / 2.f, GlfwInit().GetInstance().GetHeight () / 2.f);
    FVec2 dir = Direction (origin, FPoint2 (xpos, ypos));
    if (dir.Distance2 () < threshold2) return;
    dir.Normalize ();

    RenderCircle* player = RenderGeometryContainer::GetPlayer ();

    FPoint2 center = Cellwars::Translate (player->GetCenter (), dir * elapsed_time * velocity);
    Arena::GetInstance().Clamp (center);
    player->SetCenter (center);

    FVec2 trans = Direction (center, origin);
    Matrices::GetInstance().SetTranslateMatrix (glm::translate (glm::mat4 (1.f), glm::vec3 (trans.x, trans.y, 1.f)));
}

static void RenderPlayerPos ()
{
    RenderCircle* player = RenderGeometryContainer::GetPlayer ();

    OutputStringStream ss;
    ss << player->GetName () << " at position (" << (int)player->GetCenter().x << ", ";
    ss << (int)player->GetCenter().y << ")";

    const FVec2 pos (0.1f, 0.1f);
    CalibriFont::GetInstance().RenderText (pos, ss.CStr ());
}

static void WriteSomeBlobs ()
{
    constexpr unsigned num_blobs = 100;
    for (unsigned i = 0; i < num_blobs; ++i)
    {
        FPoint2 pos;
        pos.x = glm::linearRand (0.f, Arena::GetInstance().GetWidth());
        pos.y = glm::linearRand (0.f, Arena::GetInstance().GetHeight());

        FVec3 colour;
        colour.x = glm::linearRand (0.f, 1.f);
        colour.y = glm::linearRand (0.f, 1.f);
        colour.z = glm::linearRand (0.f, 1.f);

        RenderBlob* blob = new RenderBlob (pos, colour);
        RenderGeometryContainer::GetInstance().PushBack (blob);
    }
}

static void InitializeRenderGeometryContainer ()
{
    RenderCircle* player = RenderGeometryContainer::GetPlayer ();
    player->SetCenter (FPoint2 (500.f, 500.f));
    player->SetRad (50.f);
    player->SetColour (FVec3 (0.25f, 0.52f, 0.09f));

    RenderGeometryContainer::GetInstance().PushBack (new RenderLines);

    WriteSomeBlobs ();
}

void Application::Singleton::StageMain ()
{
    GLFWwindow* window = GlfwInit::GetInstance().GetWindow ();

    glfwSetKeyCallback (window, KeyCallback);
    glfwSetScrollCallback (window, ScrollCallback);

    constexpr unsigned num_bots = 10;
    Bot bot[10];

    InitializeRenderGeometryContainer ();
    RenderGeometryContainer::GetInstance().Sort ();

    double prev_time = glfwGetTime ();
    while (!glfwWindowShouldClose (window))
    {
        double curr_time = glfwGetTime ();
        double elapsed_time = curr_time - prev_time;
        prev_time = curr_time;

        UpdatePlayerPos (elapsed_time);
        for (unsigned i = 0; i < num_bots; ++i)
            bot[i].UpdatePosition (elapsed_time);

        glfwPollEvents ();
        Matrices::GetInstance().CoherentUpdate ();

        ClearScreen ();
        RenderGeometryContainer::GetInstance().Render ();
        RenderPlayerPos ();
        
        glfwSwapBuffers (window);
    }
}
