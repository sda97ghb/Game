#include <cmath>

#include "SFML/Window/Keyboard.hpp"

#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/Furniture/Cable.h"
#include "Arena/Entity/Player.h"

Cable::Cable() :
    _x1(0.0f),
    _y1(0.0f),
    _x2(0.0f),
    _y2(0.0f)
{
}

void Cable::setBegin(float x, float y)
{
    _x1 = x;
    _y1 = y;
}

void Cable::setEnd(float x, float y)
{
    _x2 = x;
    _y2 = y;
}

void Cable::testPlayerOnIt()
{
    try {
        Player& player = Player::instance();
        b2Body& body = player.body();
        b2Transform transform;
        transform.SetIdentity();
        if (_shapeB2.TestPoint(transform, body.GetPosition()))
        {
            b2Vec2 velocity = body.GetLinearVelocity();

            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) &&
                !sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
                velocity.x *= body.GetFixtureList()->GetFriction();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
                velocity.y = 3.0f;
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
                velocity.y = -3.0f;
            else
                velocity.y = 0.0f;

            body.SetLinearVelocity(velocity);

            body.ApplyForce(b2Vec2(0.0f, 12.0f), body.GetWorldCenter(), true);

            player.spriteAnimator().setCurrentGroup("climbing");
        }
    }
    catch (Player::NoBodyException&)
    {
    }
}

float Cable::x1() const
{
    return _x1;
}

float Cable::x2() const
{
    return _x2;
}

float Cable::y1() const
{
    return _y1;
}

float Cable::y2() const
{
    return _y2;
}

void Cable::setShape()
{
    b2Vec2 begin(_x1, _x2);
    b2Vec2 end(_x2, _y2);
    b2Vec2 s = end - begin;
    s.Normalize();
    b2Vec2 normal(-s.y, s.x); // normal is ccw rotated s

    b2Vec2 vertexes[4] = {begin - normal,
                          end   - normal,
                          end   + normal,
                          begin + normal};
    _shapeB2.Set(vertexes, 4);
}
