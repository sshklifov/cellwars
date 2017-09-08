#ifndef APPLICATION_INCLUDED
#define APPLICATION_INCLUDED

namespace Cellwars
{
    class Application
    {
    public:
        class Singleton;
        static Singleton& GetInstance ();
    };

    class Application::Singleton
    {
    public:
        void Load ();

    private:
        void StageLogin ();
        void StageMain ();
        void ClearScreen ();
    };
};

#endif /* APPLICATION_INCLUDED */
