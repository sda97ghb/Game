#include <iostream>

#include "Arena/ObjectCounter.h"

#include "Arena/Entity/Entity.h"

Entity::Entity() :
    _body(nullptr),
    _isMarkedAsDeleted(false)
{
    ObjectCounter<Entity>::addObject(this);
}

Entity::~Entity()
{
    ObjectCounter<Entity>::removeObject(this);
}

const b2Vec2& Entity::position() const
{
    return body()->GetPosition();
}

void Entity::setPosition(float x, float y)
{
    body()->SetTransform(b2Vec2(x, y), body()->GetAngle());
}

void Entity::update()
{
    callEventCallback(updateEvent);
}

b2Body* Entity::body() const
{
    return _body;
}

void Entity::setBody(b2Body* body)
{
    _body = body;
}

void Entity::markAsDeleted()
{
    _isMarkedAsDeleted = true;
}

bool Entity::inMarkedAsDeleted() const
{
    return _isMarkedAsDeleted;
}
