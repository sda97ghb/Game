#ifndef PLAYER_H
#define PLAYER_H

#include "Game/Entity.h"

class Player : public Entity
{
public:
	static Player& instance();

    float width() const;
    float height() const;

    void update();

private:
    Player();
	Player(const Player&) = delete;
	void operator= (const Player&) = delete;
};

#endif //PLAYER_H
