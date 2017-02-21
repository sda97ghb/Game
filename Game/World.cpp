#include "Game/World.h"

World::World()
{
    b2Vec2 gravity(0.0, -9.8);
    _world = new b2World(gravity);
}

World::~World()
{
    delete _world;
}

World& World::instance()
{
    static World instance;
    return instance;
}

const std::list<Ladder>& World::ladders() const
{
    return _ladders;
}

const std::list<Platform>&World::platforms() const
{
    return _platforms;
}

Ladder&World::createLadder()
{
    _ladders.emplace_back();
    Ladder& ladder = _ladders.back();

    return ladder;
}

Platform& World::createPlatform()
{
    _platforms.emplace_back();
    Platform& platform = _platforms.back();

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(0.0, 0.0);
    platform.setBody(_world->CreateBody(&bodyDef));

    return platform;
}
