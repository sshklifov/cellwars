#ifndef _VBO_ARRAY_H
#define _VBO_ARRAY_H

#include <glad.h>
#include <logger.h>

namespace cellwars
{
    /*! @brief Wrapper for vertex buffer objects.
     *
     *  This class is used to store the vbo id's returned from OpenGL calls.
     *  It will also automatically perform cleanup on them.
     */
    template <unsigned N>
    class vbo_array
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
         *  Initializes N vbo's.
         */
        vbo_array ()
        {
            glGenBuffers (N, vbo);
        }

        /*! @brief Ctor with supplied flags.
         */
        vbo_array (flags) : vbo{0}
        {
        }

        /*! @brief No copy constructor.
         *
         *  Performing a deep coppy is sort of not needed. Not to mention
         *  not wanted.
         */
        vbo_array (const vbo_array&) = delete;

        /*! @brief No move constructor.
         *
         *  Can't even be implemented. If this function is to be invoked,
         *  then you are something wrong.
         */
        vbo_array (vbo_array&&) = delete;

        /*! @brief Desctuctor.
         *
         *  Performes cleanup as promised when object goes out-of-scope.
         */
        ~vbo_array ()
        {
            glDeleteBuffers (N, vbo);
        }

        /*! @brief Generate vbo id's
         *
         *  Generate vbo id's. This function should only be called on the object
         *  if it has been constructed with the zeroes @sa @ref flags. It is like a
         *  defered call to the constructor. Hence the name.
         */
        void deferred_init ()
        {
            glGenBuffers (N, vbo);
        }

        /*! @brief Access individual vbo id.
         *
         *  @remark If compiled without -DNDEBUG, it will check for the validity of @param index
         */
        GLuint operator [] (unsigned index)
        {
#ifndef NDEBUG
            if (index >= N)
            {
                logWarn ("Indexing out-of-bounds vbo_array (size: %d, index: %d)", N, index);
            }
#endif
            return vbo[index];
        }

    private:
        GLuint vbo[N];
    };
};

#endif /* _VBO_ARRAY_H */
