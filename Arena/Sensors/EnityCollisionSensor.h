#ifndef ENITYCOLLISIONSENSOR_H
#define ENITYCOLLISIONSENSOR_H

#include <functional>

class b2Body;

class Entity;

/// @brief Сенсор столкновения с другим муществом.
class EnityCollisionSensor
{
public:
    using OnCollisionCallback = std::function<void(Entity*)>;

    EnityCollisionSensor();
    ~EnityCollisionSensor();

    void setPosition(float x, float y);

    void setSize(float width, float height);

    void setType(int type);

    void hangOnBody(b2Body* body);

    void hit(b2Body* body);

    void setOnCollisionCallback(const OnCollisionCallback& callback);

    int type() const;

    b2Body* body() const;

private:
    float _x;
    float _y;
    float _width;
    float _height;

    int _type;

    b2Body* _body;

    OnCollisionCallback _onCollisionCallback;
};

#endif // ENITYCOLLISIONSENSOR_H
