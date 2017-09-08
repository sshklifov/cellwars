/* NOTE: has to be first preprocessor directive
 */
#include "../utils/utils.h"

#ifndef _CIRCLE_H
#define _CIRCLE_H

#include <glad.h>
#include "matrices.h"
#include <pthread.h>
#include <cstdlib>

#define CIRCLE_PROG_NAME "../res/shaders/circle"
#define CIRCLE_PROG_SHADERS "vgf"

namespace cellwars
{
    /*! @brief Represents players
     *
     *  This class will be used from both the graphical and client side of
     *  the application. First, the server will pass us some cirles but in
     *  a larger vicinity than our visibility. This is to avoid latency issues.
     *  Of course, it will be used by the graphical side, on the other hand, to
     *  actually render this information. Since these two operations will cause
     *  synchronisation problems, mutexes are used.
     */
    class circle
    {
    public:
        /*! @brief Per-vertex data for circle
         */
        struct VS_IN
        {
            /*! @brief Colour of circle.
             */
            glm::vec3 colour;

            /*! @brief Center of circle (in px).
             */
            glm::vec2 center;

            /*! @brief Radius of circle (in px).
             */
            float rad;
        };

    private:
        enum {VAO_CIRCLE, VAO_CNT};
        enum {VBO_CIRCLE, VBO_CNT};
        enum {TEX_CIRCLE, TEX_CNT};

    public:
        /*! @brief Default ctor
         */
        circle () : vbo (vbo_array<VBO_CNT>::zeroes), vao (vao_array<VAO_CNT>::zeroes), tex (tex_array<TEX_CNT>::zeroes)
        {
            num_circles = 0;
            mtx = PTHREAD_MUTEX_INITIALIZER;
        }

