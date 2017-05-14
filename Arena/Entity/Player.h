#ifndef PLAYER_H
#define PLAYER_H

#include "Arena/Attacks/Attack.h"

#include "Arena/Entity/Animalia.h"
#include "Arena/Entity/ComplexStateMachine.h"

#include "Arena/Sensors/AbyssSensor.h"
#include "Arena/Sensors/ContactSensor.h"
#include "Arena/Sensors/HitSensor.h"
#include "Arena/Sensors/TimerSensor.h"

class Player : public Animalia, public ComplexStateMachine
{
    friend class PlayerBuilderSpawner;
    friend class PlayerView;

public:
    EVENT(groundHit)
    EVENT(landing)
    EVENT(readyForAttack)

    Player();
    ~Player();

    void tryToJump();
    void tryToMoveLeft();
    void tryToMoveRight();
    void tryToAttack(Attack* attack, float delay, bool attackImmediatly = false);

    bool isPreparingForAttack() const;

private:
    void onGroundHit(float speed);

    void onLanding();

    float jumpHeight() const;
    float movementSpeed() const;

    void performAttack();

    STATE(jumping)
    STATE(preparingForAttack)

    ContactSensor* _leftContactSensor;
    ContactSensor* _rightContactSensor;
    ContactSensor* _groundContactSensor;
    HitSensor* _groundHitSensor;
    HitSensor* _landingSensor;
    TimerSensor* _attackReloadSensor;

    Attack* _attack;
};

#endif // PLAYER_H
