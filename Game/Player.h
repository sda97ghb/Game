#ifndef PLAYER_H
#define PLAYER_H

#include "Game/Entity.h"
#include <Box2D/Dynamics/b2Body.h>

class Player : public Entity
{
public:
	static Player& instance();
    void update();

private:
	Player();
	Player(const Player&) = delete;
	void operator= (const Player&) = delete;
};




#endif //PLAYER_H
