#include "Arena/GlobalConstants.h"
#include "Arena/PaintingWindow.h"
#include "Arena/SensorListener.h"
#include "Arena/World.h"

World::World() :
    _player(nullptr)
{
    (void)World::physical();
    World::physical().SetContactListener(&SensorListener::instance());

//    createPlayer();
}

b2World& World::physical()
{
    static b2World worldInstance(GRAVITY_VECTOR);
    return worldInstance;
}

World& World::instance()
{
    static World instance;
    return instance;
}

World::~World()
{
    for (Entity* entity : _entities)
        if (entity != nullptr)
            delete entity;
}

void World::addUpdatable(Updatable* updatable)
{
    _updatebles.push_back(updatable);
}

void World::addEntity(Entity* entity)
{
    _entities.push_back(entity);
}

void World::removeEntity(Entity* entity)
{
    _entitiesToRemove.push_back(entity);
}

Platform& World::createPlatform()
{
    _platforms.emplace_back();
    Platform& platform = _platforms.back();

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(0.0, 0.0);
    platform.setBody(World::physical().CreateBody(&bodyDef));

    return platform;
}

Cable& World::createCable()
{
    _cables.emplace_back();
    Cable& cable = _cables.back();
    return cable;
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

Spikes& World::createSpikes()
{
	_spikes.emplace_back();
	Spikes& _spikes_ = _spikes.back();

	return _spikes_;
}

const std::list<Platform>& World::platforms() const
{
    return _platforms;
}

const std::list<Cable>& World::cable() const
{
    return _cables;
}

const std::list<Ladder>& World::ladders() const
{
    return _ladders;
}

const std::list<Water>& World::waters() const
{
    return _waters;
}

const std::list<Lava>& World::lavas() const
{
    return _lavas;
}

const std::list<Spikes>& World::spikes() const
{
	return _spikes;
}

void World::update()
{
    for (auto& updatable : _updatebles)
        updatable->update();

    for (auto& entity : _entities)
        entity->update();

    for (Ladder& ladder : _ladders)
        ladder.testPlayerOnIt();

	for (Spikes& spikes : _spikes)
		spikes.testPlayerOnIt();

    for (Water& water : _waters)
        water.testPlayerOnIt();

    for (Lava& lava : _lavas)
        lava.testPlayerOnIt();

    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

    World::physical().Step(timeStep, velocityIterations, positionIterations);

    for (Entity* entity : _entitiesToRemove)
    {
        _entities.remove(entity);
        World::physical().DestroyBody(entity->body());
        delete entity;
    }
    _entitiesToRemove.clear();
}

void World::setEntityAsPlayer(Entity* entity)
{
    _player = entity;
}

Player& World::player()
{
    return *static_cast<Player*>(_player);
}
