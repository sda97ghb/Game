#ifndef ARCHER_H
#define ARCHER_H

#include "Arena/Entity/Animalia.h"

#include "Arena/Sensors/AbyssSensor.h"
#include "Arena/Sensors/ContactSensor.h"
#include "Arena/Sensors/HitSensor.h"
#include "Arena/Sensors/PlayerSensor.h"
#include "Arena/Sensors/TimerSensor.h"

class Archer : public Animalia
{
    friend class ArcherBuilderSpawner;
    friend class ArcherView;

public:
    EVENT(groundHit)
    EVENT(landing)
    EVENT(readyToStrike)
    EVENT(strike)
    EVENT(gotSightOfPlayer)
    EVENT(lostSightOfPlayer)
    EVENT(wentButNotFound)

    Archer();

private:
    void tryToJump();
    void tryToMoveLeft();
    void tryToMoveRight();

    void onUpdate();

    void strike();

    void onGroundHit(float speed);

    void onLanding();

    void onGotSightOfPlayer();
    void onLostSightOfPlayer();

    void prepareToStrike();

    void onWentButNotFound();

    float jumpHeight() const;
    float movementSpeed() const;

    enum class State
    {
        jumping,
        lookingAround,
        preparingToStrike,
        goingToLastKnownPlayerLocation
    } _state;

    AbyssSensor _abyssSensor;
    ContactSensor _leftContactSensor;
    ContactSensor _rightContactSensor;
    ContactSensor _groundContactSensor;
    HitSensor _groundHitSensor;
    HitSensor _landingSensor;
    PlayerSensor _playerSensor;
    TimerSensor _reloadSensor;

    b2Vec2 _lastKnownPlayerLocation;
};

#endif // ARCHER_H
