/// \file
/// \brief Содержит класс троса.

#ifndef CABLE_H
#define CABLE_H

#include "Game/Furniture.h"

class Cable : public Furniture
{
public:
    void setBegin(float x, float y);
    void setEnd(float x, float y);

    void testPlayerOnIt();

    float x1() const;
    float x2() const;
    float y1() const;
    float y2() const;

private:
    float _x1;
    float _x2;
    float _y1;
    float _y2;
};

#endif // CABLE_H
