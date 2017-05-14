#include "SFML/Window/Keyboard.hpp"

#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/World.h"

#include "Arena/Entity/Player.h"

#include "Arena/Furniture/Water.h"

void Water::testPlayerOnIt()
{
    try
    {
        if (World::instance().player1()->isAlive())
            testBody(*World::instance().player1()->body());
        if (World::instance().player2()->isAlive())
            testBody(*World::instance().player2()->body());

//        player.spriteAnimator().setCurrentGroup("climbing");
    }
    catch (...)
    {
    }
}

bool Water::testBody(b2Body& body)
{
    b2Transform transform;
    transform.SetIdentity();
    if (!_shapeB2.TestPoint(transform, body.GetPosition()))
        return false;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        if (body.GetLinearVelocity().y < 2.0f)
            body.ApplyLinearImpulse(b2Vec2(0.0f, 200.0f),
                                    body.GetWorldCenter(), true);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        if (body.GetLinearVelocity().y > -2.0f)
            body.ApplyLinearImpulse(b2Vec2(0.0f, -200.0f),
                                    body.GetWorldCenter(), true);

    b2Vec2 velocity = body.GetLinearVelocity();
    velocity.x *= 0.9;
    velocity.y *= 0.9;
    body.SetLinearVelocity(velocity);

    return true;
}
