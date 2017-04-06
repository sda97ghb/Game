#ifndef ABYSSSENSOR_H
#define ABYSSSENSOR_H

#include "Box2D/Dynamics/b2Body.h"

#include "Arena/Direction.h"

class AbyssSensor
{
public:
    AbyssSensor();

    void hangOnBody(b2Body* body);

    bool isActive();

    void setDx(float dx);
    void setDy(float dy);

    float dx() const;
    float dy() const;

    Direction direction() const;
    void setDirection(const Direction& direction);

private:
    float _dx;
    float _dy;

    Direction _direction;

    b2Body* _body;
};

#endif // ABYSSSENSOR_H
