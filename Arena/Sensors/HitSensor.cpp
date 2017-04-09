#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/SensorListener.h"

#include "Arena/Sensors/HitSensor.h"

HitSensor::HitSensor() :
    _x(0.0f),
    _y(0.0f),
    _width(0.0f),
    _height(0.0f),
    _type(0),
    _activationThreshold(0.0f),
    _requireActivationThreshold(true),
    _body(nullptr)
{
}

void HitSensor::setPosition(float x, float y)
{
    _x = x;
    _y = y;
}

void HitSensor::setSize(float width, float height)
{
    _width = width;
    _height = height;
}

void HitSensor::setType(int type)
{
    _type = type;
}

void HitSensor::setActivationThreshold(float value)
{
    _activationThreshold = value;
}

void HitSensor::hangOnBody(b2Body* body)
{
    _body = body;

    b2PolygonShape sensorShape;
    sensorShape.SetAsBox(_width, _height, b2Vec2(_x, _y), 0.0f);

    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &sensorShape;
    sensorFixtureDef.isSensor = true;

    b2Fixture* fixture = _body->CreateFixture(&sensorFixtureDef);
    fixture->SetUserData((void*)_type);

    SensorListener::instance().registrySensor(*this);
}

void HitSensor::hit(float speed)
{
    if (_requireActivationThreshold && speed < _activationThreshold)
        return;
    _onHitCallback(speed);
}

int HitSensor::type() const
{
    return _type;
}

const b2Body* HitSensor::body() const
{
    return _body;
}

HitSensor::OnHitCallback HitSensor::onHitCallback() const
{
    return _onHitCallback;
}

void HitSensor::setOnHitCallback(const OnHitCallback& onHitCallback)
{
    _onHitCallback = onHitCallback;
}

void HitSensor::setRequireActivationThreshold(bool requireActivationThreshold)
{
    _requireActivationThreshold = requireActivationThreshold;
}
