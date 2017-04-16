#include "Arena/Log.h"
#include "Arena/ObjectCounter.h"
#include "Arena/World.h"

#include "Arena/Entity/Arrow.h"
#include "Arena/Entity/Archer.h"

Arrow::Arrow() :
    _isDead(false)
{
    ObjectCounter<Arrow>::addObject(this);
}

Arrow::~Arrow()
{
    ObjectCounter<Arrow>::removeObject(this);
}

void Arrow::hitEntity(Entity* entity)
{
    if (_isDead)
        return;

    for (Animalia* animalia : ObjectCounter<Animalia>::objects())
    {
        if (entity == animalia)
        {
            animalia->kill();
            World::instance().removeEntity(this);
            _isDead = true;
            break;
        }
    }
}
