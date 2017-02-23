#include "Game/Entity.h"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/ImageScaler.h"

Entity::Entity() :
    _body(nullptr),
    _isOnGround(false),
    _health(1.0),
    _mana(0.0)
{
}

void Entity::setTexture(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _texture.loadFromImage(ImageScaler::scale(original));
    _texture.setRepeated(true);
}

void Entity::setPosition(float x, float y)
{
    _body->SetTransform(b2Vec2(x, y), _body->GetAngle());
}

void Entity::setOnGround(bool value)
{
    _isOnGround = value;
}

bool Entity::isOnGround() const
{
    return _isOnGround;
}

b2Vec2 Entity::footPosition() const
{
    if (!_body)
        throw NoBodyException();
    b2Vec2 pos = _body->GetPosition();
    pos.y -= height() / 2.0;
    return pos;
}

void Entity::setBody(b2Body* body)
{
    _body = body;
}

b2Body& Entity::body()
{
    return *_body;
}

const b2Body& Entity::body() const
{
    return *_body;
}

sf::Texture& Entity::texture()
{
    return _texture;
}

const sf::Texture& Entity::texture() const
{
    return _texture;
}

sf::Sprite& Entity::sprite()
{
    return _sprite;
}

const sf::Sprite& Entity::sprite() const
{
    return _sprite;
}

b2PolygonShape& Entity::shape()
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

const b2PolygonShape& Entity::shape() const
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

void Entity::stepLeft()
{
    if (_body->GetLinearVelocity().x >= -6.0)
        _body->ApplyLinearImpulse(b2Vec2(-0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
}

void Entity::stepRight()
{
    if (_body->GetLinearVelocity().x <= 6.0)
        _body->ApplyLinearImpulse(b2Vec2(0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
}

void Entity::jump()
{
    if (isOnGround())
        _body->ApplyLinearImpulse(b2Vec2(0.0f, 1.0f),
                                  _body->GetWorldCenter(), true);
}

void Entity::setMaxHealth(float value)
{
    _maxHealth = value;
}

void Entity::setHealth(float value)
{
    if (value < 0.0f)
        _health = 0.0f;
    else if (value > _maxHealth)
        _health = _maxHealth;
    else
        _health = value;
}

void Entity::makeDamage(float value)
{
    _health -= value;
}

void Entity::heal(float value)
{
    _health += value;
    if (_health > _maxHealth)
        _health = _maxHealth;
}

void Entity::kill()
{
    _health = 0.0f;
}

void Entity::setMaxMana(float value)
{
    _maxMana = value;
}

void Entity::setMana(float value)
{
    if (value > _maxMana)
        _mana = _maxMana;
    else
        _mana = value;
}

bool Entity::isAlive() const
{
    return _health > 0.0f;
}

float Entity::health() const
{
    return _health;
}

float Entity::mana() const
{
    return _mana;
}
