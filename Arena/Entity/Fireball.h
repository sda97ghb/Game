/// \file
/// \brief Содержит класс фаербола.

#ifndef FIREBALL_H
#define FIREBALL_H

#include "Arena/Entity/Enemy.h"

/// \brief Класс лучника
class Fireball : public Enemy
{
public:
    static void spawn(float x, float y);

    Fireball();

    /// \brief Возвращает физическую ширину.
    float width() const;
    /// \brief Возвращает физическую высоту.
    float height() const;

    /// \brief Вызывает функцию текущего состояния.
    void update();

private:
    Fireball(const Fireball&) = delete;
    void operator= (const Fireball&) = delete;

    void strike();

    enum class State
    {
        going_to_player
    };

    State _state;
};

#endif // FIREBALL_H
