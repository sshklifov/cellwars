/* NOTE: has to be first preprocessor directive
 */
#include "../utils/utils.h"

#ifndef _MATRICES_H
#define _MATRICES_H

#include <glad.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cellwars
{
    /*! @brief Handles matrices
     *
     *  Since there are going to be a lot of programmes that
     *  would need to access transformation matrices, i.e.
     *  projection, scale, translate and mvp for the combined
     *  transformations, this class will be in charge of
     *  updating and storing them. A UBO will be used for this
     *  matter, and the defualt binding point of 0 will be
     *  used (see @ref binding_point).
     */
    class matrices
    {
    private:
        enum {PROJ = 1};
    public:
        /*! @brief Flags to pass to @ref coherent_update
         */
        enum flags {SCALE = 0, TRANS = 2, MVP = 3, TOTAL};

    public:
        /*! @brief Default ctor
         *
         *  Will initialize the matrices to the identity.
         */
        matrices ()
        {
            ubo = 0;
            scale = 1.0f;
            to_origin = glm::vec2 (0.0f, 0.0f);
        }


        /*! @brief No copy ctor.
         */
        matrices (const matrices&) = delete;

        /*! @brief No move ctor.
         */
        matrices (matrices&&) = delete;

        /*! @brief Destructor.
         *
         *  Performes cleanup as promised when object goes out-of-scope.
         */
        ~matrices ()
        {
            glDeleteBuffers (1, &ubo);
        }

        /*! @brief Perform initialization
         *
         *  Note that this member function is called init, as opposed
         *  to the standard naming scheme load & is_loaded. Well, since
         *  this "loading" can't fail, there is no point in returned
         *  anything (and including the is_loaded function). So, to
         *  differentiate it from them, it has a different name.
         *
         *  @param width Width of window in pixels.
         *  @param height Height of window in pixels.
         */
        void init (unsigned width, unsigned height)
        {
            glGenBuffers (1, &ubo);
            glBindBufferBase (GL_UNIFORM_BUFFER, binding_point, ubo);
            glBufferData (GL_UNIFORM_BUFFER, sizeof (glm::mat4) * matrices::TOTAL, nullptr, GL_DYNAMIC_DRAW);

            glm::mat4 proj = glm::ortho (0.0f, (float)width, 0.0f, (float)height);
            glm::mat4 id = glm::mat4 (1.0f);

            glm::mat4* buf = (glm::mat4*)glMapBuffer (GL_UNIFORM_BUFFER, GL_WRITE_ONLY);

            buf[matrices::SCALE] = id;
            buf[matrices::PROJ] = proj;
            buf[matrices::TRANS] = id;
            buf[matrices::MVP] = proj;

            glUnmapBuffer (GL_UNIFORM_BUFFER);
        }

        /*! @brief Get reference to scale factor
         *
         *  Can be used to update or just view the current scale.
         *  Most of the cases, the scale will be increased by a
         *  fixed amount, so instead of writing getters/setters,
         *  this is an easier way and more elegant (?) way of
         *  accessing/modifying the scale.
         *
         *  @remark A single float is returned as opposed to a mat4.
         */
        float& scale_ref ()
        {
            return scale;
        }

        /*! @brief Get reference to translate vector
         *
         *  For the reasons stated in @ref scale_ref, this function
         *  returnes a reference to the vector used for translation.
         *
         *  @remark Returns a vec2 as opposed to a mat4.
         */
        glm::vec2& trans_ref ()
        {
            return to_origin;
        }

        /*! @brief Update matrices.
         *
         *  If one of @ref scale_ref or @ref trans_ref has been used
         *  to update either matrix, then this function should be called
         *  to reflect the changes (notify OpenGL about them). Note
         *  the coherent part of the name. This means that the update
         *  is coherent with OpenGL. Since coherent mapping is not allowed
         *  in OpenGL 3.3 (which is our targeted version), it us up to the
         *  user to assure that no glDraw* function is running.
         *
         *  @param flags Which matrices to update
         */
        void coherent_update (int flags)
        {
            glBindBufferBase (GL_UNIFORM_BUFFER, binding_point, ubo);
            glm::mat4* buf = (glm::mat4*)glMapBufferRange (GL_UNIFORM_BUFFER, 0, sizeof (glm::mat4) * matrices::TOTAL,
                    GL_MAP_WRITE_BIT);

            if (flags & matrices::SCALE)
            {
                buf[matrices::SCALE] = glm::scale (glm::mat4 (1.0f), glm::vec3 (scale, scale, 1.0f));
                flags |= matrices::MVP;
            }

            if (flags & matrices::TRANS)
            {
                buf[matrices::TRANS] = glm::translate (glm::mat4 (1.0f), glm::vec3 (to_origin, 1.0f));
                flags |= matrices::MVP;
            }

            if (flags & matrices::MVP)
            {
                buf[matrices::MVP] = buf[matrices::SCALE] * buf[matrices::PROJ] * buf[matrices::TRANS];
            }

            glUnmapBuffer (GL_UNIFORM_BUFFER);
        }

    public:
        /*! @brief Binding point used for matrices
         */
        static constexpr GLuint binding_point = 0;

    private:
        GLuint ubo;
        float scale;
        glm::vec2 to_origin;
    };
};

#endif /* _MATRICES_H */
