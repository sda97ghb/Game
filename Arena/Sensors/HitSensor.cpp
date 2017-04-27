#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/ObjectCounter.h"
#include "Arena/SensorListener.h"

#include "Arena/Sensors/HitSensor.h"

HitSensor::~HitSensor()
{
    ObjectCounter<HitSensor>::removeObject(this);
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

HitSensor::HitSensor()
{
    ObjectCounter<HitSensor>::addObject(this);
}
