#ifndef PLAYER_H
#define PLAYER_H

#include "Arena/Entity/Animalia.h"
#include "Arena/Entity/ComplexStateMachine.h"

#include "Arena/Sensors/AbyssSensor.h"
#include "Arena/Sensors/ContactSensor.h"
#include "Arena/Sensors/HitSensor.h"

class Player : public Animalia, public ComplexStateMachine
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

    STATE(jumping)

    ContactSensor* _leftContactSensor;
    ContactSensor* _rightContactSensor;
    ContactSensor* _groundContactSensor;
    HitSensor* _groundHitSensor;
    HitSensor* _landingSensor;
};

#endif // PLAYER_H
