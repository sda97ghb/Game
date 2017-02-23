#include "TestEntity.h"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/ImageScaler.h"

TestEntity::TestEntity() :
    _body(nullptr),
    _isOnGround(false)
{
}

void TestEntity::setTexture(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _texture.loadFromImage(ImageScaler::scale(original));
    _texture.setRepeated(true);
}

void TestEntity::setPosition(float x, float y)
{
    _body->SetTransform(b2Vec2(x, y), _body->GetAngle());
}

void TestEntity::setOnGround(bool value)
{
    _isOnGround = value;
}

bool TestEntity::isOnGround() const
{
    return _isOnGround;
}

b2Vec2 TestEntity::footPosition() const
{
    if (!_body)
        throw NoBodyException();
    b2Vec2 pos = _body->GetPosition();
    pos.y -= height() / 2.0;
    return pos;
}

void TestEntity::setBody(b2Body* body)
{
    _body = body;
}

b2Body& TestEntity::body()
{
    return *_body;
}

const b2Body& TestEntity::body() const
{
    return *_body;
}

sf::Texture& TestEntity::texture()
{
    return _texture;
}

const sf::Texture& TestEntity::texture() const
{
    return _texture;
}

sf::Sprite& TestEntity::sprite()
{
    return _sprite;
}

const sf::Sprite& TestEntity::sprite() const
{
    return _sprite;
}

b2PolygonShape& TestEntity::shape()
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

const b2PolygonShape& TestEntity::shape() const
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

void TestEntity::stepLeft()
{
    if (_body->GetLinearVelocity().x >= -6.0)
        _body->ApplyLinearImpulse(b2Vec2(-0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
}

void TestEntity::stepRight()
{
    if (_body->GetLinearVelocity().x <= 6.0)
        _body->ApplyLinearImpulse(b2Vec2(0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
}

void TestEntity::jump()
{
    if (isOnGround())
        _body->ApplyLinearImpulse(b2Vec2(0.0f, 1.0f),
                                  _body->GetWorldCenter(), true);
}
