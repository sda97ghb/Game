#include <cmath>

#include "Box2D/Dynamics/b2Fixture.h"

#include "Arena/ObjectCounter.h"
#include "Arena/PaintingWindow.h"
#include "Arena/World.h"

#include "Arena/Entity/ArrowBuilderSpawner.h"
#include "Arena/Entity/ArrowView.h"

ArrowBuilderSpawner::ArrowBuilderSpawner() :
    _arrow(nullptr),
    _position(0.0f, 0.0f),
    _target(0.0f, 0.0f),
    _angle(0.0f),
    _speed(50.0f),
    _launchMode(LaunchMode::angle)
{
    _arrow = new Arrow;
}

ArrowBuilderSpawner& ArrowBuilderSpawner::setPosition(const b2Vec2& position)
{
    _position = position;
    return *this;
}

ArrowBuilderSpawner& ArrowBuilderSpawner::setPosition(float x, float y)
{
    _position.Set(x, y);
    return *this;
}

ArrowBuilderSpawner& ArrowBuilderSpawner::setTarget(const b2Vec2& target)
{
    _target = target;
    _launchMode = LaunchMode::target;
    return *this;
}

ArrowBuilderSpawner&ArrowBuilderSpawner::setTarget(float x, float y)
{
    _target.Set(x, y);
    _launchMode = LaunchMode::target;
    return *this;
}

ArrowBuilderSpawner& ArrowBuilderSpawner::setDirection(float angle)
{
    _angle = angle;
    _launchMode = LaunchMode::angle;
    return *this;
}

ArrowBuilderSpawner& ArrowBuilderSpawner::setSpeed(float speed)
{
    _speed = speed;
    return *this;
}

void ArrowBuilderSpawner::spawn()
{
    createBody();
    constructBody();
    constructSensors();
    World::instance().addEntity(_arrow);
    _arrow->callEventCallback(_arrow->spawnEvent);
    PaintingWindow::instance().addEntityView(new ArrowView(*_arrow));
}

float ArrowBuilderSpawner::width() const
{
    return 0.6f;
}

float ArrowBuilderSpawner::height() const
{
    return 0.2f;
}

b2Body* ArrowBuilderSpawner::body()
{
    return _arrow->body();
}

void ArrowBuilderSpawner::createBody()
{
    b2BodyDef bodyDef;
    bodyDef.bullet = true;
//    bodyDef.fixedRotation = true;
    bodyDef.position = _position;
    bodyDef.type = b2_dynamicBody;

    switch (_launchMode)
    {
        case LaunchMode::angle : {
            bodyDef.angle = _angle;
            bodyDef.linearVelocity.Set(_speed * ::cosf(_angle),
                                       _speed * ::sinf(_angle));
        } break;
        case LaunchMode::target : {
            b2Vec2 d = _target - _position;
            d.Normalize();

            bodyDef.angle = ::atan2f(d.y, d.x);

            d *= _speed;
            bodyDef.linearVelocity = d;
        } break;
    }

    b2Body* body = World::physical().CreateBody(&bodyDef);

    _arrow->setBody(body);
}

void ArrowBuilderSpawner::constructBody()
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

void ArrowBuilderSpawner::constructSensors()
{
    Arrow* enityPtr = _arrow;

    EnityCollisionSensor& entityCollisionSensor = enityPtr->_entityCollisionSensor;
    entityCollisionSensor.setSize(width() / 2.0f, height() / 2.0f);
    entityCollisionSensor.setOnCollisionCallback(
        [enityPtr] (Entity* entity)
        {
            enityPtr->hitEntity(entity);
        });
    entityCollisionSensor.hangOnBody(body());

//    entityCollisionSensor.setOnCollisionCallback(
//        [enityPtr] (b2Body* body)
//        {
//            for (Entity* entity : ObjectCounter<Entity>::objects())
//                if (entity->body() == body)
//                    enityPtr->hitEntity(entity);
//        });
}