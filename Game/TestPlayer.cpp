#include "TestPlayer.h"

TestPlayer& TestPlayer::instance()
{
    static TestPlayer instance;
    return instance;
}

float TestPlayer::width() const
{
    return 0.75f;
}

float TestPlayer::height() const
{
    return 1.75f;
}

TestPlayer::TestPlayer()
{
}
