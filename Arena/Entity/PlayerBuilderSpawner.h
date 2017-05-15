#ifndef PLAYERBUILDERSPAWNER_H
#define PLAYERBUILDERSPAWNER_H

#include "Arena/Entity/Player.h"

/// @brief Класс-постоитель для игрока.
class PlayerBuilderSpawner
{
public:
    PlayerBuilderSpawner();

    PlayerBuilderSpawner& setPosition(const b2Vec2& position);
    PlayerBuilderSpawner& setPosition(float x, float y);

    Player* spawn();

    PlayerBuilderSpawner& setPlayerNum(int playerNum);

private:
    float width() const;
    float height() const;

    b2Body* body();

    void createBody();
    void constructBody();
    void constructSensors();

    Player* _player;

    b2Vec2 _position;

    int _playerNum;
};

#endif // PLAYERBUILDERSPAWNER_H
