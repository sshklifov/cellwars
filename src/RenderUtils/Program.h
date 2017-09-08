#ifndef PROGRAM_INCLUDED
#define PROGRAM_INCLUDED

#include <glad/glad.h>

namespace Cellwars
{
    /*! @brief Represents OpenGL programmes.
     *
     *  This class will be responsible for loading GLSL programmes and
     *  automatically cleaning up.
     */
    class Program
    {
    public:
        /*! @brief Default ctor.
         *
         *  As a type-safe measure, the programme id will be initialized to 0.
         */
        Program ();

        /*! @brief Construct on object from an existing programme id.
         *
         *  @param id OpenGL generated id.
         */
        explicit Program (GLuint id);

        /*! @brief Load programme from disk
         *
         *  It exists to avoid code suck as Program().Load(). However, if we create a program
         *  through the constructor, then we will ignore the state value returned by @ref Load.
         *  This is not a problem as @ref IsLoaded can make this check independently.
         *
         *  @param name Path to shaders without their extensions
         *  @param shaders String of shaders to load.
         *  @return True iff called succeeded.
         *
         *  @sa @ref Load
         */
        Program (const char* name, const char* shaders);

        /*! @brief No copy ctor
         *
         *  To implement copy ctors properly, one must introcude additional overhead (smart pointers).
         *  Since it also includes code complexity, it is best avoided.
         */
        Program (const Program&) = delete;

        /*! @brief Move ctor
         *
         *  Change ownership of the programme id.
         *
         *  @param rhs Program class type which is being moved.
         */
        Program (Program&& rhs);

        /*! @brief Destructor.
         *
         *  Performes cleanup (glDelete*) when object goes out-of-scope.
         */
        ~Program ();

        /*! @brief No lvalue assignment operator
         *
         *  Since we do not allow copy ctor, it would make sense to not allow assignment operator as well
         *  (for the very same reason).
         */
        void operator= (const Program& rhs) = delete;

        /*! @brief Rvalue assignment operator.
         *  
         *  Conveniently set programme id.
         *  
         *  @param rhs Right hand side of assignment.
         *  @return A reference to the left hand side.
         */
        Program& operator= (Program&& rhs);

        /*! @brief Load programme from disk.
         *
         *  Attempts to load in binary form a programme. There is a standard method to search for shaders.
         *  First, @param name specifies the name of the shader group that forms a logical unit (programme).
         *  @param shaders specifies which shader types to search for. Available values are:
         *  -'v' for '*.vert'
         *  -'e' for '*.tese'
         *  -'c' for '*.tesc'
         *  -'g' for '*.geom'
         *  -'f' for '*.frag'
         *  -'c' for '*.comp'
         *
         *  @param name Path to shaders without their extensions
         *  @param shaders String of shaders to load.
         *  @return True iff called succeeded.
         *
         *  @remark Tesselation in OpenGL 3.3 is not supported. So passing any of the tesselation flags will
         *  result in an error.
         */
        void Load (const char* name, const char* shaders);

        /*! @brief Check if loading the programme succeeded.
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
        void Load_Impl (const char* name, const char* shaders);

    private:
        GLuint id;
    };
};

#endif /* PROGRAM_INCLUDED */
