#include "Box2D/Dynamics/Contacts/b2Contact.h"

#include "Game/ContactSensorListener.h"

ContactSensorListener& ContactSensorListener::instance()
{
    static ContactSensorListener instance;
    return instance;
}

void ContactSensorListener::registrySensor(ContactSensor& sensor)
{
    _sensors.push_back(&sensor);
}

void ContactSensorListener::BeginContact(b2Contact* contact)
{   
    int aSensorType = (int)(contact->GetFixtureA()->GetUserData());
    int bSensorType = (int)(contact->GetFixtureB()->GetUserData());

    if (aSensorType != 0)
        setSensor(contact->GetFixtureA()->GetBody(), aSensorType, true);

    if (bSensorType != 0)
        setSensor(contact->GetFixtureB()->GetBody(), bSensorType, true);
}

void ContactSensorListener::EndContact(b2Contact* contact)
{
    int aSensorType = (int)(contact->GetFixtureA()->GetUserData());
    int bSensorType = (int)(contact->GetFixtureB()->GetUserData());

    if (aSensorType != 0)
        setSensor(contact->GetFixtureA()->GetBody(), aSensorType, false);

    if (bSensorType != 0)
        setSensor(contact->GetFixtureB()->GetBody(), bSensorType, false);
}

void ContactSensorListener::setSensor(b2Body* body, int type, bool value)
{
    for (ContactSensor* sensor : _sensors)
        if (sensor->body() == body && sensor->type() == type)
        {
            sensor->set(value);
            return;
        }
}
