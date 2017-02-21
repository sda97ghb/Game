#include "TestWorldLoader.h"

#include "Game/World.h"

TestWorldLoader::TestWorldLoader()
{
}

void TestWorldLoader::load()
{
    World& world = World::instance();

    {
        Platform& platform = world.createPlatform();
        b2PolygonShape shape;
        b2Vec2 vertexes[4] = {b2Vec2(-20.0, -3.0),
                              b2Vec2( 20.0, -3.0),
                              b2Vec2( 20.0,  0.0),
                              b2Vec2(-20.0,  0.0)};
        shape.Set(vertexes, 4);
        platform.setShape(shape);
        platform.setTexture("C:/Projects/Game/Textures/stonebricks.png");
    }
    {
        Platform& platform = world.createPlatform();
        b2PolygonShape shape;
        b2Vec2 vertexes[4] = {b2Vec2(-7.0, 0.0),
                              b2Vec2(-6.0, 0.0),
                              b2Vec2(-6.0, 4.0),
                              b2Vec2(-7.0, 4.0)};
        shape.Set(vertexes, 4);
        platform.setShape(shape);
        platform.setTexture("C:/Projects/Game/Textures/stonebricks.png");
    }
    {
        Platform& platform = world.createPlatform();
        b2PolygonShape shape;
        b2Vec2 vertexes[4] = {b2Vec2(-13.0, 0.0),
                              b2Vec2(-12.0, 0.0),
                              b2Vec2(-12.0, 4.0),
                              b2Vec2(-13.0, 4.0)};
        shape.Set(vertexes, 4);
        platform.setShape(shape);
        platform.setTexture("C:/Projects/Game/Textures/stonebricks.png");
    }
    {
        Platform& platform = world.createPlatform();
        b2PolygonShape shape;
        b2Vec2 vertexes[4] = {b2Vec2(-19.0, 7.0),
                              b2Vec2( -6.0, 7.0),
                              b2Vec2( -6.0, 7.5),
                              b2Vec2(-19.0, 7.5)};
        shape.Set(vertexes, 4);
        platform.setShape(shape);
        platform.setTexture("C:/Projects/Game/Textures/stonebricks.png");
    }
    {
        Platform& platform = world.createPlatform();
        b2PolygonShape shape;
        b2Vec2 vertexes[4] = {b2Vec2(-5.0, 9.0),
                              b2Vec2(-3.0, 9.0),
                              b2Vec2(-3.0, 9.5),
                              b2Vec2(-5.0, 9.5)};
        shape.Set(vertexes, 4);
        platform.setShape(shape);
        platform.setTexture("C:/Projects/Game/Textures/stonebricks.png");
    }
    {
        Platform& platform = world.createPlatform();
        b2PolygonShape shape;
        b2Vec2 vertexes[4] = {b2Vec2(2.0, 9.0),
                              b2Vec2(5.0, 9.0),
                              b2Vec2(5.0, 9.5),
                              b2Vec2(2.0, 9.5)};
        shape.Set(vertexes, 4);
        platform.setShape(shape);
        platform.setTexture("C:/Projects/Game/Textures/stonebricks.png");
    }
    {
        Platform& platform = world.createPlatform();
        b2PolygonShape shape;
        b2Vec2 vertexes[4] = {b2Vec2(-19.0, 0.0),
                              b2Vec2(-18.0, 0.0),
                              b2Vec2(-18.0, 4.0),
                              b2Vec2(-19.0, 4.0)};
        shape.Set(vertexes, 4);
        platform.setShape(shape);
        platform.setTexture("C:/Projects/Game/Textures/stonebricks.png");
    }

    {
        Ladder& ladder = world.createLadder();
        ladder.setCoordinates(-5.5, 0.0, 7.5);
        ladder.setWidth(1.0);
        ladder.setTexture("C:/Projects/Game/Textures/ladder.png");
    }

//    Enemy enemy1;
//    enemy1.setTexture("");
//    enemy1.setPosition(0.0, 0.0);
//    world.addEnemy(enemy1);
}
