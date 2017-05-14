#include "Arena/MapUnloader.h"
#include "Arena/ObjectCounter.h"
#include "Arena/World.h"

#include "Arena/Entity/Entity.h"
#include "Arena/Entity/EntityDestroyer.h"

void MapUnloader::unload()
{
    for (Entity* entity : ObjectCounter<Entity>::objects())
        new EntityDestroyer(entity);

    auto destroyers = ObjectCounter<EntityDestroyer>::objects();
    for (auto destroyer : destroyers)
    {
        destroyer->destroy();
        delete destroyer;
    }
}
