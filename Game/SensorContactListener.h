#ifndef SENSORCONTACTLISTENER_H
#define SENSORCONTACTLISTENER_H

#include "Box2D/Dynamics/b2WorldCallbacks.h"

class SensorContactListener : public b2ContactListener
{
public:
    static constexpr int GROUND_SENSOR_TYPE = 2;

private:
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);

    void setOnGround(b2Body* body, bool value);
};

#endif // SENSORCONTACTLISTENER_H
