#ifndef SWORDATTACK_H
#define SWORDATTACK_H

#include "Arena/Attacks/Attack.h"

/// @brief Класс атаки мечем.
/// @details Атака производится по всем существам находящимся со стороны,
/// совпадающей с направлением взгляда атакующего и находящимся на дистанции
/// не больше указанной.
class SwordAttack : public Attack
{
public:
    SwordAttack();

    /// @brief Устанавливает, кто производит удар.
    SwordAttack& setActor(Animalia* animalia);

    /// @brief Устанавливает, кто производит удар.
    SwordAttack& setActor(Animalia& animalia);

    /// @brief Устанавливает урон от удара.
    SwordAttack& setDamage(float damage);

    /// @brief Устанавливает расстояние, в пределах которого производится атака.
    SwordAttack& setDistance(float distance);

    /// @brief Производит атаку.
    void perform();

private:
    float _damage;   ///< урон от атаки
    float _distance; ///< расстояние атаки
};

#endif // SWORDATTACK_H
