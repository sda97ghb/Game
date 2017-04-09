#include "Box2D/Dynamics/b2Fixture.h"
#include "Box2D/Dynamics/b2World.h"

#include "Arena/World.h"

#include "Arena/Sensors/PlayerSensor.h"

PlayerSensor::PlayerSensor() :
    _nearbyDistance(20.0f),
    _isNearbyRequired(true),
    _canSeeRequired(true),
    _previousState(false),
    _onGotSightOfPlayerCallback([](){}),
    _onLostSightOfPlayerCallback([](){}),
    _body(nullptr)
{
}

void PlayerSensor::hangOnBody(b2Body* body)
{
    _body = body;
}

bool PlayerSensor::canSee()
{
    b2RayCastInput input;
    input.p1 = _body->GetPosition();
    input.p2 = World::instance().player().body()->GetPosition();
    input.maxFraction = 1.0f;
    int32 childIndex = 0;
    b2RayCastOutput output;

    for (b2Body* b = _body->GetWorld()->GetBodyList();
         b != nullptr; b = b->GetNext())
    {
        // Dont test body with itself
        if (b == _body || b == World::instance().player().body())
            continue;

        for (b2Fixture* fixture = b->GetFixtureList();
             fixture != nullptr; fixture = fixture->GetNext())
        {
            if (fixture->RayCast(&output, input, childIndex))
                if (output.fraction < 1.0f)
                    return false;
        }
    }

    return true;
}

bool PlayerSensor::isNearby()
{
    return (World::instance().player().body()->GetPosition() -
            _body->GetPosition()).Length() < _nearbyDistance;
}

bool PlayerSensor::isActive()
{
    if (_canSeeRequired)
        if (!canSee())
            return false;

    if (_isNearbyRequired)
        if (!isNearby())
            return false;

    return true;
}

float PlayerSensor::nearbyDistance() const
{
    return _nearbyDistance;
}

void PlayerSensor::setNearbyDistance(float nearbyDistance)
{
    _nearbyDistance = nearbyDistance;
}

bool PlayerSensor::canSeeRequired() const
{
    return _canSeeRequired;
}

void PlayerSensor::setCanSeeRequired(bool canSeeRequiered)
{
    _canSeeRequired = canSeeRequiered;
}

bool PlayerSensor::isNearbyRequired() const
{
    return _isNearbyRequired;
}

void PlayerSensor::setIsNearbyRequired(bool isNearbyRequired)
{
    _isNearbyRequired = isNearbyRequired;
}

void PlayerSensor::update()
{
    bool isActiveNow = isActive();

    if (_previousState == false && isActiveNow)
        _onGotSightOfPlayerCallback();
    if (_previousState == true && !isActiveNow)
        _onLostSightOfPlayerCallback();

    _previousState = isActiveNow;
}

void PlayerSensor::setOnGotSightOfPlayerCallback(const Callback& onGotSightOfPlayerCallback)
{
    _onGotSightOfPlayerCallback = onGotSightOfPlayerCallback;
}

void PlayerSensor::setOnLostSightOfPlayerCallback(const Callback& onLostSightOfPlayerCallback)
{
    _onLostSightOfPlayerCallback = onLostSightOfPlayerCallback;
}
