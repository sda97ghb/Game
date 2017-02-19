#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Dynamics/b2Body.h>

class Entity
{
public:
	virtual void update() = 0;
	void damage(float value);
	bool isAlive();
	b2Body& body();
private:
protected:
	b2Body* _body;
	float _health;
	float _mana;
	sf::Sprite _sprite;
};




#endif //ENTITY_H