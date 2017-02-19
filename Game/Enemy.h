#ifndef ENEMY_H
#define ENEMY_H

#include "Game/Entity.h"
#include <SFML/Graphics.hpp>

class Enemy : public Entity
{
public:
	
protected:
	void update();
	void going();
	bool inaction();
	bool aggression();
	bool canSeePlayer();
};




#endif //ENEMY_H