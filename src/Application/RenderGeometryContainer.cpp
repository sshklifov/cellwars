#include "RenderGeometry.h"

using Cellwars::RenderGeometry;
using Cellwars::RenderGeometryContainer;
using Singleton = RenderGeometryContainer::Singleton;

Cellwars::RenderCircle* RenderGeometryContainer::p_player = NULL;

Cellwars::RenderCircle* RenderGeometryContainer::GetPlayer ()
{
    if (p_player == NULL)
    {
        RenderCircle* circle = new RenderCircle (FCircle (0.f, 0.f, 0.f), FVec3 (0.f, 0.f, 0.f), "");
        GetInstance().PushBack (circle);
        p_player = circle;
    }

    return p_player;
}

Singleton& RenderGeometryContainer::GetInstance ()
{
    static Singleton instance;
    return instance;
}

Singleton::~Singleton ()
{
    for (unsigned i = 0; i < v.Size (); ++i)
    {
        delete v[i];
    }
}

void Singleton::PushBack (NewPtr<RenderGeometry> p)
{
    v.PushBack (p.Release ());
}

unsigned Singleton::Size () const
{
    return v.Size ();
}

void Singleton::Render ()
{
    for (unsigned i = 0; i < v.Size (); ++i)
    {
        v[i]->Render ();
    }
}

RenderGeometry* Singleton::operator[] (unsigned idx)
{
    return v[idx];
}

void Singleton::Sort ()
{
    Cellwars::Sort (v.Begin (), v.End (),
            [](RenderGeometry* lhs, RenderGeometry* rhs)
            {
                return lhs->Priority () < rhs->Priority ();
            });
}

void Singleton::Remove (unsigned idx)
{
    // NOTE: Vector does not include any remove functionality. Why? Because forcing this
    // implementation here on Vector will not be optimal. The number or reallocations can
    // be reduced. But the algorithm is not ready yet.

    logAssert (idx < Size ());

    delete v[idx];
    unsigned size = v.Size () - 1;

    for (unsigned i = idx; i < size; ++i)
    {
        v[i] = v[i + 1];
    }

    v.Resize (size);
}

void Singleton::Remove (RenderGeometry* ptr)
{
    for (unsigned i = 0; i < v.Size (); ++i)
    {
        if (v[i] == ptr)
        {
            Remove (i);
            return;
        }
    }

    throw std::runtime_error ("requested to remove RenderGeometry which was nowhere to be found");
}
