#include "Arena/Log.h"
#include "Arena/ObjectCounter.h"
#include "Arena/World.h"

#include "Arena/Entity/Animalia.h"
#include "Arena/Entity/Arrow.h"
#include "Arena/Entity/EntityDestroyer.h"

Arrow::Arrow() :
    _isDead(false)
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
    if (_isDead)
        return;

    Log::instance().addMessage("Arrow hit!");
//    _disappearSensor.start();
    new EntityDestroyer(this);

    _isDead = true;
}

void Arrow::hitEntity(Entity* entity)
{
//    if (_isDead)
//        return;

//    for (Animalia* animalia : ObjectCounter<Animalia>::objects())
//    {
//        if (entity == animalia)
//        {
//            animalia->kill();
//            _isDead = true;
//            break;
//        }
            //    }
}

void Arrow::disappear()
{
//    new EntityDestroyer(this);
}
