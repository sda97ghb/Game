/// @file
/// @brief Содержит класс врага кота-демона.

#ifndef DAEMONCAT_H
#define DAEMONCAT_H

#include "Arena/Entity/Enemy.h"

#include "Arena/Sensors/PlayerSensor.h"

/// @brief Класс лучника
class DaemonCat : public Enemy
{
public:
    /// @brief Конструктор. По умолчанию стартует в состоянии
    /// "смотрит по сторонам".
    DaemonCat();

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
    DaemonCat(const DaemonCat&) = delete;
    void operator= (const DaemonCat&) = delete;

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

#endif // DAEMONCAT_H
