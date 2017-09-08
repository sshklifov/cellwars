#include "render_handle.h"

#include <logger.h>
#include <glad.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace cellwars;

#define MAX_NICKNAME_LEN 15

/* Will hold the nickname
 */
char nickname[MAX_NICKNAME_LEN + 1] = {0};
unsigned nickname_len = 0;

/* Checks if our font library can render the character
 */
bool is_renderable (char c)
{
    return c >= 32 && c <= 126;
}

/* Catches input as a driver would (with typematic delay and rate).
 * Writes to the nickname buffer.
 */
void glfw_char_callback (GLFWwindow*, unsigned key)
{
    if (key == 8 && nickname_len != 0)
    {
        nickname[--nickname_len] = '\0';
    }

    if (is_renderable (key) && nickname_len < MAX_NICKNAME_LEN)
    {
        nickname[nickname_len++] = key;
    }
}

/* Different stage statuses:
 *
 * - STATUS_LOOP means "still in current stage"
 * - STATUS_EXIT means "exit application"
 * - STATUS_FINISHED means "continue to next stage"
 */
enum stage_status {STATUS_LOOP, STATUS_EXIT, STATUS_FINISHED};

bool render_handle::login ()
{
    glfwSetCharCallback (window, glfw_char_callback);

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

    /* Properties for the nickname prompt box
     */
    const char* text = "nickname:";
    glm::vec2 pos (0.05 * width, 0.7 * height);
    glm::vec3 colour = glm::vec3 (0.0, 0.0, 0.0);
    float psize = 25.0;

    /* Enter main loop.
     */
    stage_status status = STATUS_LOOP;
    while (status == STATUS_LOOP)
    {
        glfwPollEvents ();

        if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            status = STATUS_EXIT;
        }
        if (glfwGetKey (window, GLFW_KEY_ENTER) == GLFW_PRESS)
        {
            status = STATUS_FINISHED;
        }

        clear ();

        glm::vec2 end = font.render_text (text, colour, pos, psize);
        font.render_text (nickname, colour, end + glm::vec2 (10.0, 0.0), 15.0);

        glfwSwapBuffers (window);
    }

    glfwSetCharCallback (window, nullptr);
    return status == STATUS_FINISHED;
}
