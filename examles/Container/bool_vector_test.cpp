#include <Container/BoolVector.h>
using namespace Cellwars;





//
#include <iostream>
using namespace std;

void first_pass ()
{
    BoolVector b;
    logAssert (b.Empty ());

    b.PushBack (1);
    logAssert (b[0] == 1);

    b = BoolVector {1, 1, 0, 0, 1};
    logAssert (*b.Data () == 25);

    b.Clear ();
    logAssert (b.Size () == 0);

    b = BoolVector (5);
    b.Resize (1020);
    logAssert (b.Size () == 1020);

    for (unsigned i = 0; i < 1020; ++i)
    {
        b[i] = i % 2;
    }
    for (unsigned i = 0; i < 1020; ++i)
    {
        bool macro_doesnt_work = i % 2;
        logAssert (b[i] == macro_doesnt_work);
    }

    b.Clear ();
    b.Resize (128);
    for (unsigned i = 0; i < 128; ++i)
    {
        b[i] = 1;
    }

    uint64_t zero = 0;
    logAssert (b.Data ()[0] == ~zero);
    logAssert (b.Data ()[1] == ~zero);
}

void second_pass ()
{
    BoolVector b;
    b.PushBack (1, 5);

    logAssert (*b.Data () == 31);

    b.ShrinkToFit ();
    logAssert (b.Capacity () == 64);

    b = BoolVector {1, 1, 0, 0};
    logAssert (b.Front () == 1);
    logAssert (b.Back () == 0);

    b.Front () = 0;
    b.Back () = 1;

    logAssert (b.Front () == 0);
    logAssert (b.Back () == 1);

    b.Resize (1020);
    for (unsigned i = 0; i < 1020; ++i)
    {
        b[i] = i % 2;
    }

    bool var = 0;
    for (BoolVector::Iterator it = b.Begin (); it != b.End (); ++it)
    {
        logAssert (*it == var);

        var ^= 1;
        *it = var;
    }

    var = 0;
    for (BoolVector::ReverseIterator it = b.RBegin (); it != b.REnd (); ++it)
    {
        logAssert (*it == var);
        
        var ^= 1;
        *it = var;
    }

    for (unsigned i = 0; i < 1020; ++i)
    {
        bool macro_doesnt_work = i % 2;
        logAssert (b[i] == macro_doesnt_work);
    }
}

void third_pass ()
{
    BoolVector b {1, 1, 0, 0};

    b.Set (0);
    logAssert (b[0] == 1);

    b.Set (1);
    logAssert (b[1] == 1);

    b.Clear (2);
    logAssert (b[2] == 0);

    b.Clear (3);
    logAssert (b[3] == 0);

    b.Flip (0);
    logAssert (b[0] == 0);

    b.Flip (1);
    logAssert (b[1] == 0);
}

void print_success ()
{
    logDebug ("Pass");
}

#include <iostream>
using namespace std;

int main ()
{
    first_pass ();
    second_pass ();
    third_pass ();

    print_success ();
    return 0;
}
