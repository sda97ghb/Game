#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/ContactSensor.h"
#include "Game/ContactSensorListener.h"

ContactSensor::ContactSensor() :
    _x(0.0f),
    _y(0.0f),
    _width(0.0f),
    _height(0.0f),
    _state(false),
    _type(0),
    _body(nullptr)
{
}

void ContactSensor::setPosition(float x, float y)
{
    _x = x;
    _y = y;
}

void ContactSensor::setSize(float width, float height)
{
    _width = width;
    _height = height;
}

void ContactSensor::setType(int type)
{
    _type = type;
}

void ContactSensor::hangOnBody(b2Body* body)
{
    _body = body;

    b2PolygonShape sensorShape;
    sensorShape.SetAsBox(_width, _height, b2Vec2(_x, _y), 0.0f);

    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &sensorShape;
    sensorFixtureDef.isSensor = true;

    b2Fixture* fixture = _body->CreateFixture(&sensorFixtureDef);
    fixture->SetUserData((void*)_type);

    ContactSensorListener::instance().registrySensor(*this);
}

void ContactSensor::set(bool state)
{
    _state = state;
}

bool ContactSensor::isActive() const
{
    return _state;
}

int ContactSensor::type() const
{
    return _type;
}

const b2Body* ContactSensor::body() const
{
    return _body;
}
