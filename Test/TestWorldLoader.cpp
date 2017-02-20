#include "TestWorldLoader.h"

#include "Game/World.h"

TestWorldLoader::TestWorldLoader()
{
}

void TestWorldLoader::load()
{
    World& world = World::instance();

    Ladder ladder;
    ladder.setCoordinates(0.0, -3.0, 27.0);
    ladder.setWidth(1.0);
    ladder.setTexture("C:/Projects/Game/Textures/ladder.png");
    world.addLadder(std::move(ladder));

    Enemy enemy1;
//    enemy1.setTexture("");
//    enemy.setPosition();
//    world.addEnemy(enemy1);
}
