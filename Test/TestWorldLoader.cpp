#include "TestWorldLoader.h"

#include "Game/World.h"

TestWorldLoader::TestWorldLoader()
{
}

void TestWorldLoader::load()
{
    Ladder ladder;
    ladder.setCoordinates(0.0, -10.0, 7.0);
    ladder.setWidth(0.45);
    ladder.setTexture("C:/Projects/Game/Textures/ladder2.png");

    World& world = World::instance();
    world.addLadder(std::move(ladder));
}
