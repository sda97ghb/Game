#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/IdDispenser.h"
#include "Arena/SensorListener.h"

#include "Arena/Sensors/ContactSensor.h"
#include "Arena/Sensors/ContactSensorBuilder.h"

ContactSensorBuilder::ContactSensorBuilder() :
    _type(IdDispenser::getNewId()),
    _dx(0.0f),
    _dy(0.0f),
    _width(1.0f),
    _height(1.0f),
    _body(nullptr),
    _shape(nullptr)
{}

ContactSensorBuilder& ContactSensorBuilder::setType(uint32_t type)
{
    _type = type;
    return *this;
}

ContactSensorBuilder& ContactSensorBuilder::setPosition(float dx, float dy)
{
    _dx = dx;
    _dy = dy;
    return *this;
}

ContactSensorBuilder& ContactSensorBuilder::setSize(float width, float height)
{
    _width = width;
    _height = height;
    return *this;
}

ContactSensorBuilder& ContactSensorBuilder::setBody(b2Body* body)
{
    _body = body;
    return *this;
}

ContactSensorBuilder& ContactSensorBuilder::setShape(b2Shape* shape)
{
    _shape = shape;
    return *this;
}

ContactSensor* ContactSensorBuilder::build()
{
    if (_body == nullptr)
        throw std::logic_error("Body is not set.");

    ContactSensor* sensor = new ContactSensor;

    sensor->_state = false;

    sensor->_type = _type;

    sensor->_body = _body;

    b2FixtureDef sensorFixtureDef;
    sensorFixtureDef.isSensor = true;

    b2PolygonShape sensorBoxShape;
    if (_shape == nullptr)
    {
        sensorBoxShape.SetAsBox(_width, _height, b2Vec2(_dx, _dy), 0.0f);
        sensorFixtureDef.shape = &sensorBoxShape;
    }
    else
    {
        sensorFixtureDef.shape = _shape;
    }

    b2Fixture* fixture = _body->CreateFixture(&sensorFixtureDef);
    fixture->SetUserData((void*)_type);

//    SensorListener::instance().registrySensor(*sensor);

    return sensor;
}
