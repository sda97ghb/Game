/// \file
/// \brief Содержит класс врага лучника.

#ifndef ARCHER_H
#define ARCHER_H

#include "Game/Enemy.h"

/// \brief Класс лучника
class Archer : public Enemy
{
public:
    Archer();

    /// \brief Возвращает физическую ширину.
    float width() const;
    /// \brief Возвращает физическую высоту.
    float height() const;

    /// \brief Вызывает функцию текущего состояния.
    void update();

private:
    Archer(const Archer& archer) = delete;
    void operator= (const Archer& archer) = delete;

    bool isReadyForStrike();
    void strike();

    enum class State
    {
        lookingAround,
        prepareToStrike,
        goingToLastSeenPosition
    };

    State _state;
};

#endif // ARCHER_H
