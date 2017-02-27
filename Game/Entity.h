#ifndef ENTITY_H
#define ENTITY_H

#include "Box2D/Dynamics/b2Body.h"

#include "Game/ContactSensor.h"
#include "Game/HitSensor.h"
#include "Game/SpriteAnimator.h"

/// Базовый класс для всех существ.
/// \attention Не наследуйтесь напрямую от этого класса, если вы разрабатывает
/// существо, враждебное к игроку, используйте класс Enemy.
class Entity
{
public:
    struct NoBodyException : public std::logic_error {
        NoBodyException() : std::logic_error("there is no body for the shape") {}
    };

    struct NoFixtureException : public std::logic_error {
        NoFixtureException() : std::logic_error("there is no fixture for the platform") {}
    };

    struct NoShapeException : public std::logic_error {
        NoShapeException() : std::logic_error("there is no shape for the platform") {}
    };

    Entity();

    /// \brief Установка координат центра масс существа.
    /// \details Координтаты задаются в физических координатах.
    void setPosition(float x, float y);

    /// \brief Возвращает координаты нижней границы существа в физических координатах.
    b2Vec2 footPosition() const;

    /// \brief Физическая ширина существа.
    virtual float width() const = 0;

    /// \brief Физическая высота существа.
    virtual float height() const = 0;

    b2PolygonShape& shape();
    const b2PolygonShape& shape() const;

    b2Body& body();
    const b2Body& body() const;

    /// \brief Делает шаг влево.
    /// \details Если скорость существа по горизонтали по модулю меньше
    /// максимальной разрешенной прикладывает импульс, направленный влево.
    void stepLeft();

    /// \brief Делает шаг вправо.
    /// \details Если скорость существа по горизонтали по модулю меньше
    /// максимальной разрешенной прикладывает импульс, направленный вправо.
    void stepRight();

    /// \brief Делает прыжок.
    /// \details Если существо касается нижней поверхностью платформы
    /// прикладывает импульс необходимый для прыжка.
    void jump();

    /// \brief Обработчик события удара по сенсору удара.
    /// \param [in] sensorType тип сенсора,
    /// например SensorsListener::GROUND_HIT_SENSOR_TYPE или произвольное целое
    /// \param [in] speed скорость сенсора относительно препятствия в момент столкновения
    void hit(int sensorType, float speed);

    /// \brief Вызывает функцию для текущего состояния существа.
    virtual void update() = 0;

    /// \brief Устанавливает максимальный уровень здоровья
    /// \param [in] value новый максимальный уровень здоровья
    void setMaxHealth(float value);

    /// \brief Устанавливает текущий уровень здоровья
    /// \param [in] value новый текущий уровень здоровья
    void setHealth(float value);

    /// \brief Наносит урон (отнимает здоровье).
    /// \param [in] количество отнимаемого здоровья
    void makeDamage(float value);

    /// \brief Лечит (добавляет здоровье).
    /// \param [in] value количество добавляемого здоровья
    /// \note Не может увеличить здоровье выше максимально возможного уровня.
    void heal(float value);

    /// \brief Мгновенно убивает существо.
    /// \details Мгновенно уменьшает здоровье до 0.
    void kill();

    /// \brief Устанавливает новый максимальный уровень маны.
    /// \param [in] value новый максимальный уровень маны
    void setMaxMana(float value);

    /// \brief Устанавливает новый текущий уровень маны.
    /// \param [in] value новый текущий уровень маны
    void setMana(float value);

    /// \brief Проверяет живое ли существо.
    /// \details Возвращает true если уровень здоровья больше нуля.
    bool isAlive() const;

    /// \brief Возвращает максимальный уровень здоровья.
    float maxHealth() const;

    /// \brief Возвращает максимальный уровень маны.
    float maxMana() const;

    /// \brief Возвращает текущий уровень здоровья.
    float health() const;

    /// \brief Возвращает текущий уровень маны.
    float mana() const;

    /// \brief Возвращает аниматор для этого существа.
    /// \details Более подробно описан в классе SpriteAnimator.
    SpriteAnimator& spriteAnimator();

protected:
    b2Body* _body; ///< физическое тело существа
    SpriteAnimator _spriteAnimator; ///< аниматор существа

    float _maxHealth; ///< максимальный уровень здоровья
    float _health; ///< текущий уровень здоровья

    float _maxMana; ///< максимальный уровень маны
    float _mana; ///< текущий уровень маны

    ContactSensor _groundSensor; ///< сенсор контакта с землей
    ContactSensor _leftSensor;   ///< левый сенсор контакта
    ContactSensor _rightSensor;  ///< правый сенсор контакта

    HitSensor _groundHitSensor; ///< сенсор удара нижней поверхности

private:
    // Разрешение для класса World использовать методы setBody и constructBody.
    friend class World;

    /// \brief Устанавливает _body для Entity.
    /// \attention Этот метод должен быть вызван только в классе World при создании существа.
    void setBody(b2Body* body);

    /// \brief Создает b2Shape для тела. Конструирует и вешает датчики на тело.
    /// \attention Этот метод должен быть вызван только в классе World
    /// после метода setBody(b2Body* body).
    void constructBody();

};

#endif //ENTITY_H
