/// @file
/// @brief Содержит класс враждебных к игроку существ.

#ifndef ENEMY_H
#define ENEMY_H

#include "Arena/Entity/Entity.h"

/// @brief Базовый класс для враждебных к игроку существ.
class Enemy : public Entity
{
protected:
    bool canSeePlayer();
    bool isAbyssAhead();
    bool isPlayerToLeft();
    void lookForPlayer();

    b2Vec2 _lastSeenPosition;
};

#endif //ENEMY_H
