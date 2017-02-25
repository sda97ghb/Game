#include "Game/World.h"

#include "Box2D/Dynamics/b2Fixture.h"

World::World()
{
    b2Vec2 gravity(0.0f, -9.8f);
    _world = new b2World(gravity);

    createPlayer();

    _world->SetContactListener(&_contactListener);
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

void World::constructEntity(Entity& entity) const
{
    const float width = entity.width();
    const float height = entity.height();
    {
        b2PolygonShape entityShape;
        entityShape.SetAsBox(width / 2.0f, height / 2.0f);
        b2FixtureDef entityFixtureDef;
        entityFixtureDef.shape = &entityShape;
        entityFixtureDef.density = 1.0f;
        entityFixtureDef.friction = 20.0f;
        entityFixtureDef.restitution = 0.0f;
        entity.body().CreateFixture(&entityFixtureDef);
    }
    {
        b2PolygonShape sensorShape;
        sensorShape.SetAsBox(width / 2.0f * 0.9, 0.1,
                             b2Vec2(0.0f, -height / 2.0f), 0.0f);
        b2FixtureDef sensorFixtureDef;
        sensorFixtureDef.shape = &sensorShape;
        sensorFixtureDef.isSensor = true;
        b2Fixture* fixture = entity.body().CreateFixture(&sensorFixtureDef);
        fixture->SetUserData((void*)SensorContactListener::GROUND_SENSOR_TYPE);
    }
    {
        b2PolygonShape sensorShape;
        sensorShape.SetAsBox(0.1f, height / 2.0 * 0.9,
                             b2Vec2(-width / 2.0f, 0.0), 0.0f);
        b2FixtureDef sensorFixtureDef;
        sensorFixtureDef.shape = &sensorShape;
        sensorFixtureDef.isSensor = true;
        b2Fixture* fixture = entity.body().CreateFixture(&sensorFixtureDef);
        fixture->SetUserData((void*)SensorContactListener::LEFT_SENSOR_TYPE);
    }
    {
        b2PolygonShape sensorShape;
        sensorShape.SetAsBox(0.1f, height / 2.0 * 0.9,
                             b2Vec2(width / 2.0f, 0.0), 0.0f);
        b2FixtureDef sensorFixtureDef;
        sensorFixtureDef.shape = &sensorShape;
        sensorFixtureDef.isSensor = true;
        b2Fixture* fixture = entity.body().CreateFixture(&sensorFixtureDef);
        fixture->SetUserData((void*)SensorContactListener::RIGHT_SENSOR_TYPE);
    }
}

void World::createPlayer()
{
    b2BodyDef entityBodyDef;
    entityBodyDef.type = b2_dynamicBody;
    entityBodyDef.fixedRotation = true;
    entityBodyDef.position.Set(0.0f, 0.0f);
    player().setBody(_world->CreateBody(&entityBodyDef));

    constructEntity(player());
}

Archer& World::createArcher()
{
    _archers.emplace_back();
    Archer& archer = _archers.back();

    b2BodyDef archerBodyDef;
    archerBodyDef.type = b2_dynamicBody;
    archerBodyDef.fixedRotation = true;
    archerBodyDef.position.Set(0.0f, 0.0f);
    archer.setBody(_world->CreateBody(&archerBodyDef));
    constructEntity(archer);

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

const std::list<Archer>& World::archers() const
{
    return _archers;
}

void World::update()
{
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 8;
    int32 positionIterations = 3;

    _world->Step(timeStep, velocityIterations, positionIterations);

    for (Ladder& ladder : _ladders)
        ladder.testPlayerOnIt();
}
