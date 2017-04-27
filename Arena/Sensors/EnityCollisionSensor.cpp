#include <iostream>

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2Body.h"

#include "Arena/IdDispenser.h"
#include "Arena/ObjectCounter.h"

#include "Arena/Entity/Entity.h"

#include "Arena/Sensors/EnityCollisionSensor.h"

EnityCollisionSensor::EnityCollisionSensor() :
    _x(0.0f),
    _y(0.0f),
    _width(0.0f),
    _height(0.0f),
    _type(IdDispenser::getNewId()),
    _body(nullptr),
    _onCollisionCallback([](Entity*){})
{
    ObjectCounter<EnityCollisionSensor>::addObject(this);
}

EnityCollisionSensor::~EnityCollisionSensor()
{
    ObjectCounter<EnityCollisionSensor>::removeObject(this);
}

void EnityCollisionSensor::setPosition(float x, float y)
{
    _x = x;
    _y = y;
}

void EnityCollisionSensor::setSize(float width, float height)
{
    _width = width;
    _height = height;
}

void EnityCollisionSensor::setType(int type)
{
    _type = type;
}

void EnityCollisionSensor::hangOnBody(b2Body* body)
{
    _body = body;

    b2PolygonShape sensorShape;
    sensorShape.SetAsBox(_width, _height, b2Vec2(_x, _y), 0.0f);

    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &sensorShape;
    sensorFixtureDef.isSensor = true;

    b2Fixture* fixture = _body->CreateFixture(&sensorFixtureDef);
    fixture->SetUserData((void*)_type);
}

void EnityCollisionSensor::hit(b2Body* body)
{
    for (Entity* entity : ObjectCounter<Entity>::objects())
        if (entity->body() == body)
            _onCollisionCallback(entity);
}

void EnityCollisionSensor::setOnCollisionCallback(const EnityCollisionSensor::OnCollisionCallback& callback)
{
    _onCollisionCallback = callback;
}

int EnityCollisionSensor::type() const
{
    return _type;
}

b2Body* EnityCollisionSensor::body() const
{
    return _body;
}
