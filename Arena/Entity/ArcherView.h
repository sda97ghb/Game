#ifndef ARCHERVIEW_H
#define ARCHERVIEW_H

#include "Arena/SpriteAnimator.h"

#include "Arena/Entity/Archer.h"
#include "Arena/Entity/EntityView.h"

/// Класс-отображение лучника.
class ArcherView : public EntityView
{
public:
    /// @brief Создает отображение лучника.
    ArcherView(const Archer& archer);

    /// @brief Спрайт, готовый к отрисовке.
    const sf::Sprite& getSprite();

    /// @brief Существо, для которого создано это отображение.
    const Entity* entity() const;

private:
    const Archer& _archer;    ///< лучник этого отображения
    SpriteAnimator _animator; ///< аниматор текстуры
};

#endif // ARCHERVIEW_H
