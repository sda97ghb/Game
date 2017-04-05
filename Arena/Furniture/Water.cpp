#include "SFML/Window/Keyboard.hpp"

#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/Player.h"
#include "Arena/Water.h"

void Water::testPlayerOnIt()
{
    try {
        Player& player = Player::instance();
        b2Body& body = player.body();
        b2Transform transform;
        transform.SetIdentity();
        if (_shapeB2.TestPoint(transform, player.body().GetPosition()))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                if (body.GetLinearVelocity().y < 2.0f)
                    body.ApplyLinearImpulse(b2Vec2(0.0f, 200.0f),
                                            body.GetWorldCenter(), true);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                if (body.GetLinearVelocity().y > -2.0f)
                    body.ApplyLinearImpulse(b2Vec2(0.0f, -200.0f),
                                            body.GetWorldCenter(), true);

            b2Vec2 velocity = body.GetLinearVelocity();
            velocity.x *= 0.9;
            velocity.y *= 0.9;
            body.SetLinearVelocity(velocity);

            player.spriteAnimator().setCurrentGroup("climbing");
        }
    }
    catch (Player::NoBodyException&)
    {
    }
}
