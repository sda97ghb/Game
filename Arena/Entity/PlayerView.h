#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Arena/SpriteAnimator.h"

#include "Arena/Entity/EntityView.h"
#include "Arena/Entity/Player.h"

class PlayerView : public EntityView
{
public:
    PlayerView(const Player& player);

    const sf::Sprite& getSprite();

private:
    const Player& _player;
    SpriteAnimator _animator;
};

#endif // PLAYERVIEW_H
