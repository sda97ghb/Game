#include <iostream>

#include "Arena/Log.h"
#include "Arena/ObjectCounter.h"
#include "Arena/World.h"

#include "Arena/Entity/Animalia.h"
#include "Arena/Entity/Arrow.h"
#include "Arena/Entity/EntityDestroyer.h"

Arrow::Arrow()
{
    ObjectCounter<Arrow>::addObject(this);

    setEventCallback(hitEvent, METHOD_CALLBACK(onHit));
}

Arrow::~Arrow()
{
    ObjectCounter<Arrow>::removeObject(this);
}

void Arrow::onHit()
{
//    return_if_deleted

    std::cout << "Arrow hit!" << std::endl;

    disappear();
}

void Arrow::hitEntity(Entity* entity)
{
//    return_if_deleted

    std::cout << "Hit entity!" << std::endl;

    for (Animalia* animalia : ObjectCounter<Animalia>::objects())
    {
        if (entity == animalia)
        {
            animalia->makeDamage(10.0f);
            break;
        }
    }
}

void Arrow::disappear()
{
    return_if_deleted
    new EntityDestroyer(this);
//    markAsDeleted();
}
