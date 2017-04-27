#include <stdexcept>

#include "Arena/Sensors/AbyssSensor.h"
#include "Arena/Sensors/AbyssSensorBuilder.h"

AbyssSensorBuilder::AbyssSensorBuilder() :
    _dx(1.0f),
    _dy(-2.0f),
    _body(nullptr)
{}

AbyssSensorBuilder& AbyssSensorBuilder::setDx(float dx)
{
    _dx = dx;
    return *this;
}

AbyssSensorBuilder& AbyssSensorBuilder::setDy(float dy)
{
    _dy = dy;
    return *this;
}

AbyssSensorBuilder& AbyssSensorBuilder::setBody(b2Body* body)
{
    _body = body;
    return *this;
}

AbyssSensor* AbyssSensorBuilder::build()
{
    if (_body == nullptr)
        throw std::logic_error("Body is not specified");

    AbyssSensor* sensor = new AbyssSensor;
    sensor->_dx = _dx;
    sensor->_dy = _dy;
    sensor->_body = _body;

    return sensor;
}
