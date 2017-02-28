/// \file
/// \brief Содержит класс болтающейся веревки.

#ifndef ROPE_H
#define ROPE_H

#include "Game/Furniture.h"

class Rope : public Furniture
{
public:
    void setPosition(float x, float y);
    void setLength(float length);

    float x() const;
    float y() const;

    float length() const;

private:
    float _x;
    float _y;
    float _length;
};

#endif // ROPE_H
