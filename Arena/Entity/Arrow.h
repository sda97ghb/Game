#ifndef ARROW_H
#define ARROW_H

#include "Arena/Entity/Entity.h"

#include "Arena/Sensors/HitSensor.h"
#include "Arena/Sensors/PlayerSensor.h"

class Arrow : public Entity
{
    friend class ArrowBuilderSpawner;
    friend class ArrowView;

public:
    EVENT(hit)

    Arrow();

    void onHit();

private:
//    HitSensor _hitSensor;
//    PlayerSensor _playerSensor;
};

#endif // ARROW_H
