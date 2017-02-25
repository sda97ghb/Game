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

void Player::punch()
{
    if (_spriteAnimator.currentGroup() == "going_left")
        _spriteAnimator.playGroup("punching_left");
    else if (_spriteAnimator.currentGroup() == "going_right")
        _spriteAnimator.playGroup("punching_right");
    else
        ;
}

void Player::update()
{
    ;
}

Player::Player()
{
}
