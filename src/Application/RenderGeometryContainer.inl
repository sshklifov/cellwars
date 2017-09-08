#include "RenderGeometry.h"
#include <stdexcept>

template <typename T>
const T* Cellwars::RenderGeometryContainer::Singleton::GetGeometry (unsigned idx) const
{
    if (!v[idx]->Identify (T::string_id))
    {
        throw std::runtime_error ("tried to cast RenderGeometry* but Identify failed");
    }

    T* res = dynamic_cast<T*> (v[idx]);
    logAssert (res != NULL);

    return res;
}

template <typename T>
T* Cellwars::RenderGeometryContainer::Singleton::GetGeometry (unsigned idx)
{
    const T* res = (const_cast<const Singleton*> (this))->GetGeometry<T> (idx);
    return const_cast<T*> (res);
}
