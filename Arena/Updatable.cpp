#include "Arena/ObjectCounter.h"
#include "Arena/Updatable.h"

Updatable::Updatable()
{
    ObjectCounter<Updatable>::addObject(this);
}

Updatable::~Updatable()
{
    ObjectCounter<Updatable>::removeObject(this);
}
