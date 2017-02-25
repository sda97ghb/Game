#ifndef CONTACT_SENSOR_H
#define CONTACT_SENSOR_H

#include "Box2D/Dynamics/b2Body.h"

class ContactSensor
{
public:
    ContactSensor();

    void setPosition(float x, float y);
    void setSize(float width, float height);

    void setType(int type);

    void hangOnBody(b2Body* body);

    void set(bool state);

    bool isActive() const;

    int type() const;
    const b2Body* body() const;

private:
    float _x;
    float _y;
    float _width;
    float _height;

    bool _state;
    int _type;

    b2Body* _body;
};

#endif // CONTACT_SENSOR_H
