#ifndef ARROW_H
#define ARROW_H

#include "Arena/Entity/Entity.h"

#include "Arena/Sensors/EnityCollisionSensor.h"
#include "Arena/Sensors/HitSensor.h"
#include "Arena/Sensors/TimerSensor.h"

class Arrow : public Entity
{
    friend class ArrowBuilderSpawner;
    friend class ArrowView;

public:
    EVENT(hit)

    Arrow();
    ~Arrow();

    void onHit();

    void hitEntity(Entity* entity);

private:
    void disappear();

    EnityCollisionSensor _entityCollisionSensor;
    HitSensor _hitSensor;
};

#endif // ARROW_H
