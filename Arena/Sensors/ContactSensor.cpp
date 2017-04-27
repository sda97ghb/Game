#include "Arena/ObjectCounter.h"

#include "Arena/Sensors/ContactSensor.h"
#include "Arena/SensorListener.h"

ContactSensor::~ContactSensor()
{
    ObjectCounter<ContactSensor>::removeObject(this);
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

ContactSensor::ContactSensor()
{
    ObjectCounter<ContactSensor>::addObject(this);
}
