#ifndef ARCHER_H
#define ARCHER_H

#include "Arena/Entity/Animalia.h"
#include "Arena/Entity/ComplexStateMachine.h"

#include "Arena/Sensors/AbyssSensor.h"
#include "Arena/Sensors/ContactSensor.h"
#include "Arena/Sensors/HitSensor.h"
#include "Arena/Sensors/PlayerSensor.h"
#include "Arena/Sensors/TimerSensor.h"

class Archer : public Animalia, public ComplexStateMachine
{
    friend class ArcherBuilderSpawner;
    friend class ArcherView;

public:
    EVENT(bump)
    EVENT(gotSightOfPlayer)
    EVENT(groundHit)
    EVENT(landing)
    EVENT(lostSightOfPlayer)
    EVENT(readyToStrike)
    EVENT(strike)
    EVENT(wentButNotFound)

    Archer();

private:
    STATE(chasing) // required() incompatible(lookingAround, preparingToStrike)
    STATE(jumping) // required() incompatible(preparingToStrike)
    STATE(lookingAround) // required() incompatible(chasing, preparingToStrike)
    STATE(preparingToStrike) // required() incompatible(chaising, jumping, lookingAround)

    void tryToJump();
    void tryToMoveLeft();
    void tryToMoveRight();

    void onBump();
    void onGroundHit(float speed);
    void onLanding();

    void onGotSightOfPlayer();
    void onLostSightOfPlayer();

    void onUpdate();

    void onWentButNotFound();

    void prepareToStrike();
    void preparingToStrike();
    void strike();

    void chasing();

    float jumpHeight() const;
    float movementSpeed() const;

    void lookingAround();

    AbyssSensor _abyssSensor;
    ContactSensor _leftContactSensor;
    ContactSensor _rightContactSensor;
    ContactSensor _groundContactSensor;
    HitSensor _groundHitSensor;
    HitSensor _landingSensor;
    HitSensor _leftBumpSensor;
    HitSensor _rightBumpSensor;
    PlayerSensor _playerSensor;
    TimerSensor _reloadSensor;

    b2Vec2 _lastKnownPlayerLocation;
};

#endif // ARCHER_H
