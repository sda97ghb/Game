/// @file
/// @brief Содержит класс сенсора игрока.

#ifndef PLAYERSENSOR_H
#define PLAYERSENSOR_H

#include "Box2D/Dynamics/b2Body.h"

/// @brief Класс сенсора, который может определить находится ли игрок
/// поблизости от сенсора или можно ли увидеть игрока с позиции
/// сенсора.
class PlayerSensor
{
public:
    /// @brief Конструктор.
    PlayerSensor();

    /// @brief Вешает датчик на тело.
    void hangOnBody(b2Body* body);

    /// @brief Проверка возможности видеть игрока с позиции сенсора.
    bool canSee();

    /// @brief Проверка нахождения игрока рядом с сенсором.
    bool isNearby();

    /// @brief Проверка активности сенсора.
    /// @details Активность сенсора зависит от установленных критериев.
    /// По умолчанию сенсор будет активен, если игрок находится
    /// в прямой видимости и на расстоянии не более 20 метров.
    bool isActive();

    float nearbyDistance() const;
    void setNearbyDistance(float nearbyDistance);

    bool canSeeRequired() const;
    bool isNearbyRequired() const;

    void setCanSeeRequired(bool canSeeRequired);
    void setIsNearbyRequired(bool isNearbyRequired);

private:
    float _nearbyDistance;

    bool _isNearbyRequired;
    bool _canSeeRequired;

    b2Body* _body;
};

#endif // PLAYERSENSOR_H
