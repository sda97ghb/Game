#include <iostream>

#include "Arena/GlobalConstants.h"

#include "Arena/Entity/Player.h"

Player::Player() :
    _state(State::normal)
{
    setEventCallback(landingEvent, METHOD_CALLBACK(onLanding));
    setEventCallback(updateEvent, [&](){
        b2Vec2 velocity = body()->GetLinearVelocity();
        velocity.x *= 0.5;
        body()->SetLinearVelocity(velocity);
    });
}

void Player::onGroundHit(float speed)
{
    makeDamage(speed);
}

void Player::onLanding()
{
    if (_state == State::jumping)
        _state = State::normal;
}

void Player::tryToJump()
{
    if (!isAlive())
        return;

    if (_state != State::normal)
        return;

    if (!_groundContactSensor.isActive())
        return;

    float yImpulse = body()->GetMass() * ::sqrt(g * jumpHeight() * 2.0);
    body()->ApplyLinearImpulse(b2Vec2(0.0f, yImpulse),
                               body()->GetWorldCenter(),
                               true);
    _state = State::jumping;
}

void Player::tryToMoveLeft()
{
    if (!isAlive())
        return;

    if (_leftContactSensor.isActive())
        return;

//    b2Vec2 velocity = body()->GetLinearVelocity();
//    velocity.x = 0;
//    body()->SetLinearVelocity(velocity);

    const float xImpulse = - body()->GetMass() * movementSpeed();
    body()->ApplyLinearImpulse(b2Vec2(xImpulse, 0.0f),
                               body()->GetWorldCenter(),
                               true);

    setLookingDirection(Direction::left);
}

void Player::tryToMoveRight()
{
    if (!isAlive())
        return;

    if (_rightContactSensor.isActive())
        return;

//    b2Vec2 velocity = body()->GetLinearVelocity();
//    velocity.x = 0;
//    body()->SetLinearVelocity(velocity);

    const float xImpulse = body()->GetMass() * movementSpeed();
    body()->ApplyLinearImpulse(b2Vec2(xImpulse, 0.0f),
                               body()->GetWorldCenter(),
                               true);

    setLookingDirection(Direction::right);
}

float Player::jumpHeight() const
{
    return 4.0f;
}

float Player::movementSpeed() const
{
    return 0.85 * 10.44f; // 10.44 m/s = usain bolt top speed
}
