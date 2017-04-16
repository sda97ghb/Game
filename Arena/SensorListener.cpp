#include <iostream>

#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Arena/ObjectCounter.h"
#include "Arena/SensorListener.h"

#include "Arena/Sensors/EnityCollisionSensor.h"

SensorListener& SensorListener::instance()
{
    static SensorListener instance;
    return instance;
}

void SensorListener::registrySensor(ContactSensor& sensor)
{
    _contactSensors.push_back(&sensor);
}

void SensorListener::registrySensor(HitSensor& sensor)
{
    _hitSensors.push_back(&sensor);
}

void SensorListener::BeginContact(b2Contact* contact)
{
    int aSensorType = (int)(contact->GetFixtureA()->GetUserData());
    int bSensorType = (int)(contact->GetFixtureB()->GetUserData());

    if (aSensorType != 0)
        setSensor(contact->GetFixtureA()->GetBody(), aSensorType, true);

    if (bSensorType != 0)
        setSensor(contact->GetFixtureB()->GetBody(), bSensorType, true);

    b2Vec2 vA = contact->GetFixtureA()->GetBody()->GetLinearVelocity();
    b2Vec2 vB = contact->GetFixtureB()->GetBody()->GetLinearVelocity();
//    float speed = (vA - vB).Length();
    float speed = ::abs((vA - vB).y);

    if (aSensorType != 0)
        hitSensor(contact->GetFixtureA()->GetBody(), aSensorType, speed);

    if (bSensorType != 0)
        hitSensor(contact->GetFixtureB()->GetBody(), bSensorType, speed);

    for (EnityCollisionSensor* sensor : ObjectCounter<EnityCollisionSensor>::objects())
    {
        if (sensor->body() == contact->GetFixtureA()->GetBody() &&
            sensor->type() == aSensorType)
            sensor->hit(contact->GetFixtureB()->GetBody());
        if (sensor->body() == contact->GetFixtureB()->GetBody() &&
            sensor->type() == bSensorType)
            sensor->hit(contact->GetFixtureA()->GetBody());
    }
}

void SensorListener::EndContact(b2Contact* contact)
{
    int aSensorType = (int)(contact->GetFixtureA()->GetUserData());
    int bSensorType = (int)(contact->GetFixtureB()->GetUserData());

    if (aSensorType != 0)
        setSensor(contact->GetFixtureA()->GetBody(), aSensorType, false);

    if (bSensorType != 0)
        setSensor(contact->GetFixtureB()->GetBody(), bSensorType, false);
}

void SensorListener::setSensor(b2Body* body, int type, bool value)
{
    for (ContactSensor* sensor : _contactSensors)
        if (sensor->body() == body && sensor->type() == type)
        {
            sensor->set(value);
            return;
        }
}

void SensorListener::hitSensor(b2Body* body, int type, float speed)
{
    for (HitSensor* sensor : _hitSensors)
        if (sensor->body() == body && sensor->type() == type)
        {
            sensor->hit(speed);
            return;
        }
}
