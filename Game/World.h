#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "Game/Ladder.h"

class World
{
public:
    static World& instance();

    void addLadder(Ladder&& ladder);

private:
    World();
    World(const World&) = delete;
    void operator= (const World&) = delete;

    std::list<Ladder> _ladders;
};

#endif // WORLD_H
