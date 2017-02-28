/// \file
/// \brief Содержит класс слушатель, ответственный за проверку
/// столкновений датчиков.

#ifndef SENSORLISTENER_H
#define SENSORLISTENER_H

#include <list>

#include "Box2D/Dynamics/b2WorldCallbacks.h"

#include "Game/ContactSensor.h"
#include "Game/HitSensor.h"

/// \brief Класс, ответственный за срабатывание датчиков при столкновении.
/// \warning Этот класс нужен для внутренней механики игры.
/// Скорее всего вам не нужно ничего изменять в этом классе.
class SensorsListener : public b2ContactListener
{
public:
    /// \brief Возвращает ссылку на объект класса.
    static SensorsListener& instance();

    enum
    {
        GROUND_CONTACT_SENSOR_TYPE = 1, ///< датчик нахождения на земле
        LEFT_CONTACT_SENSOR_TYPE   = 2, ///< датчик контакта с левым объектом
        RIGHT_CONTACT_SENSOR_TYPE  = 3, ///< датчик контакта с правым объектом
        GROUND_HIT_SENSOR_TYPE     = 4  ///< датчик удара о землю
    };

    /// \brief Регистрирует новый датчик контакта.
    /// \note Не создает копию сенсора.
    void registrySensor(ContactSensor& sensor);

    /// \brief Регистрирует новый датчик столкновения.
    /// \note Не создает копию сенсора.
    void registrySensor(HitSensor& sensor);

private:
    SensorsListener() = default;
    SensorsListener(const SensorsListener&) = delete;
    void operator= (const SensorsListener&) = delete;

    /// \brief Срабатывает при столкновении любых двух объектов.
    void BeginContact(b2Contact* contact);

    /// \brief Срабатывает при разлетании двух любых объектов.
    void EndContact(b2Contact* contact);

    /// \brief Переводит сенсор с указаннымим параметрами в указанное состояние.
    /// \param [in] body тело, на которое повешан датчик
    /// \param [in] type тип датчика на теле
    /// \param [in] value для активации true, для деактивации false
    void setSensor(b2Body* body, int type, bool value);

    /// \brief Вызывает метод удара для указанного сенсора.
    /// \param [in] body тело, на которое повешан датчик
    /// \param [in] type тип датчика на теле
    /// \param [in] speed скорость датчика в момент удара
    void hitSensor(b2Body* body, int type, float speed);

    std::list<ContactSensor*> _contactSensors; ///< список всех сенсоров контакта
    std::list<HitSensor*> _hitSensors; ///< список всех сенсоров столкновения
};

#endif // SENSORLISTENER_H
