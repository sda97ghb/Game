#ifndef PLAYERSENSORBUILDER_H
#define PLAYERSENSORBUILDER_H

#include <functional>

class b2Body;

class PlayerSensor;

class PlayerSensorBuilder
{
public:
    PlayerSensorBuilder();

    PlayerSensorBuilder& setNearbyDistance(float distance);
    PlayerSensorBuilder& setOnGotSightOfPlayerCallback(
            const std::function<void()>& callback);
    PlayerSensorBuilder& setOnLostSightOfPlayerCallback(
            const std::function<void()>& callback);
    PlayerSensorBuilder& setBody(b2Body* body);
    PlayerSensorBuilder& setNearbyRequired(bool flag);
    PlayerSensorBuilder& setCanSeeRequired(bool flag);

    PlayerSensor* build();

private:
    bool _isNearbyRequired;
    bool _isCanSeeRequired;

    float _nearbyDistance;

    std::function<void()> _onGotSightOfPlayerCallback;
    std::function<void()> _onLostSightOfPlayerCallback;

    b2Body* _body;
};

#endif // PLAYERSENSORBUILDER_H
