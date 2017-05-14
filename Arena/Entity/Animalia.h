#ifndef ANIMALIA_H
#define ANIMALIA_H

#include "Arena/Direction.h"

#include "Arena/Entity/Entity.h"

/// @brief Базовый класс всех живых существ.
/// @details Добавляет параметр здоровья и методы для его изменения.
/// Добавляет направление взгляда для существ.
/// @note Объекты этого класса учитываются ObjectCounter.
class Animalia : public Entity
{
public:
    Animalia();
    virtual ~Animalia();

    /// @brief Мгновенно убивает существо, устанавливая показатель здоровья
    /// в ноль единиц.
    void kill();

    /// @brief Наносит урон в указанное количество единиц.
    void makeDamage(float damage);

    /// @brief Восстанавливает указанное количество единиц здоровья,
    /// но не больше максимально возможного.
    void heal(float health);

    /// @brief Проверяет, живо ли существо сейчас (показатель здоровья больше 0).
    bool isAlive() const;

    /// @brief Максимально возможное количество единиц здоровья.
    float maxHealth() const;

    /// @brief Устанавливает максимально возможное количество единиц здоровья.
    void setMaxHealth(float maxHealth);

    /// @brief Текущий уровень здоровья.
    float currentHealth() const;

    /// @brief Устанавливает текущий уровень здоровья.
    void setCurrentHealth(float currentHealth);

    /// @brief Если существо живо вызывает событие обновления.
    virtual void update();

    /// @brief Направление взгляда существа.
    Direction lookingDirection() const;

    /// @brief Устанавливает направление взгляда существа.
    void setLookingDirection(const Direction& lookingDirection);

private:
    float _maxHealth;     ///< максимально возможный уровень здоровья
    float _currentHealth; ///< текущий уровень здоровья

    Direction _lookingDirection; ///< направление взгляда существа
};

#endif // ANIMALIA_H
