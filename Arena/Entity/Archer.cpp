#include <iostream>

#include "Arena/Entity/Archer.h"
#include "Arena/Log.h"
#include "Arena/Entity/Player.h"

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

            if (_goingDirection == Direction::left)
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

        if (_goingDirection == Direction::left)
            _spriteAnimator.playGroup("firing_left");
        else
            _spriteAnimator.playGroup("firing_right");
    }
    else if (_state == State::goingToLastSeenPosition)
    {
        if (canSeePlayer())
        {
            _state = State::prepareToStrike;

            if (_goingDirection == Direction::left)
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

        _abyssSensor.setDirection(_goingDirection);
        if (_abyssSensor.isActive())
            jump();

        if (_lastSeenPosition.x < body().GetPosition().x)
            stepLeft();
        else
            stepRight();
    }
}

void Archer::constructSensors()
{
    _abyssSensor.setDx(1.2f);
    _abyssSensor.setDy(-height() / 2.0f - 0.2f);
    _abyssSensor.hangOnBody(&body());
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
