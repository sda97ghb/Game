#ifndef HITSENSOR_H
#define HITSENSOR_H

#include "Box2D/Dynamics/b2Body.h"

class Entity;

class HitSensor
{
public:
    HitSensor();

    void setPosition(float x, float y);
    void setSize(float width, float height);

    void setType(int type);

    void setActivationThreshold(float value);

    void setEntity(Entity* entity);

    void hangOnBody(b2Body* body);

    void hit(float speed);

    int type() const;

    const b2Body* body() const;

private:
    float _x;
    float _y;
    float _width;
    float _height;

    int _type;

    float _activationThreshold;

    b2Body* _body;

    Entity* _entity;
};

#endif // HITSENSOR_H
