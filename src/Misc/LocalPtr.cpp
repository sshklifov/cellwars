#include "LocalPtr.h"
#include <stdexcept>

void Cellwars::DefaultDeleter (void*)
{
    throw std::runtime_error ("Resource leak, LocalPtr default deleter called");
}
