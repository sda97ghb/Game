#include "Game/Entity.h"


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