        /*! @brief Initialize object.
         *
         *  @return True/false on sucess/failure.
         */
        bool load ()
        {
            vao.deferred_init ();
            vbo.deferred_init ();

            glBindVertexArray (vao[VAO_CIRCLE]);
            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_CIRCLE]);
            glBufferData (GL_ARRAY_BUFFER, sizeof (VS_IN) * max_circles, nullptr, GL_DYNAMIC_DRAW);
            glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (VS_IN), (GLvoid*)offsetof (VS_IN, center));
            glEnableVertexAttribArray (0);
            glVertexAttribPointer (1, 1, GL_FLOAT, GL_FALSE, sizeof (VS_IN), (GLvoid*)offsetof (VS_IN, rad));
            glEnableVertexAttribArray (1);
            glVertexAttribPointer (2, 3, GL_FLOAT, GL_FALSE, sizeof (VS_IN), (GLvoid*)offsetof (VS_IN, colour));
            glEnableVertexAttribArray (2);

            if (!prog.load (CIRCLE_PROG_NAME, CIRCLE_PROG_SHADERS))
            {
                return false;
            }

            GLint ubo_prog_loc = glGetUniformBlockIndex (prog, "matrices");
            glUniformBlockBinding (prog, ubo_prog_loc, matrices::binding_point);

            /* TODO: antialiasing */

            glBindTexture (GL_TEXTURE_2D, tex[0]);
            for (unsigned dim = max_mipmap_dim, level = 0; dim != 0; dim /= 2, ++level)
            {
                byte* buf = (byte*)calloc (dim * dim, 1);

                for (unsigned t = 0; t < dim; ++t)
                {
                    for (unsigned s = 0; s < dim; ++s)
                    {
                        glm::uvec2 origin (dim / 2, dim / 2);
                        glm::uvec2 pixel = glm::uvec2 (s, t);
                        glm::uvec2 v = pixel - origin;

                        float dst2 = v.x * v.x + v.y * v.y;
                        float edge0 = (dim * dim / 4) * 0.95;
                        float edge1 = edge0 * 1.05;
                        float alpha = 1.0f - glm::smoothstep (edge0, edge1, dst2);

                        unsigned coord_1d = s + t * dim;
                        buf[coord_1d] = alpha * 255;
                    }
                }

                glTexImage2D (GL_TEXTURE_2D, level, GL_RED, dim, dim, 0, GL_RED, GL_UNSIGNED_BYTE, buf);

                free (buf);
            }

            return true;
        }

        /*! @brief Check if loading the object succeeded.
         */
        bool is_loaded ()
        {
            return prog.is_loaded ();
        }

        void render ()
        {
        }

        /*! @brief Invalidate buffer data
         *
         *  This function should be called only by the client thread. It will update
         *  the information about circles close-by. This information will be sent from
         *  the server.
         *
         *  @return Pointer to data.
         *  @remark It incoprporates mutexes so invalidation is coherent with OpenGL.
         */
        VS_IN* invalidate_data ()
        {
            pthread_mutex_lock (&mtx);

            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_CIRCLE]);

            return (VS_IN*)glMapBufferRange (GL_ARRAY_BUFFER, 0, sizeof (VS_IN) * max_circles,
                    GL_MAP_WRITE_BIT); // | GL_MAP_INVALIDATE_BUFFER_BIT);
        }

        /*! @brief Done invalidating memory
         *
         *  @param num_circles Number of circles written. Should not exceed @ref max_circles.
         *
         *  @remark Calling this function will remove the prevously placed mutex.
         */
        void done (unsigned num_circles)
        {
            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_CIRCLE]);
            glUnmapBuffer (GL_ARRAY_BUFFER);

            this->num_circles = num_circles;

            pthread_mutex_unlock (&mtx);
        }

        /*! @brief Prepare to render
         *
         *  Since the server sent us more information than will be needed. it would be
         *  optimal to perform some sort of custom clipping, as opposed to leave the
         *  driver clip 70% of the geometry. So all this function does is pass you
         *  a pointer and leave you do the clipping. Why? Because we do not know the
         *  position of the player.
         */
        const VS_IN* prep_render ()
        {
            pthread_mutex_lock (&mtx);

            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_CIRCLE]);

            return (VS_IN*)glMapBufferRange (GL_ARRAY_BUFFER, 0, sizeof (VS_IN) * max_circles,
                    GL_MAP_READ_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
        }

        /*! @brief Render circles
         *
         *  So once you determinted which vertices to render via @ref prep_render,
         *  just pass their indices to this function and it will do the rest.
         *
         *  @param indices Pointer to indicies to pass to glDrawElements
         *  @param size The size of the passed array
         *
         *  @remark You should call @ref prep_render first.
         */
        void render_indirect (GLushort* indices, unsigned size)
        {
            glBindBuffer (GL_ARRAY_BUFFER, vao[VAO_CIRCLE]);
            glUnmapBuffer (GL_ARRAY_BUFFER);

            glBindVertexArray (vao[VAO_CIRCLE]);
            glUseProgram (prog);
            glActiveTexture (GL_TEXTURE0);
            glBindTexture (GL_TEXTURE_2D, tex[TEX_CIRCLE]);
            glDrawElements (GL_POINTS, size, GL_UNSIGNED_SHORT, indices);

            pthread_mutex_unlock (&mtx);
        }

        /*! @brief Get number of circles currently in the buffer
         */
        unsigned count ()
        {
            return num_circles;
        }

        /*! @brief Get maximum supported circles.
         *
         *  @remark You could access circle::max_circles as well.
         */
        unsigned capacity ()
        {
            return max_circles;
        }

    public:
        /*! @brief Get maximum supported circles.
         */
        static constexpr unsigned max_circles = 25;

        /*! @brief Get the dimention of mipmap 0 of the texture used to render circles
         */
        static constexpr unsigned max_mipmap_dim = 2048;

    private:
        cellwars::vbo_array<VBO_CNT> vbo;
        cellwars::vao_array<VAO_CNT> vao;
        cellwars::tex_array<TEX_CNT> tex;
        cellwars::prog prog;
        pthread_mutex_t mtx;
        unsigned num_circles;
    };
};

#endif /* _CIRCLE_H */
