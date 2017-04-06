#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"

#include "Arena/Sensors/AbyssSensor.h"

AbyssSensor::AbyssSensor() :
    _dx(1.0f),
    _dy(-2.0f)
{
}

void AbyssSensor::hangOnBody(b2Body* body)
{
    _body = body;
}

bool AbyssSensor::isActive()
{
    float dx = _dx;
    if (_direction == Direction::left)
        dx = -1.0;
    else if (_direction == Direction::right)
        dx = 1.0f;

    b2RayCastInput input;
    input.p1 = _body->GetPosition();
    input.p2 = input.p1 + b2Vec2(dx, _dy);
    input.maxFraction = 1.0f;
    int32 childIndex = 0;
    b2RayCastOutput output;

    for (b2Body* b = _body->GetWorld()->GetBodyList();
         b != nullptr; b = b->GetNext())
    {
        if (b == _body)
            continue;

        for (b2Fixture* fixture = b->GetFixtureList();
             fixture != nullptr; fixture = fixture->GetNext())
        {
            if (fixture->RayCast(&output, input, childIndex))
                return false;
        }
    }

    return true;
}

float AbyssSensor::dx() const
{
    return _dx;
}

void AbyssSensor::setDx(float dx)
{
    _dx = dx;
}

float AbyssSensor::dy() const
{
    return _dy;
}

void AbyssSensor::setDy(float dy)
{
    _dy = dy;
}

Direction AbyssSensor::direction() const
{
    return _direction;
}

void AbyssSensor::setDirection(const Direction& direction)
{
    _direction = direction;
}
