/// @file
/// @brief Содержит класс врага лучника.

#ifndef PANTHER_H
#define PANTHER_H

#include "Arena/Entity/Enemy.h"

#include "Arena/Sensors/PlayerSensor.h"

/// @brief Класс лучника
class Panther : public Enemy
{
public:
    /// @brief Конструктор. По умолчанию стартует в состоянии
    /// "смотрит по сторонам".
    Panther();

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
    Panther(const Panther& panther) = delete;
    void operator= (const Panther& panther) = delete;

    /// @brief Вешает сенсоры на тело.
    /// @details Для пантеры это сенсор игрока.
    void constructSensors();

    /// @brief Готова ли запустить фаербол.
    bool isReadyForStrike();

    /// @brief Запускает фаербол.
    void strike();

    enum class State
    {
        lookingAround,
        prepareToStrike,
        goingToLastSeenPosition
    };

    State _state; ///< Текущее состояние пантеры.

    PlayerSensor _playerSensor; ///< Сенсор игрока.
};

#endif // PANTHER_H
