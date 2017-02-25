#ifndef SENSORCONTACTLISTENER_H
#define SENSORCONTACTLISTENER_H

#include "Box2D/Dynamics/b2WorldCallbacks.h"

class SensorContactListener : public b2ContactListener
{
public:
    enum
    {
        GROUND_SENSOR_TYPE = 2,
        LEFT_SENSOR_TYPE   = 3,
        RIGHT_SENSOR_TYPE  = 4
    };

private:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    void setOnGround(b2Body* body, bool value);
    void setLeftContact(b2Body* body, bool value);
    void setRightContact(b2Body* body, bool value);
};

#endif // SENSORCONTACTLISTENER_H
