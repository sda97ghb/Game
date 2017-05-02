#include <cmath>
#include <iostream>

#include "Arena/GlobalConstants.h"
#include "Arena/Log.h"
#include "Arena/ObjectCounter.h"
#include "Arena/World.h"

#include "Arena/Entity/Archer.h"
#include "Arena/Entity/ArrowBuilderSpawner.h"
#include "Arena/Entity/EntityDestroyer.h"
#include "Arena/Entity/Player.h"

Archer::Archer()
{
    ObjectCounter<Archer>::addObject(this);

    addEventCallback(bumpEvent, METHOD_CALLBACK(onBump));
    addEventCallback(deathEvent, METHOD_CALLBACK(onDeath));
    addEventCallback(gotSightOfPlayerEvent, METHOD_CALLBACK(onGotSightOfPlayer));
//    setEventCallback(groundHitEvent,)
    addEventCallback(landingEvent, METHOD_CALLBACK(onLanding));
    addEventCallback(lostSightOfPlayerEvent, METHOD_CALLBACK(onLostSightOfPlayer));
    addEventCallback(readyToStrikeEvent, METHOD_CALLBACK(strike));
//    setEventCallback(spawnEvent,)
    addEventCallback(updateEvent, METHOD_CALLBACK(onUpdate));
    addEventCallback(wentButNotFoundEvent, METHOD_CALLBACK(onWentButNotFound));

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

Archer::~Archer()
{
    delete _abyssSensor;
    delete _leftContactSensor;
    delete _rightContactSensor;
    delete _groundContactSensor;
    delete _groundHitSensor;
    delete _landingSensor;
    delete _leftBumpSensor;
    delete _rightBumpSensor;
    delete _playerSensor;
    delete _reloadSensor;

    ObjectCounter<Archer>::removeObject(this);
}

void Archer::tryToJump()
{
//    return_if_deleted

    if (!isAlive())
        return;

    if (isStateActive(jumpingState))
        return;

    if (!_groundContactSensor->isActive())
        return;

    float yImpulse = body()->GetMass() * ::sqrt(g * jumpHeight() * 2.0);
    body()->ApplyLinearImpulse(b2Vec2(0.0f, yImpulse),
                               body()->GetWorldCenter(),
                               true);

    activateState(jumpingState);
}

void Archer::tryToMoveLeft()
{
//    return_if_deleted

    if (!isAlive())
        return;

    if (_leftContactSensor->isActive())
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
//    return_if_deleted

    if (!isAlive())
        return;

    if (_rightContactSensor->isActive())
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
//    return_if_deleted

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
//    return_if_deleted

    makeDamage(speed);
}

void Archer::onLanding()
{
//    return_if_deleted

    deactivateState(jumpingState);
}

void Archer::onGotSightOfPlayer()
{
//    return_if_deleted

    prepareToStrike();
}

void Archer::onLostSightOfPlayer()
{
//    return_if_deleted

    if (isStateActive(preparingToStrikeState))
        _reloadSensor->stop();

    _lastKnownPlayerLocation = World::instance().player()->body()->GetPosition();

    activateState(chasingState);
}

void Archer::onUpdate()
{
//    return_if_deleted

//    for (const State& state : complexState())
//        std::cout << state << " ";
//    std::cout << std::endl;

    callComplexStateFunctions();
}

void Archer::onWentButNotFound()
{
//    return_if_deleted

    activateState(lookingAroundState);
}

void Archer::prepareToStrike()
{
//    return_if_deleted

    _reloadSensor->start();
    activateState(preparingToStrikeState);
}

void Archer::preparingToStrike()
{
//    return_if_deleted

    if (World::instance().player()->body()->GetPosition().x <
        body()->GetPosition().x)
        setLookingDirection(Direction::left);
    else
        setLookingDirection(Direction::right);
}

void Archer::strike()
{
//    return_if_deleted

    Log::instance().addMessage("Strike!");

    b2Vec2 myPos = body()->GetPosition();

    Player& player = *(World::instance().player());
    b2Vec2 playerPos = player.body()->GetPosition();

    b2Vec2 d = playerPos - myPos;
    d.Normalize();
    d *= 1.5f;

    myPos += d;

    ArrowBuilderSpawner().setSpeed(30.0f).setPosition(myPos).setTarget(playerPos).spawn();

    activateState(lookingAroundState);

    std::cout << "Strike!" << std::endl;
}

void Archer::chasing()
{
//    return_if_deleted

    if (_lastKnownPlayerLocation.x < body()->GetPosition().x)
        tryToMoveLeft();
    else
        tryToMoveRight();

    _abyssSensor->setDirection(lookingDirection());
    if (_abyssSensor->isActive())
        tryToJump();

    if (_lastKnownPlayerLocation.x < body()->GetPosition().x)
        tryToMoveLeft();
    else
        tryToMoveRight();

    float dx = ::fabsf(_lastKnownPlayerLocation.x - body()->GetPosition().x);
    if (dx < 0.1f)
        callEventCallbacks(wentButNotFoundEvent);
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
//    return_if_deleted

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

void Archer::onDeath()
{
    return_if_deleted
    new EntityDestroyer(this);
//    markAsDeleted();
}
