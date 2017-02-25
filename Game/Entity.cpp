#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/ContactSensorListener.h"
#include "Game/Entity.h"

Entity::Entity() :
    _body(nullptr),
    _health(1.0f),
    _mana(0.0f)
{
}

void Entity::constructBody()
{
    if (_body == nullptr)
        throw NoBodyException();
    {
        b2PolygonShape entityShape;
        entityShape.SetAsBox(width() / 2.0f, height() / 2.0f);
        b2FixtureDef entityFixtureDef;
        entityFixtureDef.shape = &entityShape;
        entityFixtureDef.density = 1.0f;
        entityFixtureDef.friction = 20.0f;
        entityFixtureDef.restitution = 0.0f;
        body().CreateFixture(&entityFixtureDef);
    }

    _groundSensor.setType(ContactSensorListener::GROUND_SENSOR_TYPE);
    _groundSensor.setPosition(0.0f, -height() / 2.0f);
    _groundSensor.setSize(width() / 2.0f * 0.9f, 0.1);
    _groundSensor.hangOnBody(_body);

    _leftSensor.setType(ContactSensorListener::LEFT_SENSOR_TYPE);
    _leftSensor.setPosition(-width() / 2.0, 0.0f);
    _leftSensor.setSize(0.1, height() / 2.0f * 0.9f);
    _leftSensor.hangOnBody(_body);

    _rightSensor.setType(ContactSensorListener::RIGHT_SENSOR_TYPE);
    _rightSensor.setPosition(width() / 2.0, 0.0f);
    _rightSensor.setSize(0.1, height() / 2.0f * 0.9f);
    _rightSensor.hangOnBody(_body);
}

void Entity::setPosition(float x, float y)
{
    _body->SetTransform(b2Vec2(x, y), _body->GetAngle());
}

b2Vec2 Entity::footPosition() const
{
    if (!_body)
        throw NoBodyException();
    b2Vec2 pos = _body->GetPosition();
    pos.y -= height() / 2.0f;
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
    if (_leftSensor.isActive())
        return;
    if (_body->GetLinearVelocity().x >= -6.0f)
        _body->ApplyLinearImpulse(b2Vec2(-0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
    _spriteAnimator.setCurrentGroup("going_left");
}

void Entity::stepRight()
{
    if (_rightSensor.isActive())
        return;
    if (_body->GetLinearVelocity().x <= 6.0f)
        _body->ApplyLinearImpulse(b2Vec2(0.4f, 0.0f),
                                  _body->GetWorldCenter(), true);
    _spriteAnimator.setCurrentGroup("going_right");
}

void Entity::jump()
{
    if (!_groundSensor.isActive())
        return;
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

SpriteAnimator& Entity::spriteAnimator()
{
    return _spriteAnimator;
}
