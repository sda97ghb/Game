#include <cmath>
#include <iostream>

#include "Arena/GlobalConstants.h"
#include "Arena/Log.h"
#include "Arena/World.h"

#include "Arena/Entity/Archer.h"

Archer::Archer()
{
    setEventCallback(bumpEvent, METHOD_CALLBACK(onBump));
//    setEventCallback(deathEvent,)
    setEventCallback(gotSightOfPlayerEvent, METHOD_CALLBACK(onGotSightOfPlayer));
//    setEventCallback(groundHitEvent,)
    setEventCallback(landingEvent, METHOD_CALLBACK(onLanding));
    setEventCallback(lostSightOfPlayerEvent, METHOD_CALLBACK(onLostSightOfPlayer));
    setEventCallback(readyToStrikeEvent, METHOD_CALLBACK(strike));
//    setEventCallback(spawnEvent,)
    setEventCallback(updateEvent, METHOD_CALLBACK(onUpdate));
    setEventCallback(wentButNotFoundEvent, METHOD_CALLBACK(onWentButNotFound));

    stateBuilder(chasingState)
        .setStateFunction(METHOD_FUNCTION(chasing))
        .setStateIncompatibilities(
            {
                lookingAroundState,
                preparingToStrikeState
            });

    stateBuilder(jumpingState)
        .setStateIncompatibilities(
            {
                preparingToStrikeState
            });

    stateBuilder(lookingAroundState)
        .setStateFunction(METHOD_FUNCTION(lookingAround))
        .setStateIncompatibilities(
            {
                chasingState,
                preparingToStrikeState
            });

    stateBuilder(preparingToStrikeState)
        .setStateFunction(METHOD_FUNCTION(preparingToStrike))
        .setStateIncompatibilities(
            {
                chasingState,
                jumpingState,
                lookingAroundState
            });

    activateState(lookingAroundState);
}

void Archer::tryToJump()
{
    if (!isAlive())
        return;

    if (isStateActive(jumpingState))
        return;

    if (!_groundContactSensor.isActive())
        return;

    float yImpulse = body()->GetMass() * ::sqrt(g * jumpHeight() * 2.0);
    body()->ApplyLinearImpulse(b2Vec2(0.0f, yImpulse),
                               body()->GetWorldCenter(),
                               true);

    activateState(jumpingState);
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

void Archer::onBump()
{
    if (lookingDirection() == Direction::left)
    {
        const float xImpulse = body()->GetMass() * movementSpeed();
        body()->ApplyLinearImpulse(b2Vec2(xImpulse, 0.0f),
                                   body()->GetWorldCenter(),
                                   true);
    }
    else
    {
        const float xImpulse = -body()->GetMass() * movementSpeed();
        body()->ApplyLinearImpulse(b2Vec2(xImpulse, 0.0f),
                                   body()->GetWorldCenter(),
                                   true);
    }

    tryToJump();
}

void Archer::onGroundHit(float speed)
{
    makeDamage(speed);
}

void Archer::onLanding()
{
    deactivateState(jumpingState);
}

void Archer::onGotSightOfPlayer()
{
    prepareToStrike();
}

void Archer::onLostSightOfPlayer()
{
    if (isStateActive(preparingToStrikeState))
        _reloadSensor.stop();

    _lastKnownPlayerLocation = World::instance().player().body()->GetPosition();

    activateState(chasingState);
}

void Archer::onUpdate()
{
    for (const State& state : complexState())
        std::cout << state << " ";
    std::cout << std::endl;

    callComplexStateFunctions();
}

void Archer::onWentButNotFound()
{
    activateState(lookingAroundState);
}

void Archer::prepareToStrike()
{
    _reloadSensor.start();
    activateState(preparingToStrikeState);
}

void Archer::preparingToStrike()
{
    if (World::instance().player().body()->GetPosition().x <
        body()->GetPosition().x)
        setLookingDirection(Direction::left);
    else
        setLookingDirection(Direction::right);
}

void Archer::strike()
{
    Log::instance().push("Strike!");
//    World::instance().player().makeDamage(10.0f);
    activateState(lookingAroundState);

    std::cout << "Strike!" << std::endl;
}

void Archer::chasing()
{
    if (_lastKnownPlayerLocation.x < body()->GetPosition().x)
        tryToMoveLeft();
    else
        tryToMoveRight();

    _abyssSensor.setDirection(lookingDirection());
    if (_abyssSensor.isActive())
        tryToJump();

    if (_lastKnownPlayerLocation.x < body()->GetPosition().x)
        tryToMoveLeft();
    else
        tryToMoveRight();

    float dx = ::fabsf(_lastKnownPlayerLocation.x - body()->GetPosition().x);
    if (dx < 0.1f)
        callEventCallback(wentButNotFoundEvent);
}

float Archer::jumpHeight() const
{
    return 4.0f;
}

float Archer::movementSpeed() const
{
    return 7.0f;
}

void Archer::lookingAround()
{
    static int counter = 0;
    if (counter >= 100)
    {
        if (lookingDirection() == Direction::left)
            setLookingDirection(Direction::right);
        else
            setLookingDirection(Direction::left);
        counter = 0;
    }
}
