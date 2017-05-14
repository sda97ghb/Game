#include <iostream>

#include "Arena/GlobalConstants.h"

#include "Arena/Entity/Player.h"

Player::Player() :
    _attack{nullptr}
{
    addEventCallback(landingEvent, METHOD_CALLBACK(onLanding));
    addEventCallback(updateEvent, [&](){
        b2Vec2 velocity = body()->GetLinearVelocity();
        velocity.x *= 0.5;
        body()->SetLinearVelocity(velocity);
    });
    addEventCallback(readyForAttackEvent, METHOD_CALLBACK(performAttack));
}

Player::~Player()
{
    if (_attack != nullptr)
        delete _attack;
    _attack = nullptr;
}

void Player::onGroundHit(float speed)
{
    return_if_deleted

    makeDamage(speed);
}

void Player::onLanding()
{
    return_if_deleted

    if (isStateActive(jumpingState))
        deactivateState(jumpingState);
}

void Player::tryToJump()
{
    return_if_deleted

    if (!isAlive())
        return;

    if (isStateActive(jumpingState))
        return;

    if (!_groundContactSensor->isActive())
        return;

    if (isPreparingForAttack())
        return;

    float yImpulse = body()->GetMass() * ::sqrt(g * jumpHeight() * 2.0);
    body()->ApplyLinearImpulse(b2Vec2(0.0f, yImpulse),
                               body()->GetWorldCenter(),
                               true);
    activateState(jumpingState);
}

void Player::tryToMoveLeft()
{
    return_if_deleted

    if (!isAlive())
        return;

    if (_leftContactSensor->isActive())
        return;

    if (isPreparingForAttack())
        return;

    const float xImpulse = - body()->GetMass() * movementSpeed();
    body()->ApplyLinearImpulse(b2Vec2(xImpulse, 0.0f),
                               body()->GetWorldCenter(),
                               true);

    setLookingDirection(Direction::left);
}

void Player::tryToMoveRight()
{
    return_if_deleted

    if (!isAlive())
        return;

    if (_rightContactSensor->isActive())
        return;

    if (isPreparingForAttack())
        return;

    const float xImpulse = body()->GetMass() * movementSpeed();
    body()->ApplyLinearImpulse(b2Vec2(xImpulse, 0.0f),
                               body()->GetWorldCenter(),
                               true);

    setLookingDirection(Direction::right);
}

void Player::tryToAttack(Attack* attack, float delay, bool attackImmediatly)
{
    if (!isAlive())
        return;

    if (isStateActive(preparingForAttackState))
        return;

    if (attackImmediatly)
        attack->perform();
    else
        _attack = attack;

    _attackReloadSensor->setTime(delay);
    _attackReloadSensor->start();
    activateState(preparingForAttackState);
}

float Player::jumpHeight() const
{
    return 4.0f;
}

float Player::movementSpeed() const
{
    return 0.85 * 10.44f; // 10.44 m/s = Usain Bolt speed
}

void Player::performAttack()
{
    if (_attack != nullptr)
        _attack->perform();

    delete _attack;
    _attack = nullptr;

    deactivateState(preparingForAttackState);
}

bool Player::isPreparingForAttack() const
{
    return isStateActive(preparingForAttackState);
}
