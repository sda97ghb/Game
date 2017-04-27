#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"

#include "Arena/Sensors/AbyssSensor.h"

bool AbyssSensor::isActive()
{
    float dxSign = 1.0f;
    if (_direction == Direction::left)
        dxSign = -1.0f;

    b2RayCastInput input;
    input.p1 = _body->GetPosition();
    input.p2 = input.p1 + b2Vec2(dxSign * _dx, _dy);
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

Direction AbyssSensor::direction() const
{
    return _direction;
}

void AbyssSensor::setDirection(const Direction& direction)
{
    _direction = direction;
}
