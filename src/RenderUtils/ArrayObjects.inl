#include "ArrayObjects.h"
#include <Container/Algorithm.h>

template <unsigned N>
Cellwars::BufferObject<N>::BufferObject () : objs {0}
{
}

template <unsigned N>
Cellwars::BufferObject<N>::BufferObject (BufferObject<N>&& rhs)
{
    Copy (CBegin (rhs.objs), CEnd (rhs.objs), Begin (objs));
    Fill (CBegin (rhs.objs), 0, N);
}

template <unsigned N>
Cellwars::BufferObject<N>::~BufferObject ()
{
}

template <unsigned N>
Cellwars::BufferObject<N>& Cellwars::BufferObject<N>::operator= (BufferObject<N>&& rhs)
{
    Clear ();
    Copy (CBegin (rhs.objs), CEnd (rhs.objs), Begin (objs));
    Fill (Begin (rhs.objs), 0, N);

    return (*this);
}

template <unsigned N>
Cellwars::VboArray<N>::VboArray () : BufferObject<N> ()
{
}

template <unsigned N>
Cellwars::VboArray<N>::~VboArray()
{
    Clear ();
}

template <unsigned N>
void Cellwars::VboArray<N>::Load ()
{
    logAssert (!IsLoaded ());
    glGenBuffers (N, this->objs);
}

template <unsigned N>
bool Cellwars::VboArray<N>::IsLoaded () const
{
    return *(this->objs) != 0;
}

template <unsigned N>
void Cellwars::VboArray<N>::Clear ()
{
    glDeleteBuffers (N, this->objs);
    Fill (Begin (this->objs), N, 0);
}
template <unsigned N>
GLuint Cellwars::VboArray<N>::operator[] (unsigned index) const
{
    logAssert (index < N);
    return this->objs[index];
}

template <unsigned N>
Cellwars::VaoArray<N>::VaoArray () : BufferObject<N> ()
{
}

template <unsigned N>
Cellwars::VaoArray<N>::~VaoArray()
{
    Clear ();
}

template <unsigned N>
void Cellwars::VaoArray<N>::Load ()
{
    logAssert (!IsLoaded ());
    glGenVertexArrays (N, this->objs);
}

template <unsigned N>
bool Cellwars::VaoArray<N>::IsLoaded () const
{
    return *(this->objs) != 0;
}

template <unsigned N>
void Cellwars::VaoArray<N>::Clear ()
{
    glDeleteVertexArrays (N, this->objs);
    Fill (Begin (this->objs), N, 0);
}

template <unsigned N>
GLuint Cellwars::VaoArray<N>::operator[] (unsigned index) const
{
    logAssert (index < N);
    return this->objs[index];
}

template <unsigned N>
Cellwars::TexArray<N>::TexArray () : BufferObject<N> ()
{
}

template <unsigned N>
Cellwars::TexArray<N>::~TexArray()
{
    Clear ();
}

template <unsigned N>
void Cellwars::TexArray<N>::Load ()
{
    logAssert (!IsLoaded ());
    glGenTextures (N, this->objs);
}

template <unsigned N>
bool Cellwars::TexArray<N>::IsLoaded () const
{
    return *(this->objs) != 0;
}

template <unsigned N>
void Cellwars::TexArray<N>::Clear ()
{
    glDeleteTextures (N, this->objs);
    Fill (Begin (this->objs), N, 0);
}

template <unsigned N>
GLuint Cellwars::TexArray<N>::operator[] (unsigned index) const
{
    logAssert (index < N);
    return this->objs[index];
}
