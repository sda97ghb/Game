#include "TestPlayer.h"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/ImageScaler.h"

TestPlayer& TestPlayer::instance()
{
    static TestPlayer instance;
    return instance;
}

void TestPlayer::setTexture(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _texture.loadFromImage(ImageScaler::scale(original));
    _texture.setRepeated(true);
}

void TestPlayer::setPosition(float x, float y)
{
    _body->SetTransform(b2Vec2(x, y), _body->GetAngle());
}

void TestPlayer::setOnGround(bool value)
{
    _isOnGround = value;
}

float TestPlayer::x() const
{
    return _body->GetPosition().x;
}

float TestPlayer::y() const
{
    return _body->GetPosition().y;
}

float TestPlayer::cornerX() const
{
    return x() - width() / 2.0;
}

float TestPlayer::cornerY() const
{
    return y() - height() / 2.0;
}

float TestPlayer::width() const
{
    return 0.75f;
}

float TestPlayer::height() const
{
    return 1.75f;
}

b2Body& TestPlayer::body()
{
    return *_body;
}

const b2Body& TestPlayer::body() const
{
    return *_body;
}

sf::Texture& TestPlayer::texture()
{
    return _texture;
}

const sf::Texture& TestPlayer::texture() const
{
    return _texture;
}

sf::Sprite& TestPlayer::sprite()
{
    return _sprite;
}

const sf::Sprite& TestPlayer::sprite() const
{
    return _sprite;
}

void TestPlayer::stepLeft()
{
    if (_body->GetLinearVelocity().x >= -6.0)
        _body->ApplyLinearImpulse(b2Vec2(-0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
}

void TestPlayer::stepRight()
{
    if (_body->GetLinearVelocity().x <= 6.0)
        _body->ApplyLinearImpulse(b2Vec2(0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
}

void TestPlayer::jump()
{
    if (isOnGround())
        _body->ApplyLinearImpulse(b2Vec2(0.0f, 1.0f),
                                  _body->GetWorldCenter(), true);
}

bool TestPlayer::isOnGround() const
{
    return _isOnGround;
}

TestPlayer::TestPlayer() :
    _isOnGround(false)
{
}

void TestPlayer::setBody(b2Body* body)
{
    _body = body;
}

b2PolygonShape& TestPlayer::shape()
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

const b2PolygonShape& TestPlayer::shape() const
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
