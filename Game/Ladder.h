#ifndef LADDER_H
#define LADDER_H

#include "Game/Furniture.h"

class Ladder : public Furniture
{
public:
    void setCoordinates(float x, float y1, float y2);
    void setWidth(float width);

    void testPlayerOnIt();

    float x() const;
    float y1() const;
    float y2() const;

    float width() const;
    float height() const;

private:
    float _x;
    float _y1;
    float _y2;
    float _width;
};

#endif // LADDER_H
