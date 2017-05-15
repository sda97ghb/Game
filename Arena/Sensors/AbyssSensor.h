#ifndef ABYSSSENSOR_H
#define ABYSSSENSOR_H

#include "Arena/Direction.h"

class b2Body;

/// @brief Датчик пропасти впереди.
class AbyssSensor
{
    friend class AbyssSensorBuilder;

public:
    bool isActive();

    Direction direction() const;
    void setDirection(const Direction& direction);

private:
    AbyssSensor() = default;

    float _dx;
    float _dy;

    b2Body* _body;

    Direction _direction;
};

#endif // ABYSSSENSOR_H
