#ifndef CONTACTSENSORLISTENER_H
#define CONTACTSENSORLISTENER_H

#include <list>

#include "Box2D/Dynamics/b2WorldCallbacks.h"

#include "Game/ContactSensor.h"

class ContactSensorListener : public b2ContactListener
{
public:
    static ContactSensorListener& instance();

    enum
    {
        GROUND_SENSOR_TYPE = 2,
        LEFT_SENSOR_TYPE   = 3,
        RIGHT_SENSOR_TYPE  = 4
    };

    void registrySensor(ContactSensor& sensor);

private:
    ContactSensorListener() = default;
    ContactSensorListener(const ContactSensorListener&) = delete;
    void operator= (const ContactSensorListener&) = delete;

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    void setSensor(b2Body* body, int type, bool value);

    std::list<ContactSensor*> _sensors;
};

#endif // CONTACTSENSORLISTENER_H
