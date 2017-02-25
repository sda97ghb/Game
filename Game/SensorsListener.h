#ifndef SENSORLISTENER_H
#define SENSORLISTENER_H

#include <list>

#include "Box2D/Dynamics/b2WorldCallbacks.h"

#include "Game/ContactSensor.h"
#include "Game/HitSensor.h"

class SensorsListener : public b2ContactListener
{
public:
    static SensorsListener& instance();

    enum
    {
        GROUND_CONTACT_SENSOR_TYPE = 1,
        LEFT_CONTACT_SENSOR_TYPE   = 2,
        RIGHT_CONTACT_SENSOR_TYPE  = 3,
        GROUND_HIT_SENSOR_TYPE     = 4
    };

    void registrySensor(ContactSensor& sensor);
    void registrySensor(HitSensor& sensor);

private:
    SensorsListener() = default;
    SensorsListener(const SensorsListener&) = delete;
    void operator= (const SensorsListener&) = delete;

    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    void setSensor(b2Body* body, int type, bool value);

    void hitSensor(b2Body* body, int type, float speed);

    std::list<ContactSensor*> _contactSensors;
    std::list<HitSensor*> _hitSensors;
};

#endif // SENSORLISTENER_H
