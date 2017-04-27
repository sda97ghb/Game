/// @file
/// @brief Содержит класс сенсора игрока.

#ifndef PLAYERSENSOR_H
#define PLAYERSENSOR_H

#include <functional>

#include "Arena/Updatable.h"

class b2Body;

/// @brief Класс сенсора, который может определить находится ли игрок
/// поблизости от сенсора или можно ли увидеть игрока с позиции
/// сенсора.
/// По умолчанию сенсор будет активен, если игрок находится
/// в прямой видимости и на расстоянии не более 20 метров.
class PlayerSensor : public Updatable
{
    friend class PlayerSensorBuilder;

public:
    using Callback = std::function<void()>;

    /// @brief Проверка возможности видеть игрока с позиции сенсора.
    bool canSee();

    /// @brief Проверка нахождения игрока рядом с сенсором.
    bool isNearby();

    /// @brief Проверка активности сенсора.
    /// @details Активность сенсора зависит от установленных критериев.
    bool isActive();

    float nearbyDistance() const;

    bool canSeeRequired() const;
    bool isNearbyRequired() const;

    void update();

private:
    /// @brief Конструктор.
    PlayerSensor();

    float _nearbyDistance;

    bool _isNearbyRequired;
    bool _canSeeRequired;

    bool _previousState;

    Callback _onGotSightOfPlayerCallback;
    Callback _onLostSightOfPlayerCallback;

    b2Body* _body;
};

#endif // PLAYERSENSOR_H
