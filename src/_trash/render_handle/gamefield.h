/* NOTE: has to be first preprocessor directive
 */
#include "../utils/utils.h"

#ifndef _GAMEFILED_H
#define _GAMEFILED_H

#include <glad.h>

#define GAMEFIELD_PROG_NAME "../res/shaders/gamefield"
#define GAMEFIELD_PROG_SHADERS "vf"

namespace cellwars
{
    /*! @brief Class used to render checked background
     */
    class gamefield
    {
    private:
        struct VS_IN
        {
            glm::vec2 pos;
        };

        enum {VBO_FIELD, VBO_CNT};
        enum {VAO_FIELD, VAO_CNT};

    public:
        /*! @brief Default ctor
         */
        gamefield () : vbo (vbo_array<VBO_CNT>::zeroes), vao (vao_array<VAO_CNT>::zeroes)
        {
        }

        /*! @brief Perform initialization
         *
         *  @param aspect_ratio Aspect ratio of window (calculated width/height).
         *  @return True/false on success/failure respectively.
         */
        bool load (float aspect_ratio)
        {
            line_spacing_vert = line_spacing_horz / aspect_ratio;

            unsigned max_vert_lines = glm::ceil (2.0f / (line_spacing_vert * min_scale)) + 2;
            unsigned max_horz_lines = glm::ceil (2.0f / (line_spacing_horz * min_scale)) + 2;
            unsigned max_vertices = (max_vert_lines + max_horz_lines) * 2;
            buf_cap = max_vertices * sizeof (VS_IN);

            vao.deferred_init ();
            vbo.deferred_init ();

            glBindVertexArray (vao[VAO_FIELD]);
            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_FIELD]);
            glBufferData (GL_ARRAY_BUFFER, buf_cap, nullptr, GL_DYNAMIC_DRAW);
            glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (VS_IN), (GLvoid*)offsetof (VS_IN, pos));
            glEnableVertexAttribArray (0);

            if (!prog.load (GAMEFIELD_PROG_NAME, GAMEFIELD_PROG_SHADERS))
            {
                return false;
            }

            return true;
        }

        /*! @brief Check if loading the object succeeded.
         */
        bool is_loaded ()
        {
            return prog.is_loaded ();
        }

        /*! @brief Render background
         *
         *  @param offset Lower left corner where to start drawing (in nds coordinates).
         *  @param scale Scale line spacing.
         *
         *  @remark @param scale should not be less than @ref min_scale, otherwise it will be clamped.
         */
        void render (glm::vec2 offset, float scale)
        {
            constexpr float epsilon = 1e-5;
            
            if (scale + epsilon < min_scale)
            {
                scale = min_scale;
            }

            const glm::vec4 white (1.0f, 1.0f, 1.0f, 1.0f);
            glClearBufferfv (GL_COLOR, 0, glm::value_ptr (white));

            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_FIELD]);
            glm::vec2* buf = (glm::vec2*)glMapBuffer (GL_ARRAY_BUFFER, GL_WRITE_ONLY);
            /* glm::vec2* buf = (glm::vec2*)glMapBufferRange (GL_ARRAY_BUFFER, 0, buf_cap, */
            /*         GL_WRITE_ONLY); */

            float vert_delta = line_spacing_vert * scale;
            float horz_delta = line_spacing_horz * scale;
            unsigned indices = 0;

            for (float v = -1.0 + offset.x; v + epsilon < 1.0; v += vert_delta)
            {
                buf[indices++] = glm::vec2 (v, -1.0f);
                buf[indices++] = glm::vec2 (v, 1.0f);
            }

            for (float h = -1.0 + offset.y; h + epsilon < 1.0; h += horz_delta)
            {
                buf[indices++] = glm::vec2 (-1.0f, h);
                buf[indices++] = glm::vec2 (1.0f, h);
            }

            glUnmapBuffer (GL_ARRAY_BUFFER);
            glBindVertexArray (vao[VAO_FIELD]);
            glUseProgram (prog);
            glDrawArrays (GL_LINES, 0, indices);
        }

    public:
        /*! @brief Horizontal line spacing used (in nds).
         */
        static constexpr float line_spacing_horz = 0.2f;

        /*! @brief Minimum supported scale
         *
         *  This limit is imposed not only to fix a buffer size
         *  but also to limit the amount of lines being rendered
         *  (i.e. for aesthetic purposed).
         */
        static constexpr float min_scale = 0.4f;

    private:
        cellwars::vbo_array<VBO_CNT> vbo;
        cellwars::vao_array<VAO_CNT> vao;
        cellwars::prog prog;
        float line_spacing_vert;
        unsigned buf_cap;
    };
};

#endif /* _GAMEFIELD_H */
