#ifndef PLAYER2VIEW_H
#define PLAYER2VIEW_H

#include "Arena/Entity/PlayerView.h"

/// @brief Класс отображение второго игрока.
class Player2View : public PlayerView
{
public:
    Player2View(const Player& player);

    const sf::Sprite& getSprite();
};

#endif // PLAYER2VIEW_H
