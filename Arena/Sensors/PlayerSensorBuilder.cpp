#include "Box2D/Dynamics/b2Body.h"

#include "Arena/Sensors/PlayerSensor.h"
#include "Arena/Sensors/PlayerSensorBuilder.h"

PlayerSensorBuilder::PlayerSensorBuilder() :
    _nearbyDistance(10.0f),
    _onGotSightOfPlayerCallback([](){}),
    _onLostSightOfPlayerCallback([](){}),
    _body(nullptr)
{}

PlayerSensorBuilder& PlayerSensorBuilder::setNearbyDistance(float distance)
{
    _nearbyDistance = distance;
    return *this;
}

PlayerSensorBuilder& PlayerSensorBuilder::setOnGotSightOfPlayerCallback(const std::function<void ()>& callback)
{
    _onGotSightOfPlayerCallback = callback;
    return *this;
}

PlayerSensorBuilder& PlayerSensorBuilder::setOnLostSightOfPlayerCallback(const std::function<void ()>& callback)
{
    _onLostSightOfPlayerCallback = callback;
    return *this;
}

PlayerSensorBuilder& PlayerSensorBuilder::setBody(b2Body* body)
{
    _body = body;
    return *this;
}

PlayerSensorBuilder& PlayerSensorBuilder::setNearbyRequired(bool flag)
{
    _isNearbyRequired = flag;
    return *this;
}

PlayerSensorBuilder& PlayerSensorBuilder::setCanSeeRequired(bool flag)
{
    _isCanSeeRequired = flag;
    return *this;
}

PlayerSensor* PlayerSensorBuilder::build()
{
    if (_body == nullptr)
        throw std::logic_error("There is no body provided");

    PlayerSensor* sensor = new PlayerSensor;

    sensor->_nearbyDistance = _nearbyDistance;
    sensor->_canSeeRequired = _isCanSeeRequired;
    sensor->_isNearbyRequired = _isNearbyRequired;
    sensor->_onGotSightOfPlayerCallback = _onGotSightOfPlayerCallback;
    sensor->_onLostSightOfPlayerCallback = _onLostSightOfPlayerCallback;
    sensor->_body = _body;
    sensor->_previousState = false;

    return sensor;
}
