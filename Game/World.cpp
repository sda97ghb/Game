#include "Game/World.h"

World::World()
{
    ;
}

World& World::instance()
{
    static World instance;
    return instance;
}

void World::addLadder(Ladder&& ladder)
{
    _ladders.push_back(std::move(ladder));
}

const std::list<Ladder>& World::ladders() const
{
    return _ladders;
}
