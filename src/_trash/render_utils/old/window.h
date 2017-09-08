#ifndef _WINDOW_H
#define _WINDOW_H

#include <glad.h>
#include <GLFW/glfw3.h>

namespace cellwars
{
    /*! @brief Wrapper for glfw's window object
     *
     *  This class only guarantees that the window handle held will be released.
     *  It has no other purpose.
     */
    class window
    {
    public:
        /*! @brief Default constructor.
         *
         *  As a type-safe measure, the handle will be initialized to null.
         */
        window ()
        {
            w_handle = nullptr;
        }

        /*! @brief No copy constructor.
         *
         *  To implement copy ctors properly, one must introcude additional overhead (like smart pointers).
         *  Since it also includes code complexity, it is best avoided.
         */
        window (const window&) = delete;

        /*! @brief Construct an object from a window handle.
         *
         */
        explicit window (GLFWwindow* w_handle)
        {
            this->w_handle = w_handle;
        }

        /*! @brief Move ctor
         *
         *  Change ownership of the window handle.
         */
        window (window&& rhs)
        {
            w_handle = rhs.w_handle;
            rhs.w_handle = nullptr;
        }

        /*! @brief Conveniently change ownership of window handle. 
         *
         *  @remark Does not return (*this)
         */
        void operator= (window&& rhs)
        {
            this->w_handle = rhs.w_handle;
            rhs.w_handle = nullptr;
        }

        /*! @brief Conveniently set window handle.
         *
         *  @remark Does not return (*this)
         */
        void operator= (GLFWwindow* w_handle)
        {
            this->w_handle = w_handle;
        }

        /*! @brief Destructor.
         *
         *  Performes cleanup as promised when object goes out-of-scope.
         */
        ~window ()
        {
            if (w_handle != nullptr)
            {
                glfwDestroyWindow (w_handle);
            }
        }

        /*! @brief Allow casting to GLFWwindow*.
         *
         *  Handy as you'd need only pass the name of the object.
         */
        operator GLFWwindow* ()
        {
            return w_handle;
        }

    private:
        GLFWwindow* w_handle;
    };
};

#endif /* _WINDOW_H */
