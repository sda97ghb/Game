/// \file
/// \brief Содержит класс игрока.

#ifndef PLAYER_H
#define PLAYER_H

#include "Arena/Entity.h"

/// \brief Класс игрока.
/// \note Вы можете обратиться к нему из любого места вызвав Player::instance()
class Player : public Entity
{
public:
    /// \brief Возвращает ссылку на объект игрока.
	static Player& instance();

    /// \brief Физическая ширина игрока
    float width() const;

    /// \brief Физическая высота игрока
    float height() const;

    /// \brief Заставляет игрока нанести удар.
    void punch();

    /// \brief Вызывает функцию текущего состояния.
    void update();

private:
    Player();
	Player(const Player&) = delete;
	void operator= (const Player&) = delete;
};

#endif //PLAYER_H
