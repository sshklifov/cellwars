#include "render_handle.h"
#include "matrices.h"
#include "blob.h"
#include "circle.h"
#include "gamefield.h"

#include <glad.h>
#include <logger.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* NOTE: The function surround by the preprocessor are only temporary.
 * They are currently used o supply some information to the application
 * so as to render more than a empty field.
 *
 * TODO: remove functions
 */

#if 1
void write_some_circles (cellwars::circle& c)
{
    cellwars::circle::VS_IN* p = (cellwars::circle::VS_IN*)c.invalidate_data ();

    p[0].center = glm::vec2 (200.0, 100.0);
    p[0].rad = 100.0;
    p[0].colour = glm::vec3 (1.0, 0.0, 0.0);

    p[1].center = glm::vec2 (1300.0, 100.0);
    p[1].rad = 300.0;
    p[1].colour = glm::vec3 (0.0, 1.0, 0.0);

    p[2].center = glm::vec2 (300.0, 1100.0);
    p[2].rad = 50.0;
    p[2].colour = glm::vec3 (0.0, 0.0, 1.0);

    p[3].center = glm::vec2 (0.0, 0.0);
    p[3].rad = 150.0;
    p[3].colour = glm::vec4 (1.0, 1.0, 0.0, 1.0);

    c.done (4);
}

void change_player_rad (cellwars::circle& c, float delta)
{
    cellwars::circle::VS_IN* p = (cellwars::circle::VS_IN*)c.invalidate_data ();

    p[3].rad += delta;
    p[3].rad = glm::clamp (p[3].rad, 0.0f, 500.0f);

    c.done (4);
}

void render_some_circles (cellwars::circle& c)
{
    GLushort indices[] = {0, 1, 2, 3};

    (void)c.prep_render ();
    c.render_indirect (indices, 4);
}

void write_some_blobs (cellwars::blob& b)
{
    cellwars::blob::VS_IN* p = (cellwars::blob::VS_IN*)b.invalidate_data ();

    p[0].center = glm::vec2 (20.0, 100.0);
    p[0].rad = 20.0;
    p[0].colour = glm::vec4 (1.0, 1.0, 0.0, 1.0);

    p[1].center = glm::vec2 (15.0, 12.0);
    p[1].rad = 20.0;
    p[1].colour = glm::vec4 (0.0, 1.0, 0.0, 1.0);

    p[2].center = glm::vec2 (1300.0, 1100.0);
    p[2].rad = 20.0;
    p[2].colour = glm::vec4 (0.0, 0.0, 1.0, 1.0);

    b.done (3);
}

void render_some_blobs (cellwars::blob& b)
{
    GLushort indices[] = {0, 1, 2};

    (void)b.prep_render ();
    b.render_indirect (indices, 3);
}
#endif

/* stage_login initialized these global variables (and wrote to them)
 */
extern char nickname[];
extern unsigned nickname_len;

bool cellwars::render_handle::main ()
{
    /* Initialize classes
     */

    cellwars::matrices matrices;
    matrices.init (width, height);

    cellwars::circle circles;
    if (!circles.load ())
    {
        return false;
    }

    cellwars::blob blobs;
    if (!blobs.load ())
    {
        return false;
    }

    cellwars::gamefield gamefield;
    if (!gamefield.load ((float)width / (float)height))
    {
        return false;
    }

    /* Call our 'temporary' functions to feed some information.
     */

    write_some_circles (circles);
    write_some_blobs (blobs);

    /* Clears OpenGL buffers. For colour, a defualt white bg is used.
     * For deph, since we are using GL_LESS, we need to clear to the
     * least priority depth value (one).
     */
    auto clear = []()
    {
        glm::vec4 white (1.0, 1.0, 1.0, 1.0);
        glClearBufferfv (GL_COLOR, 0, glm::value_ptr (white));

        float one = 1.0f;
        glClearBufferfv (GL_DEPTH, 0, &one);
    };

    /* Stores player position (important).
     */
    glm::vec2 player (width / 2.0f, height / 2.0f);

    /* Stores the center pixel in window coordinates. Used
     * to calculate the direction in which the player is heading,
     * the translation matrix and for rendering the gamefield
     * background.
     */
    glm::vec2 origin (width / 2.0f, height / 2.0f);

    glfwSetTime (0.0);
    while (!glfwWindowShouldClose (window))
    {
        constexpr float velocity = 200.0;
        float elapsed_time = glfwGetTime ();
        glfwSetTime (0.0);

        glfwPollEvents ();

        if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose (window, true);
        }
        if (glfwGetKey (window, GLFW_KEY_W) == GLFW_PRESS)
        {
            change_player_rad (circles, 10.0f);
        }
        if (glfwGetKey (window, GLFW_KEY_S) == GLFW_PRESS)
        {
            change_player_rad (circles, -10.0f);
        }

        /* Get cursor position
         */
        glm::dvec2 cursor;
        glfwGetCursorPos (window, &cursor.x, &cursor.y);
        cursor.y = height - cursor.y;

        glm::vec2 dir = (glm::vec2)cursor - origin;
        float len = glm::sqrt (dir.x * dir.x + dir.y * dir.y);

        /*! If it is fairly in the center of the screen, don't move
         */
        if (len > 15.0)
        {
            dir /= len;

            /* Update player position
             */
            player += dir * elapsed_time * velocity;
            player.x = glm::clamp (player.x, 0.0f, 3.0f * width);
            player.y = glm::clamp (player.y, 0.0f, 2.0f * height);
        }

        /* Since the user is considered as a cellwars::circle and we change his/her
         * position, we need to update the class data as well. This is quite
         * inefficient in OpenGL driver terms and is only a temporary solution.
         *
         * TODO fix
         */
        cellwars::circle::VS_IN* ptr = circles.invalidate_data ();
        ptr[3].center = player;
        circles.done (4);

        /* After calculating the new player position, update the translating matrix
         */
        matrices.trans_ref () = origin - player;
        matrices.coherent_update (matrices::TRANS);

        /* Calculate where the offset of the background grid.
         *
         * TODO: put this inside a function or better yet: implement inside the class
         */
        glm::vec2 lower_left = player - origin;
        float line_spacing = (height / 2.0f) * gamefield::line_spacing_horz;

        float offset_x = line_spacing - glm::mod (lower_left.x, line_spacing);
        float offset_y = line_spacing - glm::mod (lower_left.y, line_spacing);

        offset_x = offset_x * (2.0f / width) - 1.0f;
        offset_y = offset_y * (2.0f / height) - 1.0f;
        glm::vec2 offset (offset_x, offset_y);

        clear ();

        /* Call the class's render functions. They are require performing
         * clipping but we shaw leave the GPU to do that.
         *
         * TODO: implement clipping.
         */
        gamefield.render (offset, 1.0f);
        render_some_blobs (blobs);
        render_some_circles (circles);

        /* Render player name and position
         */
        char buf[2048];
        snprintf (buf, 2048, "%s: (%.1f, %.1f)", nickname, player.x, player.y);
        font.render_text (buf, glm::vec3 (0.0, 0.0, 0.0), glm::vec2 (50.0, 50.0), 15.0);

        glfwSwapBuffers (window);
    }

    return true;
}
