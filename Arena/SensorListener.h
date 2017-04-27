/// \file
/// \brief Содержит класс слушатель, ответственный за проверку
/// столкновений датчиков.

#ifndef SENSORLISTENER_H
#define SENSORLISTENER_H

#include "Box2D/Dynamics/b2WorldCallbacks.h"

/// \brief Класс, ответственный за срабатывание датчиков при столкновении.
/// \warning Этот класс нужен для внутренней механики игры.
/// Скорее всего вам не нужно ничего изменять в этом классе.
class SensorListener : public b2ContactListener
{
public:
    /// \brief Возвращает ссылку на объект класса.
    static SensorListener& instance();

private:
    SensorListener() = default;
    SensorListener(const SensorListener&) = delete;
    void operator= (const SensorListener&) = delete;

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
};

#endif // SENSORLISTENER_H
