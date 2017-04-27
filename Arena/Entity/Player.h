#ifndef PLAYER_H
#define PLAYER_H

#include "Arena/Entity/Animalia.h"

#include "Arena/Sensors/AbyssSensor.h"
#include "Arena/Sensors/ContactSensor.h"
#include "Arena/Sensors/HitSensor.h"

class Player : public Animalia
{
    friend class PlayerBuilderSpawner;
    friend class PlayerView;

public:
    EVENT(groundHit)
    EVENT(landing)

    Player();

    void tryToJump();
    void tryToMoveLeft();
    void tryToMoveRight();

private:
    void onGroundHit(float speed);

    void onLanding();

    float jumpHeight() const;
    float movementSpeed() const;

    enum class State
    {
        normal,
        jumping
    } _state;

    ContactSensor* _leftContactSensor;
    ContactSensor* _rightContactSensor;
    ContactSensor* _groundContactSensor;
    HitSensor* _groundHitSensor;
    HitSensor* _landingSensor;
};

#endif // PLAYER_H
