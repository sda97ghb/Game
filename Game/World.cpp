#include "Game/SensorsListener.h"
#include "Game/World.h"

World::World()
{
    b2Vec2 gravity(0.0f, -9.8f);
    _world = new b2World(gravity);

    createPlayer();

    _world->SetContactListener(&SensorsListener::instance());
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

Platform& World::createPlatform()
{
    _platforms.emplace_back();
    Platform& platform = _platforms.back();

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(0.0, 0.0);
    platform.setBody(_world->CreateBody(&bodyDef));

    return platform;
}

Ladder& World::createLadder()
{
    _ladders.emplace_back();
    Ladder& ladder = _ladders.back();

    return ladder;
}

Water& World::createWater()
{
    _waters.emplace_back();
    Water& water = _waters.back();
    return water;
}

Lava& World::createLava()
{
    _lavas.emplace_back();
    Lava& lava = _lavas.back();
    return lava;
}

b2Body* World::createBodyForEntity()
{
    b2BodyDef entityBodyDef;
    entityBodyDef.type = b2_dynamicBody;
    entityBodyDef.fixedRotation = true;
    entityBodyDef.position.Set(0.0f, 0.0f);

    return _world->CreateBody(&entityBodyDef);
}

void World::createPlayer()
{
    player().setBody(createBodyForEntity());
    player().constructBody();
}

Archer& World::createArcher()
{
    _archers.emplace_back();
    Archer& archer = _archers.back();

    archer.setBody(createBodyForEntity());
    archer.constructBody();

    return archer;
}

Player& World::player()
{
    return Player::instance();
}

const std::list<Platform>& World::platforms() const
{
    return _platforms;
}

const std::list<Ladder>& World::ladders() const
{
    return _ladders;
}

const std::list<Water>&World::waters() const
{
    return _waters;
}

const std::list<Lava>& World::lavas() const
{
    return _lavas;
}

const std::list<Archer>& World::archers() const
{
    return _archers;
}

void World::update()
{
    for (Ladder& ladder : _ladders)
        ladder.testPlayerOnIt();

    for (Water& water : _waters)
        water.testPlayerOnIt();

    for (Lava& lava : _lavas)
        lava.testPlayerOnIt();

    for (Archer& archer : _archers)
        archer.update();

    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

    _world->Step(timeStep, velocityIterations, positionIterations);
}
