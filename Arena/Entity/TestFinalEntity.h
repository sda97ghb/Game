#ifndef TESTFINALENTITY_H
#define TESTFINALENTITY_H

#include "Arena/Entity/Animalia.h"

#include "Arena/Sensors/AbyssSensor.h"
#include "Arena/Sensors/ContactSensor.h"
#include "Arena/Sensors/HitSensor.h"
#include "Arena/Sensors/PlayerSensor.h"

class TestFinalEntity : public Animalia
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

    AbyssSensor* _abyssSensor;
    ContactSensor* _leftContactSensor;
    ContactSensor* _rightContactSensor;
    ContactSensor* _groundContactSensor;
    HitSensor* _groundHitSensor;
    PlayerSensor* _playerSensor;
    PlayerSensor* _nearEnoughToAttackSensor;
};

#endif // TESTFINALENTITY_H
