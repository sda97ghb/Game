#include <iostream>

#include "Arena/Log.h"
#include "Arena/ObjectCounter.h"
#include "Arena/World.h"

#include "Arena/Entity/Animalia.h"
#include "Arena/Entity/Arrow.h"
#include "Arena/Entity/EntityDestroyer.h"

Arrow::Arrow() :
    _damage(10.0f)
{
    ObjectCounter<Arrow>::addObject(this);

    addEventCallback(hitEvent, METHOD_CALLBACK(onHit));
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
            animalia->makeDamage(_damage);
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
