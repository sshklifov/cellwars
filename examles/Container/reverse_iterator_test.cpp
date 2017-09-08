#include <Container/ReverseIterator.h>
#include <logger/logger.h>

using namespace Cellwars;

void first_pass ()
{
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    ReverseRandomAccessIterator<int> first (arr + 7);
    ReverseRandomAccessIterator<int> last (arr - 1);

    int idx = 7;
    for (ReverseRandomAccessIterator<int> it = first; it != last; ++it)
    {
        logAssert (first[7 - idx] == arr[idx]);
        logAssert (*it == arr[idx]);
        --idx;
    }

    logAssert (idx == -1);
}

void second_pass ()
{
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    ReverseRandomAccessIterator<int> it (arr + 7);

    it += 4;
    logAssert (*it == arr[3]);

    it -= 3;
    logAssert (*it == arr[6]);

    --it;
    logAssert (*it == arr[7]);

    logAssert (it + 3 < it + 4);
    logAssert (it + 4 <= it + 4);
    logAssert (it + 5 > it + 2);
    logAssert (it + 5 == it + 5);

    logAssert ((it + 2) - (it + 1) == 1);
    logAssert ((it + 5) - (it + 0) == 5);
}

void print_success ()
{
    logDebug ("Pass");
}

int main ()
{
    first_pass ();
    second_pass ();

    print_success ();
    return 0;
}

