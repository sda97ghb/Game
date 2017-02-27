#ifndef CONTACT_SENSOR_H
#define CONTACT_SENSOR_H

#include "Box2D/Dynamics/b2Body.h"

/// \brief Класс сенсора, реагирующего на контакт с другим телом.
/// \details Создает для указанного тела новую фигуру (прямоугольник)
/// чувствительную к взаимодействию с другим телом и регистрируется в классе
/// SensorListener. Для проверки наличия взаимодействия вызовите метод isActive().
class ContactSensor
{
public:
    ContactSensor();

    /// \brief Устанавливает координаты центра сенсора.
    /// \warning Должно быть вызвано раньше, чем hangOnBody(b2Body* body).
    void setPosition(float x, float y);

    /// \brief Устанавливает размер сенсора.
    /// \warning Должно быть вызвано раньше, чем hangOnBody(b2Body* body).
    void setSize(float width, float height);

    /// \brief Устанавливает тип сенсора.
    /// \details Нужно, чтобы различать сенсоры, повешенные на одно тело.
    /// \param [in] type тип сенсора, например SensorsListener::GROUND_CONTACT_SENSOR_TYPE
    /// или произвольное целое.
    /// \warning У одного тела не должно быть несколько сенсоров одного типа.
    /// \warning Должно быть вызвано раньше, чем hangOnBody(b2Body* body).
    void setType(int type);

    /// \brief Вешает сенсор на указанное тело.
    /// \details Запоминает указанное тело в _body.
    /// \warning Должно быть вызвано один раз для одного тела.
    /// \warning При повторном вызове для разных тел датчик не будет снят
    /// с предыдущего тела, но будет работать, как повешанный на последнее тело.
    void hangOnBody(b2Body* body);

    /// \brief Устанавливает, активен ли сейчас датчик.
    /// \param [in] state true если активен, иначе false
    /// \note В норме должен вызываться только из класса SensorListener,
    /// но вызов из других мест не приведет к ошибкам.
    void set(bool state);

    /// \brief Возвращает, активен ли сейчас датчик.
    bool isActive() const;

    /// \brief Возвращает тип датчика.
    int type() const;

    /// \brief Возвращает указатель на тело, на которое повешан датчик.
    const b2Body* body() const;

private:
    float _x; ///< Позиция центра датчика по x.
    float _y; ///< Позиция центра датчика по y.
    float _width;  ///< Ширина датчика.
    float _height; ///< Высота датчика.

    bool _state; ///< Текущее состояние датчика.
    int _type; ///< Тип датчика.

    b2Body* _body; ///< Тело, на которое повешан датчик.
};

#endif // CONTACT_SENSOR_H
