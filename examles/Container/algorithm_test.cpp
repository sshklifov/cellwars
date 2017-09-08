#include <Container/Algorithm.h>
#include <Container/Iterator.h>
#include <Container/ReverseIterator.h>
#include <logger/logger.h>

using namespace Cellwars;

void first_pass ()
{
    int a = 3, b = 4;
    Swap (a, b);

    logAssert (a == 4 && b == 3);

    logAssert (Min (a, b) == b);
    logAssert (Max (a, b) == a);
}

void second_pass ()
{
    int arr[20];

    RandomAccessIterator<int> it1 (arr);
    RandomAccessIterator<int> it2 (arr + 15);

    logAssert (Distance (it1, it2) == 15);
    logAssert (Distance ((BidirectionalIterator<int>)it1, (BidirectionalIterator<int>)it2) == 15);

    ReverseRandomAccessIterator<int> rit1 (arr + 14);
    ReverseRandomAccessIterator<int> rit2 (arr - 1);

    logAssert (Distance (rit1, rit2) == 15);
    logAssert (Distance ((ReverseBidirectionalIterator<int>)rit1, (ReverseBidirectionalIterator<int>)rit2) == 15);
}

void third_pass ()
{
    int arr[20];
    Fill (RandomAccessIterator<int> (arr), 0, 20);

    for (unsigned i = 0; i < 20; ++i)
    {
        logAssert (arr[i] == 0);
    }

    int numbers[5] = {0, 1, 2, 3, 4};
    Copy (RandomAccessIterator<int> (numbers), 5, RandomAccessIterator<int> (arr));

    for (int i = 0; i < 5; ++i)
    {
        logAssert (arr[i] == i);
    }

    Fill (RandomAccessIterator<int> (arr), 0, 20);
    Copy (RandomAccessIterator<int> (numbers), RandomAccessIterator<int> (numbers + 5), RandomAccessIterator<int> (arr));

    for (int i = 0; i < 5; ++i)
    {
        logAssert (arr[i] == i);
    }
}

void forth_pass ()
{
    int arr1[4] = {0, 2, 4, 6};
    int arr2[7] = {0, 2, 4, 6, 7, 8, 9};

    RandomAccessIterator<int> first1 (arr1);
    RandomAccessIterator<int> last1 (arr1 + 4);
    RandomAccessIterator<int> first2 (arr2);
    RandomAccessIterator<int> last2 (arr2 + 7);

    logAssert (!Equal (first1, last1, first2, last2));
    logAssert (!Equal (first2, last2, first1, last1));

    last2 = RandomAccessIterator<int> (arr2 + 4);
    logAssert (Equal (first1, last1, first2, last2));
    logAssert (Equal (first2, last2, first1, last1));
}

void fifth_pass ()
{
    int arr[5] = {1, 2, 3, 4, 6};

    RandomAccessIterator<int> first (arr);
    RandomAccessIterator<int> last (arr + 5);

    RandomAccessIterator<int> it = Find (first, last, 4);
    logAssert (*it == 4);

    it = Find (first, last, 4,
            [](int range_val, int)
            {
                return range_val % 2;
            });

    logAssert (*it == 1);

    int other_arr[] = {3, 4};
    RandomAccessIterator<int> other_first (other_arr);
    RandomAccessIterator<int> other_last (other_arr + 2);
    it = FindSubset (first, last, other_first, other_last);
    logAssert (it != first && it[0] == 3 && it[1] == 4);

    int find_arr[7] = {1, 2, 2, 3, 5, 2, 1};
    it = FindN (Begin (find_arr), End (find_arr), 3, 2);
    logAssert (it[1] == 1);

    it = FindN (Begin (find_arr), End (find_arr), 5, 2);
    logAssert (it == End (find_arr));

    int one_elem_arr[1] = {1};
    it = Find (Begin (one_elem_arr), End (one_elem_arr), 2);
    logAssert (it == End (one_elem_arr));

    it = Find (Begin (one_elem_arr), End (one_elem_arr), 1);
    logAssert (it == Begin (one_elem_arr));
}

void sixth_pass ()
{
    char buf[8] = "abcdeef";
    char s1[] = "ef";

    RandomAccessIterator<const char> it = Search (CBegin (buf), CEnd (buf), CBegin (s1), CEnd (s1));
    logAssert (it[0] == 'e' && it[1] == 'e');

    /* char s2[] = "g"; */
    /* it = Search (CBegin (buf), CEnd (buf), CBegin (s2), CEnd (s2)); */
    /* logAssert (it == CEnd (buf)); */

    char s2[] = "deea";
    it = Search (CBegin (buf), CEnd (buf), CBegin (s2), CEnd (s2));
    logAssert (*it == 'a');

    char s3[] = "ca";
    it = SearchN (CBegin (buf), CEnd (buf), 2, CBegin (s3), CEnd (s3));
    logAssert (*it == 'c');
}

void seventh_pass ()
{
    int arr[] = {5, 6, 0, 4, 9, 1, 7, 2, 8, 3};
    Sort (Begin (arr), End (arr));

    for (int i = 0; i < 10; ++i)
    {
        logAssert (arr[i] == i);
    }
}

void print_success ()
{
    logDebug ("Pass");
}

int main ()
{
    first_pass ();
    second_pass ();
    third_pass ();
    forth_pass ();
    fifth_pass ();
    sixth_pass ();
    seventh_pass ();

    print_success ();
    return 0;
}
