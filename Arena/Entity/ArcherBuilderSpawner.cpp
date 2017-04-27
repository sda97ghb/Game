#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/IdDispenser.h"
#include "Arena/PaintingWindow.h"
#include "Arena/SensorListener.h"
#include "Arena/World.h"

#include "Arena/Entity/ArcherBuilderSpawner.h"
#include "Arena/Entity/ArcherView.h"

#include "Arena/Sensors/AbyssSensorBuilder.h"
#include "Arena/Sensors/ContactSensorBuilder.h"
#include "Arena/Sensors/HitSensorBuilder.h"
#include "Arena/Sensors/PlayerSensorBuilder.h"
#include "Arena/Sensors/TimerSensorBuilder.h"

ArcherBuilderSpawner::ArcherBuilderSpawner() :
    _position(0.0f, 0.0f)
{
    _archer = new Archer;
}

ArcherBuilderSpawner& ArcherBuilderSpawner::setPosition(const b2Vec2& position)
{
    _position = position;
    return *this;
}

ArcherBuilderSpawner& ArcherBuilderSpawner::setPosition(float x, float y)
{
    _position.Set(x, y);
    return *this;
}

void ArcherBuilderSpawner::spawn()
{
    createBody();
    constructBody();
    constructSensors();
    _archer->callEventCallback(_archer->spawnEvent);
    new ArcherView(*_archer);
}

float ArcherBuilderSpawner::width() const
{
    return 0.75f;
}

float ArcherBuilderSpawner::height() const
{
    return 1.75f;
}

b2Body* ArcherBuilderSpawner::body()
{
    return _archer->body();
}

void ArcherBuilderSpawner::createBody()
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.position = _position;
    bodyDef.type = b2_dynamicBody;

    b2Body* body = World::physical().CreateBody(&bodyDef);

    _archer->setBody(body);
}

void ArcherBuilderSpawner::constructBody()
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

void ArcherBuilderSpawner::constructSensors()
{
    Archer* entityPtr = _archer;

    _archer->_abyssSensor = AbyssSensorBuilder()
            .setDx(width() * 0.65f)
            .setDy(- height() / 2.0f - 0.1f)
            .setBody(body())
            .build();

    _archer->_leftContactSensor = ContactSensorBuilder()
            .setPosition(-width() / 2.0, 0.0f)
            .setSize(0.1, height() / 2.0f * 0.9f)
            .setBody(body())
            .build();

    _archer->_rightContactSensor = ContactSensorBuilder()
            .setPosition(width() / 2.0, 0.0f)
            .setSize(0.1, height() / 2.0f * 0.9f)
            .setBody(body())
            .build();

    _archer->_groundContactSensor = ContactSensorBuilder()
            .setPosition(0.0f, -height() / 2.0f)
            .setSize(width() / 2.0f * 0.9f, 0.3)
            .setBody(body())
            .build();

    _archer->_groundHitSensor = HitSensorBuilder()
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

    _archer->_landingSensor = HitSensorBuilder()
            .setPosition(0.0f, -height() / 2.0f)
            .setSize(width() / 2.0f * 0.95f, 0.1f)
            .setRequireActivationThreshold(false)
            .setOnHitCallback(
                [entityPtr] (float)
                {
                    entityPtr->callEventCallback(entityPtr->landingEvent);
                })
            .setBody(body())
            .build();

    _archer->_leftBumpSensor = HitSensorBuilder()
            .setType(IdDispenser::getNewId())
            .setPosition(-width() / 2.0f, 0.0f)
            .setSize(0.1f, width() / 2.0f * 0.95f)
            .setRequireActivationThreshold(false)
            .setOnHitCallback(
                [entityPtr] (float)
                {
                    entityPtr->callEventCallback(entityPtr->bumpEvent);
                })
            .setBody(body())
            .build();

    _archer->_rightBumpSensor = HitSensorBuilder()
            .setType(IdDispenser::getNewId())
            .setPosition(width() / 2.0f, 0.0f)
            .setSize(0.1f, width() / 2.0f * 0.95f)
            .setRequireActivationThreshold(false)
            .setOnHitCallback(
                [entityPtr] (float)
                {
                    entityPtr->callEventCallback(entityPtr->bumpEvent);
                })
            .setBody(body())
            .build();

    _archer->_playerSensor = PlayerSensorBuilder()
            .setNearbyDistance(25.0f)
            .setOnGotSightOfPlayerCallback(
                [entityPtr] () {
                    entityPtr->callEventCallback(entityPtr->gotSightOfPlayerEvent);
                })
            .setOnLostSightOfPlayerCallback(
                [entityPtr] () {
                    entityPtr->callEventCallback(entityPtr->lostSightOfPlayerEvent);
                })
            .setBody(body())
            .build();

    _archer->_reloadSensor = TimerSensorBuilder()
            .setTime(1000.0)
            .setOnTimeoutCallback(
                [entityPtr] ()
                {
                    entityPtr->callEventCallback(entityPtr->readyToStrikeEvent);
                })
            .build();
}
