#ifndef GLFW_INIT_INCLUDED
#define GLFW_INIT_INCLUDED

#include <GLFW/glfw3.h>

namespace Cellwars
{
    class GlfwInit
    {
    public:
        class Singleton;

    public:
        static Singleton& GetInstance ();
    };

    class GlfwInit::Singleton
    {
    public:
        Singleton ();
        ~Singleton ();

        Singleton (const Singleton&) = delete;
        Singleton (Singleton&&) = delete;
        void operator= (const Singleton&) = delete;
        void operator= (Singleton&&) = delete;

        bool IsLoaded () const;
        void Clear ();

        GLFWwindow* GetWindow ();
        unsigned GetWidth ();
        unsigned GetHeight ();

    private:
        GLFWwindow* window;
        unsigned width;
        unsigned height;

        bool status;
    };
};

#endif /* GLFW_INIT_INCLUDED */
