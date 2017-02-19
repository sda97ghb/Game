#ifndef ENEMY_H
#define ENEMY_H

#include "Game/Entity.h"
#include <SFML/Graphics.hpp>

class Enemy : public Entity
{
public:
	
protected:
	void inaction();
	void aggression();
	bool canSeePlayer();
};




#endif //ENEMY_H