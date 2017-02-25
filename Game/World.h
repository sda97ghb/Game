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
#include "Game/Player.h"
#include "Game/Rope.h"
#include "Game/Spikes.h"
#include "Game/Swordman.h"
#include "Game/Water.h"

class World
{
public:
    ~World();
    static World& instance();

    Platform& createPlatform();

    Ladder& createLadder();

    Archer& createArcher();

    Player& player();

    const std::list<Platform>& platforms() const;

    const std::list<Ladder>& ladders() const;

    const std::list<Archer>& archers() const;

    void update();

private:
    World();

    World(const World&) = delete;
    void operator= (const World&) = delete;

    b2Body* createBodyForEntity();

    void createPlayer();

    std::list<Ladder> _ladders;
    std::list<Platform> _platforms;

    std::list<Archer> _archers;

    b2World* _world;
};

#endif // WORLD_H
