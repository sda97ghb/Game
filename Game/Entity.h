#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <Box2D/Dynamics/b2Body.h>

class Entity
{
public:
    void setPosition(float x, float y);

    float x();
    float y();

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
