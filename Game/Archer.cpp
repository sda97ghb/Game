#include <iostream>

#include "Game/Archer.h"
#include "Game/Log.h"
#include "Game/Player.h"

Archer::Archer() :
    _state(State::lookingAround)
{
}

float Archer::width() const
{
    return 0.75f;
}

float Archer::height() const
{
    return 1.75f;
}

void Archer::update()
{
    lookForPlayer();

    if (_state == State::lookingAround)
    {
        if (canSeePlayer())
        {
            _state = State::prepareToStrike;

            if (_goingDirection == GoingDirection::left)
                _spriteAnimator.playGroup("firing_left");
            else
                _spriteAnimator.playGroup("firing_right");
        }
    }
    else if (_state == State::prepareToStrike)
    {
        if (!canSeePlayer())
        {
            _state = State::goingToLastSeenPosition;
            return;
        }

        if (!isReadyForStrike())
            return;

        strike();

        if (_goingDirection == GoingDirection::left)
            _spriteAnimator.playGroup("firing_left");
        else
            _spriteAnimator.playGroup("firing_right");
    }
    else if (_state == State::goingToLastSeenPosition)
    {
        if (canSeePlayer())
        {
            _state = State::prepareToStrike;

            if (_goingDirection == GoingDirection::left)
                _spriteAnimator.playGroup("firing_left");
            else
                _spriteAnimator.playGroup("firing_right");

            return;
        }

        if (body().GetPosition() == _lastSeenPosition)
        {
            _state = State::lookingAround;
            return;
        }

        if (isAbyssAhead())
            jump();

        if (_lastSeenPosition.x < body().GetPosition().x)
            stepLeft();
        else
            stepRight();
    }
}

void Archer::lookForPlayer()
{
    if (canSeePlayer())
    {
        _lastSeenPosition = Player::instance().body().GetPosition();
        if (isPlayerToLeft())
            _goingDirection = GoingDirection::left;
        else
            _goingDirection = GoingDirection::right;
    }
}

bool Archer::isReadyForStrike()
{
    return _spriteAnimator.currentGroup() != "firing_left" &&
            _spriteAnimator.currentGroup() != "firing_right";
}

void Archer::strike()
{
    Log::instance().push("Strike!");
    Player::instance().makeDamage(5.0f);
}
