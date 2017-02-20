#include "Game/Entity.h"

void Entity::setPosition(float x, float y)
{
    _body->SetTransform(b2Vec2(x, y), _body->GetAngle());
}

float Entity::x()
{
    return _body->GetPosition().x;
}

float Entity::y()
{
    return _body->GetPosition().y;
}

void Entity::damage(float value)
{
	if(value > _health) _health = 0.0;
	else _health -= value;
}

bool Entity::isAlive()
{ 
	return _health > 0.0; 
}

b2Body& Entity::body()
{
	return *_body;
}
