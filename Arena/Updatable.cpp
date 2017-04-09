#include "Arena/Updatable.h"
#include "Arena/World.h"

Updatable::Updatable()
{
    World::instance().addUpdatable(this);
}
