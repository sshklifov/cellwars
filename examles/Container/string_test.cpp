#include <Container/String.h>
#include <iostream>

using namespace Cellwars;
using namespace std;

void first_pass ()
{
    String s ("123");
    logAssert (s.Size () == 3);
    logAssert (s[0] == '1' && s[1] == '2' && s[2] == '3');

    s.Resize (5);
    logAssert (s.Size () == 5);

    s[3] = 3;
    s[4] = 4;

    s.ShrinkToFit ();
    logAssert (s.Capacity () == s.Size ());
}

void second_pass ()
{
    const char* s = "12345678";
    String str (s, 5);

    logAssert (str.Front () == '5' && str.Back () == '1');

    str.Back () = '3';
    logAssert (str[0] == '3');

    String str2 = str.Substr (3);
    logAssert (str2.Size () == 2);
    logAssert (str2[0] == '4' && str2[1] == '5');

    str2.Append ('8', 5);
    logAssert (str2.Size () == 7);
    logAssert (str2[6] == '8');
}

void third_pass ()
{
    cout << "Trying Getline on string... Enter a line: ";
    String str;
    Getline (cin, str);

    str.NullTerminate ();
    cout << "You enterned : " << str.CStr () << endl;
    cout << "Size: " << str.Size ();
}

void forth_pass ()
{
    char buf[] = "abcdefabcedfaaaabc";
    String str (buf);

    logAssert (str[0] == 'a' && str[2] == 'c');
    logAssert (str.Find ("def") == 3);
    logAssert (str.Find ("abc", 3) == 6);
    logAssert (str.Find ("5") == String::Npos);
    logAssert (str.Find ("defa", 3) == 3);
    /* logAssert (str.Find ("a", 101) == StringSegment::Npos); */

    logAssert (str[0] == 'a' && str[2] == 'c');
    logAssert (str.RFind ("a") == 15);

    logAssert (str.RFind ("dfa") == 10);
    logAssert (str.RFind ("cdefab") == 2);
    logAssert (str.RFind ("5") == String::Npos);
    logAssert (str.RFind ("abcd", 4) == 0);
}

void fifth_pass ()
{
    char buf[] = "abcdefabcedfaaaabc";
    String str (buf);

    logAssert (str.FindFirstOf ("b") == 1);
    logAssert (str.FindFirstOf ("gef", 0, 3) == 9);
    logAssert (str.FindFirstOf ("gsedag", 0, 5) == 9);
    logAssert (str.FindFirstOf ("513") == String::Npos);
    logAssert (str.FindFirstOf ("a", 0, 100) == String::Npos);

    logAssert (str.FindFirstNotOf ("gef", 0, 3) == 2);
    logAssert (str.FindFirstNotOf ("abcf", 0, 3) == 9);
    logAssert (str.FindFirstNotOf ("fab", 11, 1) == 17);
    logAssert (str.FindFirstNotOf ("a", 100) == String::Npos);
    logAssert (str.FindFirstNotOf ("abcdef") == String::Npos);
}

void sixth_pass ()
{
    char buf[] = "abcdefabcedfaaaabc";
    String str (buf);

    logAssert (str.FindLastOf ("f") == 11);
    logAssert (str.FindLastOf ("a", 6) == 6);
    logAssert (str.FindLastOf ("abc", 5, 3) == 7);
    logAssert (str.FindLastOf ("5") == String::Npos);

    logAssert (str.FindLastNotOf ("gef", 0, 3) == 15);
    logAssert (str.FindLastNotOf ("abcf", 0, 3) == 4);
    logAssert (str.FindLastNotOf ("fab", 11, 1) == 4);
    logAssert (str.FindLastNotOf ("a", 100) == String::Npos);
    logAssert (str.FindLastNotOf ("abcdef") == String::Npos);
}

void seventh_pass ()
{
    logAssert (String("abc") < String("abcd"));
    logAssert (String("dabc") < String("gggg"));
    logAssert (String("adda") == String("adda"));
    logAssert (String("adda") <= String("adda"));
    logAssert (String("dada") > String("dad"));
    logAssert (String("abbkba") > String("abbaba"));
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
