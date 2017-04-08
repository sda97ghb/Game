//#include "TestWorldLoader.h"

//#include "Arena/World.h"

//TestWorldLoader::TestWorldLoader()
//{
//}

//// TEST TEXTURE "C:/Projects/Game/Textures/solid.png"

//void TestWorldLoader::load()
//{
//    World& world = World::instance();

//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(-22.0, -6.0),
//                              b2Vec2( 22.0, -6.0),
//                              b2Vec2( 22.0, -5.5),
//                              b2Vec2(-22.0, -5.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(-22.0, 20.0),
//                              b2Vec2( 22.0, 20.0),
//                              b2Vec2( 22.0, 20.5),
//                              b2Vec2(-22.0, 20.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(-22.5, -6.0),
//                              b2Vec2(-22.0, -6.0),
//                              b2Vec2(-22.0, 20.5),
//                              b2Vec2(-22.5, 20.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(22.0, -6.0),
//                              b2Vec2(22.5, -6.0),
//                              b2Vec2(22.5, 20.5),
//                              b2Vec2(22.0, 20.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }

//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(-20.0, -30.0),
//                              b2Vec2( 20.0, -30.0),
//                              b2Vec2( 20.0,  0.0),
//                              b2Vec2(-20.0,  0.0)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(-7.0, 0.0),
//                              b2Vec2(-6.0, 0.0),
//                              b2Vec2(-6.0, 4.0),
//                              b2Vec2(-7.0, 4.0)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(-13.0, 0.0),
//                              b2Vec2(-12.0, 0.0),
//                              b2Vec2(-12.0, 4.0),
//                              b2Vec2(-13.0, 4.0)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(-19.0, 7.0),
//                              b2Vec2( -6.0, 7.0),
//                              b2Vec2( -6.0, 7.5),
//                              b2Vec2(-19.0, 7.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(-5.0, 9.0),
//                              b2Vec2(-3.0, 9.0),
//                              b2Vec2(-3.0, 9.5),
//                              b2Vec2(-5.0, 9.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(2.0, 9.0),
//                              b2Vec2(5.0, 9.0),
//                              b2Vec2(5.0, 9.5),
//                              b2Vec2(2.0, 9.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(9.0, 9.0),
//                              b2Vec2(10.0, 9.0),
//                              b2Vec2(10.0, 9.5),
//                              b2Vec2(9.0, 9.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(15.0, 9.0),
//                              b2Vec2(20.0, 9.0),
//                              b2Vec2(20.0, 9.5),
//                              b2Vec2(15.0, 9.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(-19.0, 0.0),
//                              b2Vec2(-18.0, 0.0),
//                              b2Vec2(-18.0, 4.0),
//                              b2Vec2(-19.0, 4.0)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }
//    {
//        Platform& platform = world.createPlatform();
//        b2PolygonShape shape;
//        b2Vec2 vertexes[4] = {b2Vec2(2.0, 17.0),
//                              b2Vec2(5.0, 17.0),
//                              b2Vec2(5.0, 17.5),
//                              b2Vec2(2.0, 17.5)};
//        shape.Set(vertexes, 4);
//        platform.setShape(shape);
//        platform.setTexture("Textures/stonebricks.png");
//    }

//    {
//        Ladder& ladder = world.createLadder();
//        ladder.setCoordinates(-5.5f, 0.0f, 9.5f);
//        ladder.setWidth(1.0f);
//        ladder.setTexture("Textures/ladder.png");
//    }
//    {
//        Ladder& ladder = world.createLadder();
//        ladder.setCoordinates(5.5f, 0.0f, 20.0f);
//        ladder.setWidth(1.0f);
//        ladder.setTexture("Textures/ladder.png");
//    }
//    {
//        Ladder& ladder = world.createLadder();
//        ladder.setCoordinates(-7.5f, 0.0f, 5.0f);
//        ladder.setWidth(1.0f);
//        ladder.setTexture("Textures/ladder.png");
//    }
//    {
//        Ladder& ladder = world.createLadder();
//        ladder.setCoordinates(-11.5f, 0.0f, 5.0f);
//        ladder.setWidth(1.0f);
//        ladder.setTexture("Textures/ladder.png");
//    }

//    {
//        Water& water = world.createWater();
//        b2Vec2 vertexes[4] = {b2Vec2(-12.0, 0.0),
//                              b2Vec2( -7.0, 0.0),
//                              b2Vec2( -7.0, 3.8),
//                              b2Vec2(-12.0, 3.8)};
//        b2PolygonShape shape;
//        shape.Set(vertexes, 4);
//        water.setShape(shape);
//        water.setTextureBack("Textures/stoneBricks.png");
//        water.setTexture("Textures/water.png");
//    }
//    {
//        Lava& lava = world.createLava();
//        b2Vec2 vertexes[4] = {b2Vec2(-18.0, 0.0),
//                              b2Vec2(-13.0, 0.0),
//                              b2Vec2(-13.0, 3.8),
//                              b2Vec2(-18.0, 3.8)};
//        b2PolygonShape shape;
//        shape.Set(vertexes, 4);
//        lava.setShape(shape);
//        lava.setTextureBack("Textures/stoneBricks.png");
//        lava.setTexture("Textures/lava.png");
//    }

//    {
//        Player& player = world.player();
//        player.setPosition(0.0f, player.height() / 2.0f);
//        SpriteAnimator& animator = player.spriteAnimator();
//        animator.setTexture("Textures/playerFrames.png");
//        animator.setAnimationGroup("going_left", 0, 0, 12, 28, 4, Orientation::vertical);
//        animator.setAnimationGroup("going_right", 12, 0, 12, 28, 4, Orientation::vertical);
//        animator.setAnimationGroup("climbing", 24, 0, 12, 28, 2, Orientation::vertical);
//        animator.setAnimationGroup("punching_right", 36, 0, 18, 28, 3, Orientation::horizontal);
//        animator.setAnimationGroup("punching_left", 36, 28, 18, 28, 3, Orientation::horizontal);
//        animator.setAnimationGroup("dead", 52, 56, 28, 28);
//        animator.setCurrentGroup("going_right");
//        animator.nextFrame();
//    }

//    {
//        Archer& archer = world.createArcher();
//        archer.setPosition(3.0f, 10.0f);
//        SpriteAnimator& animator = archer.spriteAnimator();
//        animator.setTexture("Textures/archerFrames.png");
//        animator.setAnimationGroup("going_left", 0, 0, 12, 28, 1, Orientation::horizontal);
//        animator.setAnimationGroup("going_right", 0, 28, 12, 28, 1, Orientation::horizontal);
//        animator.setAnimationGroup("climbing", 12, 0, 12, 28, 2, Orientation::vertical);
//        animator.setAnimationGroup("firing_left", 24, 0, 18, 28, 5, Orientation::horizontal);
//        animator.setAnimationGroup("firing_right", 24, 28, 18, 28, 5, Orientation::horizontal);
//        animator.setAnimationGroup("dead", 0, 0, 12, 28);
//        animator.setCurrentGroup("going_left");
//        animator.nextFrame();
//    }
//}
