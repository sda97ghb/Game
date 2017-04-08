/// \file
/// \brief Содержит класс мира.

#ifndef WORLD_H
#define WORLD_H

#include <list>

#include "Box2D/Dynamics/b2World.h"

#include "Arena/Platform.h"

//#include "Arena/Entity/Player.h"
#include "Arena/Entity/LivingEntity.h"

#include "Arena/Furniture/Cable.h"
#include "Arena/Furniture/FallingGround.h"
#include "Arena/Furniture/Ladder.h"
#include "Arena/Furniture/Lava.h"
#include "Arena/Furniture/Rope.h"
#include "Arena/Furniture/Spikes.h"
#include "Arena/Furniture/Water.h"

/// \brief Класс мира.
/// \details Хранит физический мир, платформы, объекты взаимодействия,
/// существ. Предоставляет фабричные методы добавления новых объектов.
/// Отвечает за обновление мира.
/// \note Это класс-одиночка.
class World
{
public:
    /// @brief Ссылка на объект физической модели мира.
    static b2World& physical();

    /// \brief Ссылка на объект мира. (не физического, а вообще)
    static World& instance();

    void addEntity(LivingEntity* entity);

    /// \brief Метод добавления платформы.
    Platform& createPlatform();

    /// \brief Метод добавления лавового озера.
    Cable& createCable();

    /// \brief Метод добавления лестницы.
    Ladder& createLadder();

	/// \brief Метод добавления водоема.
	Water& createWater();

    /// \brief Метод добавления лавового озера.
    Lava& createLava();
	
	/// \brief Метод добавления шипов.
	Spikes& createSpikes();

    /// \brief Возвращает константный список всех платформ.
    const std::list<Platform>& platforms() const;

    /// \brief Возвращает константный список всех тросов.
    const std::list<Cable>& cable() const;

    /// \brief Возвращает константный список всех лестниц.
    const std::list<Ladder>& ladders() const;

	/// \brief Возвращает константный список всех водоемов.
	const std::list<Water>& waters() const;

    /// \brief Возвращает константный список всех лавовых озер.
    const std::list<Lava>& lavas() const;

	/// \brief Возвращает константный список всех шипов.
	const std::list<Spikes>& spikes() const;

//    /// \brief Возвращает ссылку на игрока.
//    /// \note Вы можете использовать Player::instance() вместо этого
//    /// метода.
//    Player& player();

    /// \brief Обновляет мир.
    void update();

private:
    World();

    World(const World&) = delete;
    void operator= (const World&) = delete;

    std::list<Platform> _platforms; ///< список всех платформ

    std::list<Cable> _cables; ///< список всех тросов
    std::list<Ladder> _ladders; ///< список всех лестниц

	std::list<Water> _waters; ///< список всех водоемов
    std::list<Lava> _lavas; ///< список всех лавовых озер
	std::list<Spikes> _spikes; ///< список всех шипов

    std::list<LivingEntity*> _entities;
};

#endif // WORLD_H
