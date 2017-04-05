#include "Arena/SensorListener.h"
#include "Arena/World.h"

World::World()
{
    b2Vec2 gravity(0.0f, -9.8f);
    _world = new b2World(gravity);

    createPlayer();

    _world->SetContactListener(&SensorListener::instance());
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

Archer& World::createArcher()
{
    _archers.emplace_back();
    Archer& archer = _archers.back();

    archer.setBody(createBodyForEntity());
    archer.constructBody();

    return archer;
}

Panther&World::createPanther()
{
    _panthers.emplace_back();
    Panther& panther = _panthers.back();

    panther.setBody(createBodyForEntity());
    panther.constructBody();
    return panther;
}

Fireball& World::createFireball()
{
    _fireballs.emplace_back();
    Fireball& fireball = _fireballs.back();

    fireball.setBody(createBodyForEntity());
    fireball.constructBody();
    return fireball;
}

Player& World::player()
{
    return Player::instance();
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

const std::list<Archer>& World::archers() const
{
    return _archers;
}

const std::list<Panther>& World::panthers() const
{
    return _panthers;
}

const std::list<Fireball>&World::fireballs() const
{
    return _fireballs;
}

void World::update()
{
    for (Ladder& ladder : _ladders)
        ladder.testPlayerOnIt();

	for (Spikes& spikes : _spikes)
		spikes.testPlayerOnIt();

    for (Water& water : _waters)
        water.testPlayerOnIt();

    for (Lava& lava : _lavas)
        lava.testPlayerOnIt();

    for (Archer& archer : _archers)
        archer.update();

    for (Panther& panther : _panthers)
        panther.update();

    for (Fireball& fireball : _fireballs)
        fireball.update();

    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

    _world->Step(timeStep, velocityIterations, positionIterations);
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
