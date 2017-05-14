#ifndef PLAYER1VIEW_H
#define PLAYER1VIEW_H

#include "Arena/Entity/PlayerView.h"

class Player1View : public PlayerView
{
public:
    Player1View(const Player& player);

    const sf::Sprite& getSprite();
};

#endif // PLAYER1VIEW_H
