#include "Game/Player.h"

Player& Player::instance()
{
    static Player instance;
    return instance;
}

float Player::width() const
{
    return 0.75f;
}

float Player::height() const
{
    return 1.75f;
}

void Player::update()
{
    ;
}

Player::Player()
{
}
