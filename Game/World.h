/// \file
/// \brief Содержит класс мира.

#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "Box2D/Dynamics/b2World.h"

#include "Game/Archer.h"
#include "Game/Cable.h"
#include "Game/FallingGround.h"
#include "Game/Ladder.h"
#include "Game/Lava.h"
#include "Game/Mage.h"
#include "Game/Platform.h"
#include "Game/Player.h"
#include "Game/Rope.h"
#include "Game/Spikes.h"
#include "Game/Swordman.h"
#include "Game/Water.h"

/// \brief Класс мира.
/// \details Хранит физический мир, платформы, объекты взаимодействия,
/// существ. Предоставляет фабричные методы добавления новых объектов.
/// Отвечает за обновление мира.
/// \note Это класс-одиночка.
class World
{
public:
    ~World();
    /// \brief Ссылка на объект мира. (не физического, а вообще)
    static World& instance();

    /// \brief Метод добавления платформы.
    Platform& createPlatform();

    /// \brief Метод добавления лестницы.
    Ladder& createLadder();

    /// \brief Метод добавления водоема.
    Water& createWater();

    /// \brief Метод добавления лавового озера.
    Lava& createLava();

    /// \brief Метод добавления лучника.
    Archer& createArcher();

    /// \brief Возвращает ссылку на игрока.
    /// \note Вы можете использовать Player::instance() вместо этого
    /// метода.
    Player& player();

    /// \brief Возвращает константный список всех платформ.
    const std::list<Platform>& platforms() const;

    /// \brief Возвращает константный список всех лестниц.
    const std::list<Ladder>& ladders() const;

    /// \brief Возвращает константный список всех водоемов.
    const std::list<Water>& waters() const;

    /// \brief Возвращает константный список всех лавовых озер.
    const std::list<Lava>& lavas() const;

    /// \brief Возвращает константный список всех лучников.
    const std::list<Archer>& archers() const;

    /// \brief Обновляет мир.
    void update();

private:
    World();

    World(const World&) = delete;
    void operator= (const World&) = delete;

    /// \brief Создает физическое тело для существ.
    b2Body* createBodyForEntity();

    /// \brief Создает физическое тело для игрока.
    void createPlayer();

    std::list<Platform> _platforms; ///< список всех платформ

    std::list<Ladder> _ladders; ///< список всех лестниц

    std::list<Water> _waters; ///< список всех водоемов
    std::list<Lava> _lavas; ///< список всех лавовых озер

    std::list<Archer> _archers; ///< список всех лучников

    b2World* _world; ///< физический мир
};

#endif // WORLD_H
