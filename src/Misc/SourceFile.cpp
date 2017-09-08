#include "SourceFile.h"
#include <Container/StringStream.h>

#include <fstream>

using Cellwars::NewPtr;
using Cellwars::OutputStringStream;

NewPtr<char> Cellwars::SourceFile (const char* path)
{
    std::ifstream file (path, std::ios_base::binary);
    if (!file)
    {
        OutputStringStream ss;
        ss << "Cannot open file for reading " << path;

        throw std::runtime_error (ss.CStr ());
    }

    file.seekg (0, std::ios_base::end);
    if (!file)
    {
        OutputStringStream ss;
        ss << "Failed to seek to end for file " << path;

        throw std::runtime_error (ss.CStr ());
    }

    std::streampos pos = file.tellg ();
    if (pos == -1)
    {
        OutputStringStream ss;
        ss << "Failed to tell stream position for file " << path;

        throw std::runtime_error (ss.CStr ());
    }

    file.seekg (0, std::ios_base::beg);
    if (!file)
    {
        OutputStringStream ss;
        ss << "Failed to seek to start for file " << path;

        throw std::runtime_error (ss.CStr ());
    }

    NewPtr<char> res = new char[(unsigned)pos + 1];
    file.read (res.GetPtr (), pos);

    if (!file.good ())
    {
        OutputStringStream ss;
        ss << "Reading " << pos << " bytes from file " << path;
        ss << " resulted in a failure.";

        throw std::runtime_error (ss.CStr ());
    }

    logAssert (file.peek () == EOF);

    res[pos] = '\0';
    return res;
}
