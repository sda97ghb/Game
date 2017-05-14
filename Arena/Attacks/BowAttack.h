#ifndef BOWATTACK_H
#define BOWATTACK_H

#include "Box2D/Common/b2Math.h"

#include "Arena/Attacks/Attack.h"

#include "Arena/Entity/ArrowBuilderSpawner.h"

/// @brief Класс атаки из лука.
class BowAttack : public Attack
{
public:
    // overloading for ArrowBuilderSpawner's methods with another return type

    /// @brief Устанавливает урон от попадания.
    BowAttack& setDamage(float damage);

    /// @brief Устанавливает направление выстрела.
    BowAttack& setDirection(float angle);

    /// @brief Устанавливает позицию, из которой производится выстрел.
    BowAttack& setPosition(const b2Vec2& position);

    /// @brief Устанавливает позицию, из которой производится выстрел.
    BowAttack& setPosition(float x, float y);

    /// @brief Устанавливает скорость вылета стрелы.
    BowAttack& setSpeed(float speed);

    /// @brief Устанавливает позицию, в которою будет выпущена стрела.
    BowAttack& setTarget(const b2Vec2& position);

    // special methods for Attack

    /// @brief Устанавливает, кто будет производить выстрел.
    /// @note Нет никакой разницы между этим методом и setActor(Animalia& actor),
    /// кроме типа аргумента.
    BowAttack& setActor(Animalia* actor);

    /// @brief Устанавливает, кто будет производить выстрел.
    /// @note Нет никакой разницы между этим методом и setActor(Animalia* actor),
    /// кроме типа аргумента.
    BowAttack& setActor(Animalia& actor);

    /// @brief Устанавливает, в какую точку будет выпущена стрела.
    /// @note Нет никакой разницы между этим методом и setTarget(Animalia& target),
    /// кроме типа аргумента.
    BowAttack& setTarget(Animalia* target);

    /// @brief Устанавливает, в какую точку будет выпущена стрела.
    /// @note Нет никакой разницы между этим методом и setTarget(Animalia* target),
    /// кроме типа аргумента.
    BowAttack& setTarget(Animalia& target);

    /// @brief Производит выстрел.
    void perform();

private:
    ArrowBuilderSpawner _arrowBuilderSpawner; ///< Вспомогательный объект построитель стрел
};

#endif // BOWATTACK_H
