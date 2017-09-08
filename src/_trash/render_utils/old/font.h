#ifndef _FONT_H
#define _FONT_H

#include <glad.h>
#include <logger.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "atlas.h"

#define FONT_PATH "../res/font/font.ttf"
#define FONT_PROG_NAME "../res/shaders/text"
#define FONT_PROG_SHADERS "vgf"

namespace cellwars
{
    /*! @brief Renders text to the sceen.
     */
    class font
    {
    private:
        struct gslot
        {
            glm::vec2 leftbot;
            glm::vec2 s_size;
            glm::uvec2 tex_coord;
            glm::uvec2 t_size;
        };

        enum {VAO_TEXT, VAO_CNT};
        enum {VBO_TEXT, VBO_CNT};
        enum {TEX_TEXT, TEX_CNT};

    public:
        /*! @brief Default ctor
         */
        font () : vbo (vbo_array<VBO_CNT>::zeroes), vao (vao_array<VAO_CNT>::zeroes), tex (tex_array<TEX_CNT>::zeroes)
        {
        }

        /*! @brief Perform initialization
         *
         *  @param width Width of window in pixels
         *  @param height Height of window in pixels.
         *  @param dpi_horz Horizontal dpi of monitor.
         *  @param dpi_vert Vertical dpi of monitor.
         *  @return True/false on success/failure respectively.
         */
        bool load (unsigned width, unsigned height, float dpi_horz, float dpi_vert)
        {
            for (unsigned i = 0; i < layers; ++i)
            {
                if (!mipmap[i].load (FONT_PATH, dpi_horz, dpi_vert, sizes[i]))
                {
                    free ();
                    return false;
                }
            }

            if (!prog.load (FONT_PROG_NAME, FONT_PROG_SHADERS))
            {
                free ();
                return false;
            }

            vao.deferred_init ();
            vbo.deferred_init ();
            tex.deferred_init ();

            glBindVertexArray (vao[VAO_TEXT]);
            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_TEXT]);
            glBufferData (GL_ARRAY_BUFFER, max_text_len * sizeof (font::gslot), nullptr, GL_DYNAMIC_DRAW);
            glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (font::gslot), (GLvoid*)offsetof (font::gslot, leftbot));
            glEnableVertexAttribArray (0);
            glVertexAttribPointer (1, 2, GL_FLOAT, GL_FALSE, sizeof (font::gslot), (GLvoid*)offsetof (font::gslot, s_size));
            glEnableVertexAttribArray (1);
            glVertexAttribIPointer (2, 2, GL_UNSIGNED_INT, sizeof (font::gslot), (GLvoid*)offsetof (font::gslot, tex_coord));
            glEnableVertexAttribArray (2);
            glVertexAttribIPointer (3, 2, GL_UNSIGNED_INT, sizeof (font::gslot), (GLvoid*)offsetof (font::gslot, t_size));
            glEnableVertexAttribArray (3);

            glBindTexture (GL_TEXTURE_2D, tex[TEX_TEXT]);
            glTexImage2D (GL_TEXTURE_2D, 0, GL_RED, 1024, 1024 * layers, 0, GL_RED, GL_UNSIGNED_BYTE, nullptr);

            /* for (unsigned i = 0; i < layers; ++i) */
            /* { */
            /*     glTexSubImage2D (GL_TEXTURE_2D, 0, 0, 1024 * i, 1024, 1024, GL_RED, GL_UNSIGNED_BYTE, mipmap[i].get_ctex ()); */
            /*     mipmap[i].free_tex (); */
            /* } */

            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glm::mat4 projection = glm::ortho (0.0f, (float)width, 0.0f, (float)height);
            GLuint proj_loc = glGetUniformLocation (prog, "projection");
            glUseProgram (prog);
            glUniformMatrix4fv (proj_loc, 1, GL_FALSE, glm::value_ptr (projection));

            colour_loc = glGetUniformLocation (prog, "text_colour");

            logDebug ("successfully loaded font %s", FONT_PATH);

            return true;
        }

        /*! @brief Check if loading the font succeeded.
         *
         *  @remark If @ref load has not been called, then this function will return false.
         */
        bool is_loaded () const
        {
            return prog.is_loaded ();
        }

        /*! @brief Release resources early (before going out-of-scope)
         */
        void free ()
        {
            for (unsigned i = 0; i < layers; ++i)
            {
                mipmap[i].free ();
            }

            prog.free ();
        }

        /*! @brief Render some text to screen
         *
         *  @param text String of text to render
         *  @param colour What colour should the text be
         *  @param origin Where the text should start (lower left corner)
         *  @param psize Point size of text.
         *  @return Where the text rendering ended (lower-right corner).
         *
         *  @remark Length of text should not exceed @ref max_text_len
         */
        glm::vec2 render_text (const char* text, glm::vec3 colour, glm::vec2 origin, float psize)
        {
#ifndef NDEBUG
            /* Check if the string is indeed the correct size.
             */
            unsigned len = 0;
            while (text[len++] != '\0');

            if (len > max_text_len)
            {
                logError ("supplied %u characters, limit is %u", len, max_text_len);
            }
#endif
            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_TEXT]);
            font::gslot* buf = (font::gslot*)glMapBufferRange (GL_ARRAY_BUFFER, 0, max_text_len * sizeof (font::gslot),
                    GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

            unsigned level = get_level (psize);
            float scale = get_scale (level, psize);

            unsigned i;
            for (i = 0; text[i] != '\0'; ++i)
            {
                unsigned id = text[i] - ' ';
                const atlas::gslot& curr = mipmap[level].get_cmeta ()[id];

                buf[i].leftbot.x = origin.x + curr.lefttop.x * scale;
                buf[i].leftbot.y = origin.y + (curr.lefttop.y - (signed)curr.size.y) * scale;

                buf[i].s_size = (glm::vec2)curr.size * scale;
                buf[i].t_size = curr.size;

                buf[i].tex_coord.s = (id % 16) * 64;
                buf[i].tex_coord.t = (id / 16) * 64 + level * 1024;

                origin.x += curr.advance * scale;
            }

            glUnmapBuffer (GL_ARRAY_BUFFER);
            glBindVertexArray (vao[VAO_TEXT]);
            glUseProgram (prog);
            glUniform3fv (colour_loc, 1, glm::value_ptr (colour));
            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, tex[TEX_TEXT]);
            glDrawArrays (GL_POINTS, 0, i);

            return origin;
        }

   private:
        static unsigned get_level (float psize)
        {
            if (psize < 17.0)
            {
                return 0;
            }
            else if (psize < 22.0)
            {
                return 1;
            }
            else
            {
                return 2;
            }
        }

        static float get_scale (unsigned level, float psize)
        {
            return psize / sizes[level];
        }

    public:
        /*! @brief Maximum suppored text length.
         */
        static constexpr unsigned max_text_len = 100;

    private:
        static constexpr unsigned layers = 4;
        static constexpr float sizes[layers] = {15.0, 18.0, 30.0};

    private:
        cellwars::atlas mipmap[layers];
        cellwars::prog prog;
        cellwars::vbo_array<1> vbo;
        cellwars::vao_array<1> vao;
        cellwars::tex_array<1> tex;
        GLuint colour_loc;
    };
};

#endif /* _FONT_H */
