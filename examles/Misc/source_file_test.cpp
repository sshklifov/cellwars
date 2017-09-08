#include <Misc/SourceFile.h>
#include <iostream>

using namespace Cellwars;
using namespace std;

void first_pass ()
{
    NewPtr<char> p = SourceFile ("source_file_test.cpp");
    cout << p.GetCPtr () << endl;
}

int main ()
{
    first_pass ();
}
