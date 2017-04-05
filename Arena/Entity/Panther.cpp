#include "Box2D/Common/b2Math.h"

#include "Arena/Entity/Fireball.h"
#include "Arena/Entity/Panther.h"
#include "Arena/Entity/Player.h"
#include "Arena/Log.h"

Panther::Panther() :
    _state(State::lookingAround)
{
}

float Panther::width() const
{
    return 14.0f / 5.0f; //0.75f;
}

float Panther::height() const
{
    return 6.0f / 5.0f; //1.75f;
}

void Panther::update()
{
    Log::instance().push(_playerSensor.canSee() ? "I see you" : "I can't see you");
    Log::instance().push(_playerSensor.isNearby() ? "You are near to me." : "Where are you going?");

    if (_playerSensor.isActive())
    {
        _lastSeenPosition = Player::instance().body().GetPosition();
        if (isPlayerToLeft())
            _goingDirection = GoingDirection::left;
        else
            _goingDirection = GoingDirection::right;
    }

    if (_state == State::lookingAround)
    {
        if (_playerSensor.isActive())
        {
            _state = State::prepareToStrike;

            if (_goingDirection == GoingDirection::left)
                _spriteAnimator.playGroup("punching_left");
            else
                _spriteAnimator.playGroup("punching_right");
        }
    }
    else if (_state == State::prepareToStrike)
    {
        static int r = 0;
        r += 3;
        _spriteAnimator.sprite().setColor(sf::Color(r % 256, (r + 80) % 256, (r + 160) % 256));

        if (!_playerSensor.isActive())
        {
            _state = State::goingToLastSeenPosition;
            return;
        }

        if (!isReadyForStrike())
            return;

        strike();

        if (_goingDirection == GoingDirection::left)
            _spriteAnimator.playGroup("punching_left");
        else
            _spriteAnimator.playGroup("punching_right");
    }
    else if (_state == State::goingToLastSeenPosition)
    {
        if (_playerSensor.isActive())
        {
            _state = State::prepareToStrike;

            if (_goingDirection == GoingDirection::left)
                _spriteAnimator.playGroup("punching_left");
            else
                _spriteAnimator.playGroup("punching_right");

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

void Panther::constructSensors()
{
    _playerSensor.hangOnBody(&body());
}

bool Panther::isReadyForStrike()
{
    return _spriteAnimator.currentGroup() != "punching_left" &&
           _spriteAnimator.currentGroup() != "punching_right";
}

void Panther::strike()
{
    Fireball::spawn(body().GetPosition().x, body().GetPosition().y);
//    body().ApplyLinearImpulse(b2Vec2(0.0f, body().GetMass() * 3.0f), body().GetWorldCenter(), true);
//    if (_groundSensor.isActive())
        body().ApplyLinearImpulse(b2Vec2(0.0f, body().GetMass() * 5.0f), body().GetWorldCenter(), true);
//    jump();
//    Log::instance().push("Strike!"a);
//    Player::instance().makeDamage(5.0f);
}

//#include <iostream>

//#include "Arena/Panther.h"
//#include "Arena/Log.h"
//#include "Arena/Player.h"

//Panther::Panther() :
//    _state(State::lookingAround)
//{
//}

//float Panther::width() const
//{
//    return 0.75f;
//}

//float Panther::height() const
//{
//    return 1.75f;
//}

//void Panther::update()
//{
//    lookForPlayer();

//    if (_state == State::lookingAround)
//    {
//        if (canSeePlayer())
//        {
//            _state = State::prepareToStrike;

//            if (_goingDirection == GoingDirection::left)
//                _spriteAnimator.playGroup("punching_left");
//            else
//                _spriteAnimator.playGroup("punching_right");
//        }
//    }
//    else if (_state == State::prepareToStrike)
//    {
//        if (!canSeePlayer())
//        {
//            _state = State::goingToLastSeenPosition;
//            return;
//        }

//        if (!isReadyForStrike())
//            return;

//        strike();

//        if (_goingDirection == GoingDirection::left)
//            _spriteAnimator.playGroup("punching_left");
//        else
//            _spriteAnimator.playGroup("punching_right");
//    }
//    else if (_state == State::goingToLastSeenPosition)
//    {
//        if (canSeePlayer())
//        {
//            _state = State::prepareToStrike;

//            if (_goingDirection == GoingDirection::left)
//                _spriteAnimator.playGroup("punching_left");
//            else
//                _spriteAnimator.playGroup("punching_right");

//            return;
//        }

//        if (body().GetPosition() == _lastSeenPosition)
//        {
//            _state = State::lookingAround;
//            return;
//        }

//        if (isAbyssAhead())
//            jump();

//        if (_lastSeenPosition.x < body().GetPosition().x)
//            stepLeft();
//        else
//            stepRight();
//    }
//}

//bool Panther::isReadyForStrike()
//{
//    return _spriteAnimator.currentGroup() != "punching_left" &&
//           _spriteAnimator.currentGroup() != "punching_right";
//}

//void Panther::strike()
//{
//    Log::instance().push("Strike!");
//    Player::instance().makeDamage(5.0f);
//}
