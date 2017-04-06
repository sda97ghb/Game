/// @file
/// @brief Содержит класс врага лучника.

#ifndef ARCHER_H
#define ARCHER_H

#include "Arena/Entity/Enemy.h"

#include "Arena/Sensors/AbyssSensor.h"

/// @brief Класс лучника
class Archer : public Enemy
{
public:
    /// @brief Конструктор. Изачально устанавливает в состояние
    /// "смотрит по сторонам".
    Archer();

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
    Archer(const Archer& archer) = delete;
    void operator= (const Archer& archer) = delete;

    /// @brief Вешает сенсоры на тело.
    /// @details Для лучника это сенсор пропасти.
    void constructSensors();

    /// @brief Проверка, натянута ли тетива.
    bool isReadyForStrike();

    /// @brief Совершает выстрел.
    void strike();

    /// @brief Состояния лучника.
    enum class State
    {
        lookingAround,          ///< Смотрит по сторонам, ждет игрока.
        prepareToStrike,        ///< Натягивает тетиву, стреляет.
        goingToLastSeenPosition ///< Идет к тому месту, где последний раз видел игрока.
    };

    State _state; ///< Текущее состояние лучника.

    AbyssSensor _abyssSensor;
};

#endif // ARCHER_H
