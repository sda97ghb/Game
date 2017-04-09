#include <iostream>

#include "Arena/GlobalConstants.h"
#include "Arena/Log.h"
#include "Arena/World.h"

#include "Arena/Entity/Archer.h"

Archer::Archer() :
    _state(State::lookingAround)
{
    setEventCallback(readyToStrikeEvent, METHOD_CALLBACK(strike));
    setEventCallback(updateEvent, METHOD_CALLBACK(onUpdate));
    setEventCallback(landingEvent, METHOD_CALLBACK(onLanding));
    setEventCallback(gotSightOfPlayerEvent, METHOD_CALLBACK(onGotSightOfPlayer));
    setEventCallback(lostSightOfPlayerEvent, METHOD_CALLBACK(onLostSightOfPlayer));
    setEventCallback(wentButNotFoundEvent, METHOD_CALLBACK(onWentButNotFound));
}

void Archer::tryToJump()
{
    if (!isAlive())
        return;

    if (_state == State::jumping)
        return;

    if (!_groundContactSensor.isActive())
        return;

    float yImpulse = body()->GetMass() * ::sqrt(g * jumpHeight() * 2.0);
    body()->ApplyLinearImpulse(b2Vec2(0.0f, yImpulse),
                               body()->GetWorldCenter(),
                               true);
    _state = State::jumping;
}

void Archer::tryToMoveLeft()
{
    if (!isAlive())
        return;

    if (_leftContactSensor.isActive())
        return;

    b2Vec2 velocity = body()->GetLinearVelocity();
    velocity.x = 0;
    body()->SetLinearVelocity(velocity);

    const float xImpulse = - body()->GetMass() * movementSpeed();
    body()->ApplyLinearImpulse(b2Vec2(xImpulse, 0.0f),
                               body()->GetWorldCenter(),
                               true);

    setLookingDirection(Direction::left);
}

void Archer::tryToMoveRight()
{
    if (!isAlive())
        return;

    if (_rightContactSensor.isActive())
        return;

    b2Vec2 velocity = body()->GetLinearVelocity();
    velocity.x = 0;
    body()->SetLinearVelocity(velocity);

    const float xImpulse = body()->GetMass() * movementSpeed();
    body()->ApplyLinearImpulse(b2Vec2(xImpulse, 0.0f),
                               body()->GetWorldCenter(),
                               true);

    setLookingDirection(Direction::right);
}

void Archer::onUpdate()
{
    switch (_state)
    {
        case State::goingToLastKnownPlayerLocation :
        {
            std::cout << "going to last known location" << std::endl;

            if (_lastKnownPlayerLocation.x < body()->GetPosition().x)
                tryToMoveLeft();
            else
                tryToMoveRight();

            _abyssSensor.setDirection(lookingDirection());
            if (_abyssSensor.isActive() ||
                _leftContactSensor.isActive() ||
                _rightContactSensor.isActive())
                tryToJump();

            float dx = (_lastKnownPlayerLocation.x - body()->GetPosition().x);
            if (dx < 0.0f)
                dx *= -1.0f;
            if (dx < 0.1f)
                callEventCallback(wentButNotFoundEvent);
        } break;
    }
}

void Archer::strike()
{
    Log::instance().push("Strike!");
//    World::instance().player().makeDamage(10.0f);
    _state = State::lookingAround;
}

void Archer::onGroundHit(float speed)
{
    makeDamage(speed);
}

void Archer::onLanding()
{
    _state = State::lookingAround;
}

void Archer::onGotSightOfPlayer()
{
    std::cout << "got sight of player" << std::endl;
    prepareToStrike();
}

void Archer::onLostSightOfPlayer()
{
    std::cout << "lost sight of player" << std::endl;

    if (_state == State::preparingToStrike)
        _reloadSensor.stop();

    _lastKnownPlayerLocation = World::instance().player().body()->GetPosition();
    _state = State::goingToLastKnownPlayerLocation;
}

void Archer::prepareToStrike()
{
    _reloadSensor.start();
    _state = State::preparingToStrike;
}

void Archer::onWentButNotFound()
{
    _state = State::lookingAround;
}

float Archer::jumpHeight() const
{
    return 4.0f;
}

float Archer::movementSpeed() const
{
    return 7.0f;
}
