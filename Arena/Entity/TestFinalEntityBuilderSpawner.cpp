#include <iostream>

#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/IdDispenser.h"
#include "Arena/PaintingWindow.h"
#include "Arena/SensorListener.h"
#include "Arena/World.h"

#include "Arena/Entity/TestFinalEntity.h"
#include "Arena/Entity/TestFinalEntityBuilderSpawner.h"
#include "Arena/Entity/TestFinalEntityView.h"

TestFinalEntityBuilderSpawner::TestFinalEntityBuilderSpawner() :
    _position(0.0f, 0.0f)
{
    _entity = new TestFinalEntity;
}

TestFinalEntityBuilderSpawner&
TestFinalEntityBuilderSpawner::setPosition(const b2Vec2& position)
{
    _position = position;
    return *this;
}

TestFinalEntityBuilderSpawner&
TestFinalEntityBuilderSpawner::setPosition(float x, float y)
{
    _position.Set(x, y);
    return *this;
}

void TestFinalEntityBuilderSpawner::spawn()
{
    createBody();
    constructBody();
    constructSensors();
    _entity->callEventCallback(_entity->spawnEvent);
//    PaintingWindow::instance().addEntityView(new TestFinalEntityView(*_entity));
}

float TestFinalEntityBuilderSpawner::width() const
{
    return 14.0f / 5.0f;
}

float TestFinalEntityBuilderSpawner::height() const
{
    return 6.0f / 5.0f;
}

b2Body* TestFinalEntityBuilderSpawner::body()
{
    return _entity->body();
}

void TestFinalEntityBuilderSpawner::createBody()
{
    b2BodyDef bodyDef;
    bodyDef.fixedRotation = true;
    bodyDef.position = _position;
    bodyDef.type = b2_dynamicBody;

    b2Body* body = World::physical().CreateBody(&bodyDef);

    _entity->setBody(body);
}

void TestFinalEntityBuilderSpawner::constructBody()
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

void TestFinalEntityBuilderSpawner::constructSensors()
{
    AbyssSensor& abyssSensor = _entity->_abyssSensor;
    abyssSensor.setDx(  width() * 0.65f);
    abyssSensor.setDy(- height() / 2.0f);
    abyssSensor.hangOnBody(body());

    ContactSensor& leftContactSensor = _entity->_leftContactSensor;
    leftContactSensor.setType(IdDispenser::getNewId());
    leftContactSensor.setPosition(-width() / 2.0, 0.0f);
    leftContactSensor.setSize(0.1, height() / 2.0f * 0.9f);
    leftContactSensor.hangOnBody(body());

    ContactSensor& rightContactSensor = _entity->_rightContactSensor;
    rightContactSensor.setType(IdDispenser::getNewId());
    rightContactSensor.setPosition(width() / 2.0, 0.0f);
    rightContactSensor.setSize(0.1, height() / 2.0f * 0.9f);
    rightContactSensor.hangOnBody(body());

    ContactSensor& groundContactSensor = _entity->_groundContactSensor;
    groundContactSensor.setType(IdDispenser::getNewId());
    groundContactSensor.setPosition(0.0f, -height() / 2.0f);
    groundContactSensor.setSize(width() / 2.0f * 0.9f, 0.1);
    groundContactSensor.hangOnBody(body());

    HitSensor& groundHitSensor = _entity->_groundHitSensor;
    groundHitSensor.setType(IdDispenser::getNewId());
    groundHitSensor.setPosition(0.0f, -height() / 2.0f);
    groundHitSensor.setSize(width() / 2.0f * 0.9f, 0.3);
    groundHitSensor.setActivationThreshold(10.0f);
    TestFinalEntity* entityPtr = _entity;
    groundHitSensor.setOnHitCallback(
        [entityPtr] (float speed)
        {
            entityPtr->onGroundHit(speed);
            entityPtr->callEventCallback(entityPtr->groundHitEvent);
        });
    groundHitSensor.hangOnBody(body());

    PlayerSensor& playerSensor = _entity->_playerSensor;
    playerSensor.setNearbyDistance(15.0f);
    playerSensor.hangOnBody(body());

    PlayerSensor& nearEnoughToAttackSensor = _entity->_nearEnoughToAttackSensor;
    nearEnoughToAttackSensor.setNearbyDistance(2.0f);
    nearEnoughToAttackSensor.hangOnBody(body());
}
