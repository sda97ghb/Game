#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/IdDispenser.h"
#include "Arena/PaintingWindow.h"
#include "Arena/SensorListener.h"
#include "Arena/World.h"

#include "Arena/Entity/PlayerBuilderSpawner.h"
#include "Arena/Entity/PlayerView.h"

#include "Arena/Sensors/ContactSensorBuilder.h"
#include "Arena/Sensors/HitSensorBuilder.h"

PlayerBuilderSpawner::PlayerBuilderSpawner() :
    _position(0.0f, 0.0f)
{
    _player = new Player;
}

PlayerBuilderSpawner& PlayerBuilderSpawner::setPosition(const b2Vec2& position)
{
    _position = position;
    return *this;
}

PlayerBuilderSpawner& PlayerBuilderSpawner::setPosition(float x, float y)
{
    _position.Set(x, y);
    return *this;
}

void PlayerBuilderSpawner::spawn()
{
    createBody();
    constructBody();
    constructSensors();
    World::instance().setPlayer(_player);
    _player->callEventCallback(_player->spawnEvent);
    new PlayerView(*_player);
}

float PlayerBuilderSpawner::width() const
{
    return 0.75f;
}

float PlayerBuilderSpawner::height() const
{
    return 1.75f;
}

b2Body* PlayerBuilderSpawner::body()
{
    return _player->body();
}

void PlayerBuilderSpawner::createBody()
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.position = _position;
    bodyDef.type = b2_dynamicBody;

    b2Body* body = World::physical().CreateBody(&bodyDef);

    _player->setBody(body);
}

void PlayerBuilderSpawner::constructBody()
{
    if (body() == nullptr)
        throw std::logic_error("No body was provided.");
//        throw NoBodyException();

    b2PolygonShape bodyShape;
    bodyShape.SetAsBox(width() / 2.0f, height() / 2.0f);

    b2FixtureDef bodyFixtureDef;
    bodyFixtureDef.shape = &bodyShape;
    bodyFixtureDef.density = 57.14f; // human density ~= (75kg / (1.75m * 0.75m))
    bodyFixtureDef.friction = 20.0f;
    bodyFixtureDef.restitution = 0.0f;

    body()->CreateFixture(&bodyFixtureDef);
}

void PlayerBuilderSpawner::constructSensors()
{
    Player* entityPtr = _player;

    _player->_leftContactSensor = ContactSensorBuilder()
            .setPosition(-width() / 2.0, 0.0f)
            .setSize(0.1, height() / 2.0f * 0.9f)
            .setBody(body())
            .build();

    _player->_rightContactSensor = ContactSensorBuilder()
            .setPosition(width() / 2.0, 0.0f)
            .setSize(0.1, height() / 2.0f * 0.9f)
            .setBody(body())
            .build();

    _player->_groundContactSensor = ContactSensorBuilder()
            .setPosition(0.0f, -height() / 2.0f)
            .setSize(width() / 2.0f * 0.9f, 0.1)
            .setBody(body())
            .build();

    _player->_groundHitSensor = HitSensorBuilder()
        .setPosition(0.0f, -height() / 2.0f)
        .setSize(width() / 2.0f * 0.9f, 0.3)
        .setActivationThreshold(10.0f)
        .setOnHitCallback(
            [entityPtr] (float speed)
            {
                entityPtr->onGroundHit(speed);
                entityPtr->callEventCallback(entityPtr->groundHitEvent);
            })
        .setBody(body())
        .build();

    _player->_landingSensor = HitSensorBuilder()
        .setPosition(0.0f, -height() / 2.0f)
        .setSize(width() / 2.0f * 0.9f, 0.1f)
        .setRequireActivationThreshold(false)
        .setOnHitCallback(
            [entityPtr] (float)
            {
                entityPtr->callEventCallback(entityPtr->landingEvent);
            })
        .setBody(body())
        .build();
}
