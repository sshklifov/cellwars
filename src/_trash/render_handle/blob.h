/* NOTE: has to be first preprocessor directive
 */
#include "../utils/utils.h"

#ifndef _BLOB_H
#define _BLOB_H

#include <glad.h>
#include "matrices.h"
#include <pthread.h>
#include <cstddef>

#define BLOB_PROG_NAME "../res/shaders/blob"
#define BLOB_PROG_SHADERS "vgf"

namespace cellwars
{

    /*! @brief Represents blobs (the pickups in the game)
     *
     *  This class will be used from both the graphical and client side of
     *  the application. First, the server will pass us some blobs but in
     *  a larger vicinity than our visibility. This is to avoid latency issues.
     *  Of course, it will be used by the graphical side, on the other hand, to
     *  actually render this information. Since these two operations will cause
     *  synchronisation problems, mutexes are used.
     */
    class blob
    {
    public:
        /*! @brief Per-vertex data for blob
         */
        struct VS_IN
        {
            /*! @brief Colour of blob.
             */
            glm::vec3 colour;

            /*! @brief Center of blob (in px).
             */
            glm::vec2 center;

            /*! @brief Radius of blob (in px).
             */
            float rad;
        };

    private:
        enum {VAO_BLOB, VAO_CNT};
        enum {VBO_BLOB, VBO_CNT};

    public:
        /*! @brief Default ctor
         */
        blob () : vbo (vbo_array<VBO_CNT>::zeroes), vao (vao_array<VAO_CNT>::zeroes)
        {
            num_blobs = 0;
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

            glBindVertexArray (vao[VAO_BLOB]);
            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_BLOB]);
            glBufferData (GL_ARRAY_BUFFER, sizeof (VS_IN) * max_blobs, nullptr, GL_DYNAMIC_DRAW);
            glVertexAttribPointer (0, 2, GL_FLOAT, GL_FALSE, sizeof (VS_IN), (GLvoid*)offsetof (VS_IN, center));
            glEnableVertexAttribArray (0);
            glVertexAttribPointer (1, 1, GL_FLOAT, GL_FALSE, sizeof (VS_IN), (GLvoid*)offsetof (VS_IN, rad));
            glEnableVertexAttribArray (1);
            glVertexAttribPointer (2, 4, GL_FLOAT, GL_FALSE, sizeof (VS_IN), (GLvoid*)offsetof (VS_IN, colour));
            glEnableVertexAttribArray (2);

            if (!prog.load (BLOB_PROG_NAME, BLOB_PROG_SHADERS))
            {
                return false;
            }

            GLint ubo_prog_loc = glGetUniformBlockIndex (prog, "matrices");
            glUniformBlockBinding (prog, ubo_prog_loc, matrices::binding_point);

            return true;
        }

        /*! @brief Check if loading the object succeeded.
         */
        bool is_loaded ()
        {
            return prog.is_loaded ();
        }

        /*! @brief Invalidate buffer data
         *
         *  This function should be called only by the client thread. It will update
         *  the information about blobs close-by. This information will be sent by
         *  the server.
         *
         *  @return Pointer to data.
         *  @remark It incoprporates mutexes so invalidation is coherent with OpenGL.
         */
        VS_IN* invalidate_data ()
        {
            pthread_mutex_lock (&mtx);

            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_BLOB]);

            return (VS_IN*)glMapBufferRange (GL_ARRAY_BUFFER, 0, sizeof (VS_IN) * max_blobs,
                    GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
        }

        /*! @brief Done invalidating memory
         *
         *  @param num_blobs Number of blobs written. Should not exceed @ref max_blobs.
         *
         *  @remark Calling this function will remove the prevously placed mutex.
         */
        void done (unsigned num_blobs)
        {
            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_BLOB]);
            glUnmapBuffer (GL_ARRAY_BUFFER);

            this->num_blobs = num_blobs;

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

            glBindBuffer (GL_ARRAY_BUFFER, vbo[VBO_BLOB]);

            return (VS_IN*)glMapBufferRange (GL_ARRAY_BUFFER, 0, sizeof (VS_IN) * max_blobs,
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
            glBindBuffer (GL_ARRAY_BUFFER, vao[VAO_BLOB]);
            glUnmapBuffer (GL_ARRAY_BUFFER);

            glBindVertexArray (vao[VAO_BLOB]);
            glUseProgram (prog);
            glDrawElements (GL_POINTS, size, GL_UNSIGNED_SHORT, indices);

            pthread_mutex_unlock (&mtx);
        }

        /*! @brief Get number of blobs currently in the buffer
         */
        unsigned count ()
        {
            return num_blobs;
        }

        /*! @brief Get maximum supported blobs.
         *
         *  @remark You could access blobs::max_blobs as well.
         */
        unsigned capacity ()
        {
            return max_blobs;
        }

    public:
        /*! @brief Maximum supported blobs.
         */
        static constexpr unsigned max_blobs = 100;

    private:
        cellwars::vbo_array<VBO_CNT> vbo;
        cellwars::vao_array<VAO_CNT> vao;
        cellwars::prog prog;
        pthread_mutex_t mtx;
        unsigned num_blobs;
    };
};

#endif /* _BLOB_H */
