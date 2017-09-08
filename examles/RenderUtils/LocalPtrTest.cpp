#include <RenderUtils/LocalPtr.h>

#include <cstdlib>
#include <cstdio>

#include <utility>

using namespace Cellwars;

struct DeleterType
{
    void operator() (void* ptr)
    {
        printf ("freeing %p\n", ptr);
        free (ptr);
    }
} Deleter;

using TestPtr = LocalPtr<int, DeleterType>;

void first_pass ()
{
    TestPtr p ((int*)malloc (500), Deleter);
    printf ("allocating 500 bytes\n");
    printf ("pointer is: %p\n", p.GetCPtr ());
}

void second_pass ()
{
    TestPtr p1 ((int*)malloc (500), Deleter);
    printf ("allocating 500 bytes\n");
    printf ("pointer is: %p\n", p1.GetCPtr ());

    TestPtr p2;
    printf ("creating empty pointer; moving first pointer to the new one\n");
    p2 = std::move (p1);
}

void third_pass ()
{
    TestPtr p ((int*)malloc (4), Deleter);

    printf ("allocating 4 bytes\n");
    printf ("pointer is: %p\n", p.GetCPtr ());

    printf ("pointer bool operator: %d\n", (bool)p);
    printf ("pointer operator!: %d\n", !p);

    printf ("releasing contents of ptr\n");
    free (p.Release ());
    printf ("ptr now points to: %p\n", p.GetCPtr ());

    printf ("pointer bool operator: %d\n", (bool)p);
    printf ("pointer operator!: %d\n", !p);
}

void fourth_pass ()
{
    int* raw_ptr = (int*)malloc (sizeof (int));
    *raw_ptr = 4;

    const TestPtr p (raw_ptr, Deleter);
    printf ("creating pointer to four with adress: %p\n", p.GetCPtr ());
    printf ("operator* yields: %d\n", *p);
}

void fifth_pass ()
{
    struct Compound
    {
        int i;
        float f;
        char c;
    };

    Compound* raw_ptr = (Compound*)malloc (sizeof (Compound));
    raw_ptr->i = 13;
    raw_ptr->f = 0.3f;
    raw_ptr->c = 'a';

    LocalPtr<Compound, void(*)(void*)> p (raw_ptr, free);
    printf ("creating point to compound type {13, 0.3f, \'a\'} with address: %p\n", p.GetPtr ());

    printf ("accessing integer: %d\n", p->i);
    printf ("accessing float: %f\n", p->f);
    printf ("accessing char: %c\n", p->c);

    printf ("releasing pointer: %p\n", p.Release ());
    printf ("deleting initialization (should be same): %p\n", raw_ptr);

    free (raw_ptr);
}

void print_delim ()
{
    printf ("--------------------------------------------------\n");
}

int main ()
{
    first_pass ();
    print_delim ();

    second_pass ();
    print_delim ();

    third_pass ();
    print_delim ();

    fourth_pass ();
    print_delim ();

    fifth_pass ();
    print_delim ();

    return 0;
}
