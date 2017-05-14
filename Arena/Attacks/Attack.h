#ifndef ATTACK_H
#define ATTACK_H

class Animalia;

/// @brief Базовый класс для всех атак.
/// @details Содержит указатель на того, кто производит атаку
/// и чисто виртуальный метод для воспроизведения атаки.
class Attack
{
public:
    Attack();

    /// @brief Устанавливает, кто будет производить атаку.
    void setActor(Animalia* actor);

    /// @brief Воспроизводит атаку.
    virtual void perform() = 0;

protected:
    Animalia* _actor; ///< кто будет производить атаку
};

#endif // ATTACK_H
