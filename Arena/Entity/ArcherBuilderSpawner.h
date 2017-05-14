#ifndef ARCHERBUILDERSPAWNER_H
#define ARCHERBUILDERSPAWNER_H

#include "Arena/Entity/Archer.h"

/// @brief Класс-конструктор лучника.
class ArcherBuilderSpawner
{
public:
    ArcherBuilderSpawner();

    /// @brief Устанавливает позицию появления.
    ArcherBuilderSpawner& setPosition(const b2Vec2& position);

    /// @brief Устанавливает позицию появления.
    ArcherBuilderSpawner& setPosition(float x, float y);

    /// @brief Непосредственно создает лучника.
    void spawn();

private:
    float width() const;  ///< ширина физического тела
    float height() const; ///< высота физического тела

    /// @brief Физическое тело.
    b2Body* body();

    /// @brief Создает физическое тело тело, но не физическую форму.
    void createBody();

    /// @brief Создает физическую форму.
    void constructBody();

    /// @brief Создает все сенсоры.
    void constructSensors();

    Archer* _archer; /// создаваемый лучник

    b2Vec2 _position; /// позиция появления
};

#endif // ARCHERBUILDERSPAWNER_H
