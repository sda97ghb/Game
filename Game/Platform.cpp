#include "Game/Platform.h"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/ImageScaler.h"

void Platform::setTexture(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _texture.loadFromImage(ImageScaler::scale(original));
    _texture.setRepeated(true);
}

b2PolygonShape& Platform::shapeB2()
{
    b2Fixture* fixture = _body->GetFixtureList();
    if (fixture == nullptr)
        throw NoShapeException();
    b2Shape* shape = fixture->GetShape();
    if (shape == nullptr)
        throw NoShapeException();
    return *static_cast<b2PolygonShape*>(shape);
}

const b2PolygonShape& Platform::shapeB2() const
{
    b2Fixture* fixture = _body->GetFixtureList();
    if (fixture == nullptr)
        throw NoShapeException();
    b2Shape* shape = fixture->GetShape();
    if (shape == nullptr)
        throw NoShapeException();
    return *static_cast<b2PolygonShape*>(shape);
}

void Platform::setBody(b2Body* body)
{
    _body = body;
}

void Platform::setShape(const b2PolygonShape& shape)
{
    if (_body == nullptr)
        throw NoBodyException();
    _body->CreateFixture(&shape, 0.0f);
}

b2Body& Platform::body()
{
    return *_body;
}

const b2Body&Platform::body() const
{
    return *_body;
}

sf::ConvexShape& Platform::shapeSF()
{
    return _shape;
}

const sf::ConvexShape&Platform::shapeSF() const
{
    return _shape;
}

sf::Texture& Platform::texture()
{
    return _texture;
}

const sf::Texture&Platform::texture() const
{
    return _texture;
}
