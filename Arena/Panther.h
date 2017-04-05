/// \file
/// \brief Содержит класс врага лучника.

#ifndef PANTHER_H
#define PANTHER_H

#include "Arena/Enemy.h"

/// \brief Класс лучника
class Panther : public Enemy
{
public:
    Panther();

    /// \brief Возвращает физическую ширину.
    float width() const;
    /// \brief Возвращает физическую высоту.
    float height() const;

    /// \brief Вызывает функцию текущего состояния.
    void update();

private:
    Panther(const Panther& panther) = delete;
    void operator= (const Panther& panther) = delete;

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

#endif // PANTHER_H
