#include "Game/Player.h"

Player& Player::instance()
{
	static Player instance;
    return instance;
}

b2Body& Player::body()
{
    return *_body;
}

Player::Player()
{
}
