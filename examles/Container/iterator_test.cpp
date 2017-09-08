#include <Container/Iterator.h>
#include <logger/logger.h>

using namespace Cellwars;

void first_pass ()
{
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    RandomAccessIterator<int> first (arr);
    RandomAccessIterator<int> last (arr + 8);

    int idx = 0;
    for (RandomAccessIterator<int> it = first; it != last; ++it)
    {
        logAssert (first[idx] == arr[idx]);
        logAssert (*it == arr[idx]);
        ++idx;
    }

    logAssert (idx == 8);
}

void second_pass ()
{
    int arr[8] = {1, 2, 3, 4, 5, 6, 7, 8};

    RandomAccessIterator<int> it (arr);

    it += 4;
    logAssert (*it == arr[4]);

    it -= 3;
    logAssert (*it == arr[1]);

    --it;
    logAssert (*it == arr[0]);

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
