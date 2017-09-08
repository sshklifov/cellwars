#include "SourceFile.h"
#include <Misc/LocalPtr.h>
#include <Container/StringStream.h>
#include <logger/logger.h>

#include <fstream>

using Cellwars::NewPtr;
using Cellwars::OutputStringStream;

static std::streampos TellFileSizeAndRewind (std::ifstream& file)
{
    file.seekg (0, std::ios_base::end);
    if (!file)
    {
        throw std::runtime_error ("Failed to seek to end of file");
    }

    std::streampos pos = file.tellg ();
    if (pos == -1)
    {
        throw std::runtime_error ("Failed to tell stream position of file");
    }

    file.seekg (0, std::ios_base::beg);
    if (!file)
    {
        throw std::runtime_error ("Failed to seek to start of file");
    }

    return pos;
}

static NewPtr<char> StoreFileContentsInMemory(std::ifstream& file, std::streampos bytes)
{
    NewPtr<char> res = new char[(unsigned)bytes + 1];
    file.read (res.GetPtr (), bytes);

    if (!file.good ())
    {
        OutputStringStream ss;
        ss << "Reading " << bytes << " bytes from file"
        << " resulted in a failure";

        throw std::runtime_error (ss.CStr ());
    }

    logAssert(file.peek() == EOF);
    res[bytes] = '\0';

    return res;
}

NewPtr<char> Cellwars::SourceFile (const char* path)
{
    std::ifstream file (path, std::ios_base::binary);
    if (!file)
    {
        OutputStringStream ss;
        ss << "Cannot open file for reading " << path;

        throw std::runtime_error (ss.CStr ());
    }

    std::streampos pos = TellFileSizeAndRewind(file);
    NewPtr<char> res = StoreFileContentsInMemory(file, pos);
    return res;
}
