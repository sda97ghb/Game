#include <iostream>
#include "Entity.h"

Entity::Entity() :
    _body(nullptr)
{}

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
