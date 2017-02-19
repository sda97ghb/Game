#ifndef PLAYER_H
#define PLAYER_H

#include <Box2D/Dynamics/b2Body.h>

class Player
{
public:
	static Player& instance();

	b2Body& body();

private:
	Player();
	Player(const Player&) = delete;
	void operator= (const Player&) = delete;

	b2Body* _body;
};




#endif //PLAYER_H