#ifndef TESTFINALENTITY_H
#define TESTFINALENTITY_H

#include "Arena/Direction.h"

#include "Arena/Entity/LivingEntity.h"

#include "Arena/Sensors/AbyssSensor.h"
#include "Arena/Sensors/ContactSensor.h"
#include "Arena/Sensors/HitSensor.h"
#include "Arena/Sensors/PlayerSensor.h"

class TestFinalEntity : public LivingEntity
{
    friend class TestFinalEntityBuilderSpawner;

public:
    EVENT(groundHit)

    TestFinalEntity();

private:
    void onSpawn();
    void onDeath();
    void onLivingUpdate();
    void onGroundHit(float speed);

    AbyssSensor _abyssSensor;
    ContactSensor _leftContactSensor;
    ContactSensor _rightContactSensor;
    ContactSensor _groundContactSensor;
    HitSensor _groundHitSensor;
    PlayerSensor _playerSensor;
    PlayerSensor _nearEnoughToAttackSensor;

    Direction _lookingDirection;
};

#endif // TESTFINALENTITY_H
