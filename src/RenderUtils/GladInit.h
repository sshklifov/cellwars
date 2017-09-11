#ifndef GLAD_INIT_INCLUDED
#define GLAD_INIT_INCLUDED

namespace Cellwars
{
    class GladInit
    {
    public:
        class Singleton;

    public:
        static Singleton& GetInstance ();
    };

    class GladInit::Singleton
    {
    public:
        Singleton ();
        ~Singleton ();

        Singleton (const Singleton&) = delete;
        Singleton (Singleton&&) = delete;
        void operator= (const Singleton&) = delete;
        void operator= (Singleton&&) = delete;

        bool IsLoaded () const;
    };
};

#endif /* GLAD_INIT_INCLUDED */