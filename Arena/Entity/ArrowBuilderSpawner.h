#ifndef ARROWBUILDERSPAWNER_H
#define ARROWBUILDERSPAWNER_H

#include "Arena/Entity/Arrow.h"

/// @brief Класс-построитель стрелы.
class ArrowBuilderSpawner
{
public:
    ArrowBuilderSpawner();

    ArrowBuilderSpawner& setPosition(const b2Vec2& position);
    ArrowBuilderSpawner& setPosition(float x, float y);
    ArrowBuilderSpawner& setTarget(const b2Vec2& target);
    ArrowBuilderSpawner& setTarget(float x, float y);
    ArrowBuilderSpawner& setDirection(float angle);
    ArrowBuilderSpawner& setSpeed(float speed);
    ArrowBuilderSpawner& setDamage(float damage);

    void spawn();

private:
    float width() const;
    float height() const;

    b2Body* body();

    void createBody();
    void constructBody();
    void constructSensors();

    Arrow* _arrow;

    b2Vec2 _position;
    b2Vec2 _target;
    float _angle;
    float _speed;
    float _damage;

    enum class LaunchMode
    {
        angle,
        target
    } _launchMode;
};

#endif // ARROWBUILDERSPAWNER_H
