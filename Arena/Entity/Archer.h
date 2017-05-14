#ifndef ARCHER_H
#define ARCHER_H

#include "Arena/Entity/Animalia.h"
#include "Arena/Entity/ComplexStateMachine.h"

#include "Arena/Sensors/AbyssSensor.h"
#include "Arena/Sensors/ContactSensor.h"
#include "Arena/Sensors/HitSensor.h"
#include "Arena/Sensors/PlayerSensor.h"
#include "Arena/Sensors/TimerSensor.h"

/// @brief Класс лучника. Отвечает только за логику, но не за создание
/// или отображение.
class Archer : public Animalia, public ComplexStateMachine
{
    friend class ArcherBuilderSpawner;
    friend class ArcherView;

public:
    EVENT(bump)             ///< столкновение с левым или правым объектом
    EVENT(gotSightOfPlayer) ///< увидел игрока
    EVENT(groundHit)        ///< сильно ударился о землю
    EVENT(landing)          ///< приземлился на землю
    EVENT(lostSightOfPlayer)///< потерял игрока из виду
    EVENT(readyToStrike)    ///< готов к совершению выстрела
    EVENT(strike)           ///< совершил выстрел
    EVENT(wentButNotFound)  ///< дошел до места, где последний раз видел игрока

    Archer();
    ~Archer();

private:
    /// @brief погоня за игроком
    STATE(chasing) // required() incompatible(lookingAround, preparingToStrike)

    /// @brief прыжок
    STATE(jumping) // required() incompatible(preparingToStrike)

    /// @brief неактивен, стоит смотрит по сторонам
    STATE(lookingAround) // required() incompatible(chasing, preparingToStrike)

    /// @brief готовится к выстрелу, натягивает тетиву
    STATE(preparingToStrike) // required() incompatible(chaising, jumping, lookingAround)

    /// @brief Совершит прыжок, если сможет.
    void tryToJump();

    /// @brief Пойдет влево,если сможет.
    void tryToMoveLeft();

    /// @brief Пойдет вправо, если сможет.
    void tryToMoveRight();

    /// @brief Обработчик события столкновения в левым или правым объектом.
    void onBump();

    /// @brief Обработчик события сильного удара о землю.
    /// @param [in] speed скорость непосредственнно перед столкновением
    void onGroundHit(float speed);

    /// @brief Обработчик события приземления
    void onLanding();

    /// @brief Обработчик события, когда увидел игрока
    void onGotSightOfPlayer();

    /// @brief Обработчик события, когда потерял игрока из виду
    void onLostSightOfPlayer();

    /// @brief Обработчик события обновления.
    void onUpdate();

    /// @brief Обработчик события, когда дошел до места, где последний раз
    /// сидел игрока.
    void onWentButNotFound();

    /// @brief Начать готовиться к выстрелу.
    void prepareToStrike();

    /// @brief Обработчик состояния подготовки к выстрелу.
    void preparingToStrike();

    /// @brief Совершить выстрел.
    void strike();

    /// @brief Обработчик состояния погони.
    void chasing();

    /// @brief Высота прыжка.
    float jumpHeight() const;

    /// @brief Скорость бега.
    float movementSpeed() const;

    /// @brief Обработчик состояния, когда неактивен, стоит смотрит по сторонам.
    void lookingAround();

    /// @brief Обработчик события смерти.
    void onDeath();

    AbyssSensor* _abyssSensor;           ///< датчик пропасти впереди
    ContactSensor* _leftContactSensor;   ///< датчик контакта с левым объектом
    ContactSensor* _rightContactSensor;  ///< датчик контакта с правым объектом
    ContactSensor* _groundContactSensor; ///< датчик контакта с землей
    HitSensor* _groundHitSensor;         ///< датчик сильного удара о землю
    HitSensor* _landingSensor;           ///< датчик приземления
    HitSensor* _leftBumpSensor;          ///< датчик столкновения с левым объектом
    HitSensor* _rightBumpSensor;         ///< датчик столкновения с правым объектом
    PlayerSensor* _playerSensor;         ///< датчик игрока
    TimerSensor* _reloadSensor;          ///< датчик перезарядки

    b2Vec2 _lastKnownPlayerLocation; ///< место, где последний раз видел игрока
};

#endif // ARCHER_H
