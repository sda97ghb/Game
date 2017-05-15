#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "Arena/SpriteAnimator.h"

#include "Arena/Entity/EntityView.h"
#include "Arena/Entity/Player.h"

/// @brief Базовый класс-отображение для игроков.
class PlayerView : public EntityView
{
public:
    PlayerView(const Player& player);

    const sf::Sprite& getSprite();

    const Entity* entity() const;

protected:
    const Player& _player;
    SpriteAnimator _animator;
};

#endif // PLAYERVIEW_H
