#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "Box2D/Dynamics/b2World.h"

#include "Game/Archer.h"
#include "Game/Cable.h"
#include "Game/FallingGround.h"
#include "Game/Ladder.h"
#include "Game/Lava.h"
#include "Game/Mage.h"
#include "Game/Platform.h"
#include "Game/Rope.h"
#include "Game/Spikes.h"
#include "Game/Swordman.h"
#include "Game/Water.h"

class World
{
public:
    static World& instance();

    Platform& createPlatform();
    const std::list<Platform>& platforms() const;

    Ladder& createLadder();
    const std::list<Ladder>& ladders() const;

private:
    World();
    ~World();

    World(const World&) = delete;
    void operator= (const World&) = delete;

    std::list<Ladder> _ladders;
    std::list<Platform> _platforms;

    b2World* _world;
};

#endif // WORLD_H
