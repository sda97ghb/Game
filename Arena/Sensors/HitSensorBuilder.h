#ifndef HITSENSORBUILDER_H
#define HITSENSORBUILDER_H

#include <cstdint>
#include <functional>

class b2Body;

class HitSensor;

class HitSensorBuilder
{
public:
    using OnHitCallback = std::function<void(float)>;

    HitSensorBuilder();

    HitSensorBuilder& setType(uint32_t type);
    HitSensorBuilder& setPosition(float dx, float dy);
    HitSensorBuilder& setSize(float width, float height);
    HitSensorBuilder& setActivationThreshold(float speed);
    HitSensorBuilder& setOnHitCallback(const OnHitCallback& callback);
    HitSensorBuilder& setBody(b2Body* body);
    HitSensorBuilder& setRequireActivationThreshold(bool flag);

    HitSensor* build();

private:
    float _dx; ///< Позиция центра датчика по x.
    float _dy; ///< Позиция центра датчика по y.
    float _width;  ///< Ширина датчика.
    float _height; ///< Высота датчика.

    uint32_t _type; ///< Тип датчика.

    float _activationThreshold; ///< Порог воздействия, необходимый для активации датчика
    bool _requireActivationThreshold; ///< Требовать, чтобы для активации сила воздействия на сенсор была больше порогового значения.

    b2Body* _body; ///< Тело, на которое повешан датчик.

    OnHitCallback _onHitCallback;
};

#endif // HITSENSORBUILDER_H
