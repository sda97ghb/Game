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

void Entity::update()
{
//    return_if_deleted

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

bool Entity::isMarkedAsDeleted() const
{
    return _isMarkedAsDeleted;
}
