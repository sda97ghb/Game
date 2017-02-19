#include "Game/Player.h"

Player& Player::instance()
{
	static Player instance;
    return instance;
}
