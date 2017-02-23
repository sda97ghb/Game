#include "Game/World.h"

#include "Box2D/Dynamics/b2Fixture.h"

World::World()
{
    b2Vec2 gravity(0.0, -9.8);
    _world = new b2World(gravity);

    createPlayer();

    _world->SetContactListener(&_contactListener);
}

World::~World()
{
    delete _world;
}

void World::createPlayer()
{
    b2BodyDef entityBodyDef;
    entityBodyDef.type = b2_dynamicBody;
    entityBodyDef.fixedRotation = true;
    entityBodyDef.position.Set(0.0, 0.0);
    player().setBody(_world->CreateBody(&entityBodyDef));
    {
        b2PolygonShape playerShape;
        playerShape.SetAsBox(0.75f / 2.0f, 1.75f / 2.0f);
        b2FixtureDef playerFixtureDef;
        playerFixtureDef.shape = &playerShape;
        playerFixtureDef.density = 1.0f;
        playerFixtureDef.friction = 20.0f;
        playerFixtureDef.restitution = 0.0f;
        player().body().CreateFixture(&playerFixtureDef);
    }
    {
        b2PolygonShape sensorShape;
        sensorShape.SetAsBox(0.3f, 0.3f, b2Vec2(0.0f, -1.75f / 2.0f), 0.0f);
        b2FixtureDef sensorFixtureDef;
        sensorFixtureDef.shape = &sensorShape;
        sensorFixtureDef.isSensor = true;
        b2Fixture* fixture = player().body().CreateFixture(&sensorFixtureDef);
        fixture->SetUserData((void*)SensorContactListener::GROUND_SENSOR_TYPE);
    }
}

World& World::instance()
{
    static World instance;
    return instance;
}

TestPlayer& World::player()
{
    return TestPlayer::instance();
}

TestArcher& World::createArcher()
{
    _archers.emplace_back();
    TestArcher& archer = _archers.back();

    b2BodyDef archerBodyDef;
    archerBodyDef.type = b2_dynamicBody;
    archerBodyDef.fixedRotation = true;
    archerBodyDef.position.Set(0.0, 0.0);
    archer.setBody(_world->CreateBody(&archerBodyDef));
    {
        b2PolygonShape archerShape;
        archerShape.SetAsBox(0.75f / 2.0f, 1.75f / 2.0f);
        b2FixtureDef archerFixtureDef;
        archerFixtureDef.shape = &archerShape;
        archerFixtureDef.density = 1.0f;
        archerFixtureDef.friction = 20.0f;
        archerFixtureDef.restitution = 0.0f;
        archer.body().CreateFixture(&archerFixtureDef);
    }
    {
        b2PolygonShape sensorShape;
        sensorShape.SetAsBox(0.3f, 0.3f, b2Vec2(0.0f, -1.75f / 2.0f), 0.0f);
        b2FixtureDef sensorFixtureDef;
        sensorFixtureDef.shape = &sensorShape;
        sensorFixtureDef.isSensor = true;
        b2Fixture* fixture = archer.body().CreateFixture(&sensorFixtureDef);
        fixture->SetUserData((void*)SensorContactListener::GROUND_SENSOR_TYPE);
    }

    return archer;
}

const std::list<TestArcher>& World::archers() const
{
    return _archers;
}

const std::list<Ladder>& World::ladders() const
{
    return _ladders;
}

void World::update()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 6;
    int32 positionIterations = 2;

    _world->Step(timeStep, velocityIterations, positionIterations);
}

const std::list<Platform>& World::platforms() const
{
    return _platforms;
}

Ladder& World::createLadder()
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
