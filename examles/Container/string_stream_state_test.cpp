#include <Container/StringStream.h>
#include <logger/logger.h>
using namespace Cellwars;

void first_pass ()
{
    StringStreamState st;
    logAssert (st.GetStateBitField () == StringStreamState::GOOD);

    st.SetStates (StringStreamState::PARTIAL_WR | StringStreamState::ENCODING_ERR);
    logAssert (st.GetStateBitField () & StringStreamState::PARTIAL_WR);
    logAssert (st.GetStateBitField () & StringStreamState::ENCODING_ERR);

    st.ClearStates (StringStreamState::PARTIAL_WR);
    logAssert ((st.GetStateBitField () & StringStreamState::PARTIAL_WR) == 0);
    st.ClearStates (StringStreamState::PARTIAL_WR);
    logAssert ((st.GetStateBitField () & StringStreamState::PARTIAL_WR) == 0);

    st.ClearStates (StringStreamState::ENCODING_ERR);
    logAssert (st.GetStateBitField () == StringStreamState::GOOD);
}

void print_success ()
{
    logDebug ("Pass");
}

int main ()
{
    first_pass ();

    print_success ();
    return 0;
}
