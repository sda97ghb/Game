#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/IdDispenser.h"
#include "Arena/PaintingWindow.h"
#include "Arena/SensorListener.h"
#include "Arena/World.h"

#include "Arena/Entity/ArcherBuilderSpawner.h"
#include "Arena/Entity/ArcherView.h"

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
    World::instance().addEntity(_archer);
    _archer->callEventCallback(_archer->spawnEvent);
    PaintingWindow::instance().addEntityView(new ArcherView(*_archer));
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

    AbyssSensor& abyssSensor = _archer->_abyssSensor;
    abyssSensor.setDx(  width() * 0.65f);
    abyssSensor.setDy(- height() / 2.0f - 0.1f);
    abyssSensor.hangOnBody(body());

    ContactSensor& leftContactSensor = _archer->_leftContactSensor;
    leftContactSensor.setType(IdDispenser::getNewId());
    leftContactSensor.setPosition(-width() / 2.0, 0.0f);
    leftContactSensor.setSize(0.1, height() / 2.0f * 0.9f);
    leftContactSensor.hangOnBody(body());

    ContactSensor& rightContactSensor = _archer->_rightContactSensor;
    rightContactSensor.setType(IdDispenser::getNewId());
    rightContactSensor.setPosition(width() / 2.0, 0.0f);
    rightContactSensor.setSize(0.1, height() / 2.0f * 0.9f);
    rightContactSensor.hangOnBody(body());

    ContactSensor& groundContactSensor = _archer->_groundContactSensor;
    groundContactSensor.setType(IdDispenser::getNewId());
    groundContactSensor.setPosition(0.0f, -height() / 2.0f);
    groundContactSensor.setSize(width() / 2.0f * 0.9f, 0.1);
    groundContactSensor.hangOnBody(body());

    HitSensor& groundHitSensor = _archer->_groundHitSensor;
    groundHitSensor.setType(IdDispenser::getNewId());
    groundHitSensor.setPosition(0.0f, -height() / 2.0f);
    groundHitSensor.setSize(width() / 2.0f * 0.9f, 0.3);
    groundHitSensor.setActivationThreshold(10.0f);
    groundHitSensor.setOnHitCallback(
        [entityPtr] (float speed)
        {
            entityPtr->onGroundHit(speed);
            entityPtr->callEventCallback(entityPtr->groundHitEvent);
        });
    groundHitSensor.hangOnBody(body());

    HitSensor& landingSensor = entityPtr->_landingSensor;
    landingSensor.setType(IdDispenser::getNewId());
    landingSensor.setPosition(0.0f, -height() / 2.0f);
    landingSensor.setSize(width() / 2.0f * 0.95f, 0.1f);
    landingSensor.setRequireActivationThreshold(false);
    landingSensor.setOnHitCallback(
        [entityPtr] (float)
        {
            entityPtr->callEventCallback(entityPtr->landingEvent);
        });
    landingSensor.hangOnBody(body());

    HitSensor& leftBumpSensor = entityPtr->_leftBumpSensor;
    leftBumpSensor.setType(IdDispenser::getNewId());
    leftBumpSensor.setPosition(-width() / 2.0f, 0.0f);
    leftBumpSensor.setSize(0.1f, width() / 2.0f * 0.95f);
    leftBumpSensor.setRequireActivationThreshold(false);
    leftBumpSensor.setOnHitCallback(
        [entityPtr] (float)
        {
            entityPtr->callEventCallback(entityPtr->bumpEvent);
        });
    leftBumpSensor.hangOnBody(body());

    HitSensor& rightBumpSensor = entityPtr->_rightBumpSensor;
    rightBumpSensor.setType(IdDispenser::getNewId());
    rightBumpSensor.setPosition(width() / 2.0f, 0.0f);
    rightBumpSensor.setSize(0.1f, width() / 2.0f * 0.95f);
    rightBumpSensor.setRequireActivationThreshold(false);
    rightBumpSensor.setOnHitCallback(
        [entityPtr] (float)
        {
            entityPtr->callEventCallback(entityPtr->bumpEvent);
        });
    rightBumpSensor.hangOnBody(body());

    PlayerSensor& playerSensor = _archer->_playerSensor;
    playerSensor.setNearbyDistance(25.0f);
    playerSensor.setOnGotSightOfPlayerCallback(
        [entityPtr] () {
            entityPtr->callEventCallback(entityPtr->gotSightOfPlayerEvent);
        });
    playerSensor.setOnLostSightOfPlayerCallback(
        [entityPtr] () {
            entityPtr->callEventCallback(entityPtr->lostSightOfPlayerEvent);
        });
    playerSensor.hangOnBody(body());

    TimerSensor& reloadSensor = _archer->_reloadSensor;
    reloadSensor.setTime(1000.0);
    reloadSensor.setOnTimeoutCallback(
        [entityPtr] ()
        {
//            entityPtr->strike();
//            entityPtr->callEventCallback(entityPtr->strikeEvent);
        });
    // Not need to hang the sensor on the body.
}
