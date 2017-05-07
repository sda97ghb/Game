#include "Arena/GlobalConstants.h"
#include "Arena/ObjectCounter.h"
#include "Arena/SensorListener.h"
#include "Arena/World.h"

#include "Arena/Entity/Entity.h"

World::World() :
    _player1(nullptr),
    _player2(nullptr)
{
    World::physical().SetContactListener(&SensorListener::instance());
}

b2World& World::physical()
{
    static b2World physical(GRAVITY_VECTOR);
    return physical;
}

World& World::instance()
{
    static World instance;
    return instance;
}

void World::update()
{
    for (Updatable* updatable : ObjectCounter<Updatable>::objects())
        updatable->update();

    //---- ANCIENT SHIT CESTION BEGIN ----//

    for (Ladder& ladder : _ladders)
        ladder.testPlayerOnIt();

    for (Spikes& spikes : _spikes)
        spikes.testPlayerOnIt();

    for (Water& water : _waters)
        water.testPlayerOnIt();

    for (Lava& lava : _lavas)
        lava.testPlayerOnIt();

    //---- ANCIENT SHIT CESTION END ----//

    const float32 timeStep = 1.0f / 60.0f;
    const int32 velocityIterations = 8;
    const int32 positionIterations = 3;

    World::physical().Step(timeStep, velocityIterations, positionIterations);
}

void World::setPlayer1(Player* player)
{
    _player1 = player;
}

void World::setPlayer2(Player* player)
{
    _player2 = player;
}

Player* World::player1()
{
    return _player1;
}

Player* World::player2()
{
    return _player2;
}

//---- ANCIENT SHIT CESTION BEGIN ----//

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

//---- ANCIENT SHIT CESTION END ----//
