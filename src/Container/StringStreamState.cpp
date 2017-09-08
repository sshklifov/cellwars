#include "StringStream.h"

using Cellwars::StringStreamState;

void StringStreamState::SetStates (ValueType new_states)
{
    state |= new_states;
}

void StringStreamState::ClearStates (ValueType old_states)
{
    state &= ~old_states;
}

StringStreamState::ValueType StringStreamState::GetStateBitField () const
{
    return state;
}
