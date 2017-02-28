/// \file
/// \brief Содержит класс враждебных к игроку существ.

#ifndef ENEMY_H
#define ENEMY_H

#include "Game/Entity.h"

/// \brief Базовый класс для враждебных к игроку существ.
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
