#include "TestArcher.h"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/ImageScaler.h"

TestArcher::TestArcher() :
    _body(nullptr),
    _isOnGround(false)
{
}

void TestArcher::setTexture(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _texture.loadFromImage(ImageScaler::scale(original));
    _texture.setRepeated(true);
}

void TestArcher::setPosition(float x, float y)
{
    _body->SetTransform(b2Vec2(x, y), _body->GetAngle());
}

void TestArcher::setBody(b2Body* body)
{
    _body = body;
}

float TestArcher::x() const
{
    return _body->GetPosition().x;
}

float TestArcher::y() const
{
    return _body->GetPosition().y;
}

float TestArcher::cornerX() const
{
    return x() - width() / 2.0;
}

float TestArcher::cornerY() const
{
    return y() - height() / 2.0;
}

float TestArcher::width() const
{
    return 0.75f;
}

float TestArcher::height() const
{
    return 1.75f;
}

b2Body& TestArcher::body()
{
    return *_body;
}

const b2Body& TestArcher::body() const
{
    return *_body;
}

sf::Texture& TestArcher::texture()
{
    return _texture;
}

const sf::Texture& TestArcher::texture() const
{
    return _texture;
}

sf::Sprite& TestArcher::sprite()
{
    return _sprite;
}

const sf::Sprite& TestArcher::sprite() const
{
    return _sprite;
}

b2PolygonShape& TestArcher::shape()
{
    if (_body == nullptr)
        throw NoBodyException();
    b2Fixture* fixture = _body->GetFixtureList();
    if (fixture == nullptr)
        throw NoFixtureException();
    b2Shape* shape = fixture->GetShape();
    if (shape == nullptr)
        throw NoShapeException();
    return *static_cast<b2PolygonShape*>(shape);
}

const b2PolygonShape& TestArcher::shape() const
{
    if (_body == nullptr)
        throw NoBodyException();
    b2Fixture* fixture = _body->GetFixtureList();
    if (fixture == nullptr)
        throw NoFixtureException();
    b2Shape* shape = fixture->GetShape();
    if (shape == nullptr)
        throw NoShapeException();
    return *static_cast<b2PolygonShape*>(shape);
}

void TestArcher::stepLeft()
{
    if (_body->GetLinearVelocity().x >= -6.0)
        _body->ApplyLinearImpulse(b2Vec2(-0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
}

void TestArcher::stepRight()
{
    if (_body->GetLinearVelocity().x <= 6.0)
        _body->ApplyLinearImpulse(b2Vec2(0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
}

void TestArcher::jump()
{
    if (isOnGround())
        _body->ApplyLinearImpulse(b2Vec2(0.0f, 1.0f),
                                  _body->GetWorldCenter(), true);
}

void TestArcher::setOnGround(bool value)
{
    _isOnGround = value;
}

bool TestArcher::isOnGround() const
{
    return _isOnGround;
}
