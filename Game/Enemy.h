#ifndef ENEMY_H
#define ENEMY_H

#include "Game/Entity.h"

class Enemy : public Entity
{
protected:
	void update();
	void going();
	bool inaction();
	bool aggression();
	bool canSeePlayer();
};

#endif //ENEMY_H
