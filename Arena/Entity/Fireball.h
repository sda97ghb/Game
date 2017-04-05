/// @file
/// @brief Содержит класс фаербола.

#ifndef FIREBALL_H
#define FIREBALL_H

#include "Arena/Entity/Enemy.h"

/// @brief Класс фаербола. Летает. Сам наводится на игрока. При ударе наносит урон.
class Fireball : public Enemy
{
public:
    /// @brief Создает фаербол в указанном месте.
    static void spawn(float x, float y);

    /// @brief Конструктор.
    Fireball();

    /// @brief Возвращает физическую ширину.
    float width() const;
    /// @brief Возвращает физическую высоту.
    float height() const;

    /// @brief Вызывает функцию текущего состояния.
    void update();

private:
    // Операторы удалены, потому что при простом копировании существ
    // у них остается одно физическое тело.
    // Возможно это нужно будет исправить в следующих версиях.
    Fireball(const Fireball&) = delete;
    void operator= (const Fireball&) = delete;

    /// @brief Наносит игроку урон и исчезает.
    void boom();

    /// @brief Состояния фаербола.
    enum class State
    {
        going_to_player ///< Летит в направлении игрока.
    };

    State _state; ///< Текущее состояние фаербола.
};

#endif // FIREBALL_H
