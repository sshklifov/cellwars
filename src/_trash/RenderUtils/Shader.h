#ifndef _SHADER_H
#define _SHADER_H

#include <glad/glad.h>

namespace Cellwars
{
    /*! @brief Represents OpenGL shaders.
     *
     *  Should not be used in most of the times. It's purpose is to
     *  lay the ground for the Program class.
     */
    class Shader
    {
    public:
        /*! @brief Default ctor.
         *
         *  As a type-safe measure, the shader id will be initialized to 0.
         */
        Shader ();

        /*! @brief Construct an object from an existing shader id.
         *
         *  @param id OpenGL generated id.
         */
        explicit Shader (GLuint id);

        /*! @brief Load shader from disk
         *
         *  It exists to avoid code suck as Shader().Load(). However, if we create a shader
         *  through the constructor, then we will ignore the state value returned by @ref Load.
         *  This is not a problem as @ref IsLoaded can make this check independently.
         *
         *  @param file Path to file on file system.
         *  @param type OpenGL constant that determines shader type.
         *  @return True iff call succeeded.
         */
        Shader (const char* file, GLenum type);

        /*! @brief No copy ctor.
         *
         *  To implement copy ctors properly, one must introduce additional overhead (smart pointers).
         *  Since it also includes code complexity, it is best avoided.
         */
        Shader (const Shader&) = delete;

        /*! @brief Move ctor
         *
         *  Change ownership of shader id.
         *
         *  @param rhs Shader class type which is being moved.
         */
        Shader (Shader&& rhs);

        /*! @brief Destructor.
         *
         *  Performes cleanup (glDelete*) when object goes out-of-scope.
         */
        ~Shader ();

        /*! @brief No lvalue assignment operator
         *
         *  Since we do not allow copy ctor, it would make sense to not allow assignment operator as well
         *  (for the very same reason).
         */
        void operator= (const Shader& rhs) = delete;

        /*! @brief Rvalue assignment operator.
         *  
         *  Conveniently set shader id.
         *  
         *  @param rhs Right hand side of assignment.
         *  @return A reference to the left hand side.
         */
        Shader& operator= (Shader&& rhs);

        /*! @brief Load shader from disk.
         *
         *  Attempts to load in binary form a shader from disk (in text form).
         *
         *  @param file Path to file on file system.
         *  @param type OpenGL constant that determines shader type.
         *  @return True iff call succeeded.
         */
        bool Load (const char* file, GLenum type);

        /*! @brief Check if loading the shader succeeded.
         *
         *  @remark If @ref Load has not been called, then this function will return false.
         */
        bool IsLoaded () const;

        /*! @brief Release resources early (before going out-of-scope)
         */
        void Clear ();

        /*! @brief Allow casting to GLuint
         *
         *  Handy as you'd need only pass the class instance to a gl* call.
         */
        operator GLuint () const;

    private:
        bool _Impl_Load (const char* file, GLenum type);

    private:
        GLuint id;
    };
};

#endif /* _SHADER_H */

