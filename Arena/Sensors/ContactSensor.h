/// \file
/// \brief Содержит класс датчика контакта.

#ifndef CONTACT_SENSOR_H
#define CONTACT_SENSOR_H

class b2Body;

/// \brief Класс сенсора, реагирующего на контакт с другим телом.
/// (Не путать с HitSensor)
/// \details Создает для указанного тела новую фигуру (прямоугольник)
/// чувствительную к взаимодействию с другим телом и регистрируется в классе
/// SensorsListener. Для проверки наличия взаимодействия вызовите метод isActive().
class ContactSensor
{
    friend class ContactSensorBuilder;

public:
    ~ContactSensor();

    /// \brief Устанавливает, активен ли сейчас датчик.
    /// \param [in] state true если активен, иначе false
    /// \note В норме должен вызываться только из класса SensorListener,
    /// но вызов из других мест не приведет к ошибкам.
    void set(bool state);

    /// \brief Возвращает состояние, активен ли сейчас датчик.
    bool isActive() const;

    /// \brief Возвращает тип датчика.
    int type() const;

    /// \brief Возвращает указатель на тело, на которое повешан датчик.
    const b2Body* body() const;

private:
    ContactSensor();

    bool _state; ///< Текущее состояние датчика.

    int _type; ///< Тип датчика.

    b2Body* _body; ///< Тело, на которое повешан датчик.
};

#endif // CONTACT_SENSOR_H
