/// \file
/// \brief Содержит класс датчика удара.

#ifndef HITSENSOR_H
#define HITSENSOR_H

#include <functional>

#include "Box2D/Dynamics/b2Body.h"

class Entity;

/// \brief Сенсор столкновения с другим объектом. (Не путать с ContactSensor)
/// \details Создает для указанного тела новую фигуру (прямоугольник),
/// чувствительную к взаимодейтвию с другим телом и регистрируется в классе
/// SensorsListener. В отличии от ContactSensor срабатывает только
/// в момент столкновения и не умеет проверять существавание контакта
/// в текущий момент.
/// \note Для работы с этим датчиком унаследуйте свой класс от Entity или
/// производных от него.
class HitSensor
{
public:
    using OnHitCallback = std::function<void(float)>;

    HitSensor();

    /// \brief Устанавливает координаты центра сенсора.
    /// \warning Должен быть вызван раньше, чем hangOnBody(b2Body* body).
    void setPosition(float x, float y);

    /// \brief Устанавливает размеры сенсора.
    /// \warning Должен быть вызван раньше, чем hangOnBody(b2Body* body).
    void setSize(float width, float height);

    /// \brief Устанавливает тип сенсора.
    /// \details Нужно, чтобы различать сенсоры повешанные на одно тело.
    /// \param [in] type тип сенсора, например SensorsListener::GROUND_HIT_SENSOR_TYPE
    /// или произвольное целое.
    /// \warning У одного тела не должно быть несколько сенсоров одинакового типа.
    /// \warning Должен быть вызван раньше, чем hangOnBody(b2Body* body).
    void setType(int type);

    /// \brief Устанавливает уровень воздействия на сенсор, необходимый для
    /// его активации.
    /// \param [in] value необходимая скорость сенсора в момент удара
    void setActivationThreshold(float value);

    /// \brief Вешает сенсор на указанное тело.
    /// \details Запоминает указанное телов в _body, создает для него
    /// фигуру-сенсор, регистрирует сенсор в SensorsListener.
    /// \warning Должен быть вызвано один раз для одного тела.
    /// \warning При повторном вызове для разных тел датчик не будет снят
    /// с предыдущего тела.
    /// \note Указанное тело не обязательно должно принадлежать существу,
    /// указанному ранее.
    void hangOnBody(b2Body* body);

    /// \brief Ударяет сенсор с указанной скоростью.
    /// \param [in] speed скорость сенсора относительно препятствия в момент удара
    /// \note В норме должен вызываться только из класса SensorListener,
    /// но вызов из других мест не должен привести к ошибкам.
    void hit(float speed);

    /// \brief Возвращает тип датчика.
    int type() const;

    /// \brief Возвращает указатель на тело, на которое повешан датчик.
    const b2Body* body() const;

    OnHitCallback onHitCallback() const;
    void setOnHitCallback(const OnHitCallback& onHitCallback);

    void setRequireActivationThreshold(bool requireActivationThreshold);

private:
    float _x; ///< Позиция центра датчика по x.
    float _y; ///< Позиция центра датчика по y.
    float _width;  ///< Ширина датчика.
    float _height; ///< Высота датчика.

    int _type; ///< Тип датчика.

    float _activationThreshold; ///< Порог воздействия, необходимый для активации датчика
    bool _requireActivationThreshold; ///< Требовать, чтобы для активации сила воздействия на сенсор была больше порогового значения.

    b2Body* _body; ///< Тело, на которое повешан датчик.

    OnHitCallback _onHitCallback;
};

#endif // HITSENSOR_H
