#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/IdDispenser.h"

#include "Arena/Sensors/HitSensor.h"
#include "Arena/Sensors/HitSensorBuilder.h"

HitSensorBuilder::HitSensorBuilder() :
    _dx(0.0f),
    _dy(0.0f),
    _width(1.0f),
    _height(1.0f),
    _type(IdDispenser::getNewId()),
    _activationThreshold(1.0f),
    _requireActivationThreshold(true),
    _body(nullptr),
    _onHitCallback([](float){})
{}

HitSensorBuilder& HitSensorBuilder::setType(uint32_t type)
{
    _type = type;
    return *this;
}

HitSensorBuilder& HitSensorBuilder::setPosition(float dx, float dy)
{
    _dx = dx;
    _dy = dy;
    return *this;
}

HitSensorBuilder& HitSensorBuilder::setSize(float width, float height)
{
    _width = width;
    _height = height;
    return *this;
}

HitSensorBuilder& HitSensorBuilder::setActivationThreshold(float speed)
{
    _activationThreshold = speed;
    return *this;
}

HitSensorBuilder& HitSensorBuilder::setOnHitCallback(const HitSensorBuilder::OnHitCallback& callback)
{
    _onHitCallback = callback;
    return *this;
}

HitSensorBuilder& HitSensorBuilder::setBody(b2Body* body)
{
    _body = body;
    return *this;
}

HitSensorBuilder& HitSensorBuilder::setRequireActivationThreshold(bool flag)
{
    _requireActivationThreshold = flag;
    return *this;
}

HitSensor* HitSensorBuilder::build()
{
    if (_body == nullptr)
        throw std::logic_error("Body is not set");

    HitSensor* sensor = new HitSensor;

    sensor->_activationThreshold = _activationThreshold;
    sensor->_requireActivationThreshold = _requireActivationThreshold;

    sensor->_onHitCallback = _onHitCallback;

    sensor->_type = _type;

    sensor->_body = _body;

    b2PolygonShape sensorShape;
    sensorShape.SetAsBox(_width, _height, b2Vec2(_dx, _dy), 0.0f);

    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.shape = &sensorShape;
    sensorFixtureDef.isSensor = true;

    b2Fixture* fixture = _body->CreateFixture(&sensorFixtureDef);
    fixture->SetUserData((void*)_type);

    return sensor;
}
