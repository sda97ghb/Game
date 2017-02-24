#include "Game/Ladder.h"

#include <iostream>

#include <SFML/Window/Keyboard.hpp>

#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/ImageScaler.h"
#include "Game/Player.h"

Ladder::Ladder() :
    _x(0.0f),
    _y1(0.0f),
    _y2(1.0f),
    _width(1.0f)
{
}

void Ladder::setCoordinates(float x, float y1, float y2)
{
    _x = x;
    _y1 = y1;
    _y2 = y2;
    setShape();
}

void Ladder::setWidth(float width)
{
    _width = width;
    setShape();
}

void Ladder::setTexture(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _texture.loadFromImage(ImageScaler::scale(original));
    _texture.setRepeated(true);
}

void Ladder::testPlayerOnIt()
{
    try {
        Player& player = Player::instance();
        b2Body& body = player.body();
        b2Transform transform;
        transform.SetIdentity();
        if (_shapeB2.TestPoint(transform, player.footPosition()))
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
        }
    }
    catch (Player::NoBodyException&)
    {
        std::cout << "something went wrong(" << std::endl;
    }
}

float Ladder::x() const
{
    return _x;
}

float Ladder::y1() const
{
    return _y1;
}

float Ladder::y2() const
{
    return _y2;
}

float Ladder::width() const
{
    return _width;
}

float Ladder::height() const
{
    return _y2 - _y1;
}

b2Vec2 Ladder::size() const
{
    return b2Vec2(width(), height());
}

b2PolygonShape& Ladder::shapeB2()
{
    return _shapeB2;
}

const b2PolygonShape& Ladder::shapeB2() const
{
    return _shapeB2;
}

sf::RectangleShape& Ladder::shapeSF()
{
    return _shapeSF;
}

const sf::RectangleShape& Ladder::shapeSF() const
{
    return _shapeSF;
}

sf::Texture& Ladder::texture()
{
    return _texture;
}

const sf::Texture& Ladder::texture() const
{
    return _texture;
}

void Ladder::setShape()
{
    b2Vec2 vertexes[4] = {b2Vec2(_x - _width / 2.0f, _y1),
                          b2Vec2(_x + _width / 2.0f, _y1),
                          b2Vec2(_x + _width / 2.0f, _y2),
                          b2Vec2(_x - _width / 2.0f, _y2)};
    _shapeB2.Set(vertexes, 4);
}
