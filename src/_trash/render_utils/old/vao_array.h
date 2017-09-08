#ifndef _VAO_ARRAY_H
#define _VAO_ARRAY_H

#include <glad.h>
#include <logger.h>

namespace cellwars
{
    /*! @brief Wrapper for vertex array objects.
     *
     *  This class is used to store the vao id's returned from OpenGL calls.
     *  It will also automatically perform cleanup on them.
     */
    template <unsigned N>
    class vao_array
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
         *  Initializes N vao's.
         */
        vao_array ()
        {
            glGenVertexArrays (N, vao);
        }

        /*! @brief Ctor with supplied flags.
         */
        vao_array (flags) : vao {0}
        {
        }

        /*! @brief No copy constructor.
         *
         *  Performing a deep coppy is sort of not needed. Not to mention
         *  not wanted.
         */
        vao_array (const vao_array&) = delete;

        /*! @brief No move constructor.
         *
         *  Can't even be implemented. If this function is to be invoked,
         *  then you are something wrong.
         */
        vao_array (vao_array&&) = delete;

        /*! @brief Desctuctor.
         *
         *  Performes cleanup as promised when object goes out-of-scope.
         */
        ~vao_array ()
        {
            glDeleteVertexArrays (N, vao);
        }

        /*! @brief Generate vao id's
         *
         *  Generate vao id's. This function should only be called on the object
         *  if it has been constructed with the zeroes @sa @ref flags. It is like a
         *  defered call to the constructor. Hence the name.
         */
        void deferred_init ()
        {
            glGenVertexArrays (N, vao);
        }

        /*! @brief Access individual vao id.
         *
         *  @remark If compiled without -DNDEBUG, it will check for the validity of @param index
         */
        GLuint operator [] (unsigned index)
        {
#ifndef NDEBUG
            if (index >= N)
            {
                logWarn ("Indexing out-of-bounds vao_array (size: %d, index: %d)", N, index);
            }
#endif
            return vao[index];
        }

    private:
        GLuint vao[N];
    };
};

#endif /* _VAO_ARRAY_H */
