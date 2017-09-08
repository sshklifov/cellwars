#ifndef _TEX_ARRAY_H
#define _TEX_ARRAY_H

#include <glad.h>
#include <logger.h>

namespace cellwars
{
    /*! @brief Wrapper for texture objects.
     *
     *  This class is used to store the texture id's returned from OpenGL calls.
     *  It will also automatically perform cleanup on them.
     */
    template <unsigned N>
    class tex_array
    {
    public:
        /*! @brief Flags to supply to the constructor.
         *
         *  Currently, only zeroes is supported. It will make the ctor refrain from
         *  making any gl commands. This is very usefull if glad hasn't been initialized
         *  as otherwise the programme will crash (or at the very least fail the gl command).
         */
        enum flags {zeroes};

    public:
        /*! @brief Default ctor.
         *
         *  Initializes N texture's.
         */
        tex_array ()
        {
            glGenTextures (N, tex);
        }

        /*! @brief Ctor with supplied flags.
         */
        tex_array (flags) : tex {0}
        {

        }

        /*! @brief No copy constructor.
         *
         *  Performing a deep coppy is sort of not needed. Not to mention
         *  not wanted.
         */
        tex_array (const tex_array&) = delete;


        /*! @brief No move constructor.
         *
         *  Can't even be implemented. If this function is to be invoked,
         *  then you are something wrong.
         */
        tex_array (tex_array&&) = delete;

        /*! @brief Desctuctor.
         *
         *  Performes cleanup as promised when object goes out-of-scope.
         */
        ~tex_array ()
        {
            glDeleteTextures (N, tex);
        }

        /*! @brief Generate texture id's
         *
         *  Generate texture id's. This function should only be called on the object
         *  if it has been constructed with the zeroes @sa @ref flags. It is like a
         *  defered call to the constructor. Hence the name.
         */
        void deferred_init ()
        {
            glGenTextures (N, tex);
        }

        /*! @brief Access individual texture id.
         *
         *  @remark If compiled without -DNDEBUG, it will check for the validity of @param index
         */
        GLuint operator [] (unsigned index)
        {
#ifndef NDEBUG
            if (index >= N)
            {
                logWarn ("Indexing out-of-bounds tex_array (size: %d, index: %d)", N, index);
            }
#endif
            return tex[index];
        }

    private:
        GLuint tex[N];
    };
};

#endif /* _TEX_ARRAY_H */

