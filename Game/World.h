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

#include "Game/Player.h"

//#include "Game/TestPlayer.h"
//#include "Game/TestArcher.h"

#include "Game/SensorContactListener.h"

class World
{
public:
    static World& instance();

    Player& player();

    Archer& createArcher();
    const std::list<Archer>& archers() const;

    Platform& createPlatform();
    const std::list<Platform>& platforms() const;

    Ladder& createLadder();
    const std::list<Ladder>& ladders() const;

    void update();

private:
    World();
    ~World();

    World(const World&) = delete;
    void operator= (const World&) = delete;

    void createPlayer();

    std::list<Ladder> _ladders;
    std::list<Platform> _platforms;

    std::list<Archer> _archers;

    b2World* _world;

    SensorContactListener _contactListener;
};

#endif // WORLD_H
