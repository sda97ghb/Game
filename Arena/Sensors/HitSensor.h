/// @file
/// @brief Содержит класс датчика удара.

#ifndef HITSENSOR_H
#define HITSENSOR_H

#include <functional>

class b2Body;

/// @brief Сенсор столкновения с другим объектом. (Не путать с ContactSensor)
/// @details Создает для указанного тела новую фигуру (прямоугольник),
/// чувствительную к взаимодейтвию с другим телом и регистрируется в классе
/// SensorsListener. В отличии от ContactSensor срабатывает только
/// в момент столкновения и не умеет проверять существавание контакта
/// в текущий момент.
/// @note Для работы с этим датчиком унаследуйте свой класс от Entity или
/// производных от него.
class HitSensor
{
    friend class HitSensorBuilder;

public:
    using OnHitCallback = std::function<void(float)>;

    ~HitSensor();

    /// @brief Ударяет сенсор с указанной скоростью.
    /// @param [in] speed скорость сенсора относительно препятствия в момент удара
    /// @note В норме должен вызываться только из класса SensorListener,
    /// но вызов из других мест не должен привести к ошибкам.
    void hit(float speed);

    /// @brief Возвращает тип датчика.
    int type() const;

    /// @brief Возвращает указатель на тело, на которое повешан датчик.
    const b2Body* body() const;

    OnHitCallback onHitCallback() const;

private:
    HitSensor();

    int _type; ///< Тип датчика.

    float _activationThreshold; ///< Порог воздействия, необходимый для активации датчика
    bool _requireActivationThreshold; ///< Требовать, чтобы для активации сила воздействия на сенсор была больше порогового значения.

    b2Body* _body; ///< Тело, на которое повешан датчик.

    OnHitCallback _onHitCallback;
};

#endif // HITSENSOR_H
