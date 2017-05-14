#include "Arena/Attacks/Attack.h"

Attack::Attack() :
    _actor {nullptr}
{
}

void Attack::setActor(Animalia* actor)
{
    _actor = actor;
}
