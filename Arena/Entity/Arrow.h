#ifndef ARROW_H
#define ARROW_H

#include "Arena/Entity/Entity.h"

#include "Arena/Sensors/EnityCollisionSensor.h"
#include "Arena/Sensors/PlayerSensor.h"

class Arrow : public Entity
{
    friend class ArrowBuilderSpawner;
    friend class ArrowView;

public:
    EVENT(hit)

    Arrow();
    ~Arrow();

    void onHit();

    void hitEntity(Entity*entity);

private:
    EnityCollisionSensor _entityCollisionSensor;
//    PlayerSensor _playerSensor;

    bool _isDead;
};

#endif // ARROW_H
