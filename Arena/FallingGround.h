/// \file
/// \brief Содержит класс земли, обваливающейся при падении.

#ifndef FALLINGGROUND_H
#define FALLINGGROUND_H

#include <list>

#include "Box2D/Common/b2Math.h"

#include "Arena/Furniture.h"

class FallingGround : public Furniture
{
public:
    void setPosition(float x, float y);
    void setShape(std::list<b2Vec2> vertexes);

    void testPlayerOnIt();

    float x() const;
    float y() const;

private:
    float _x;
    float _y;
};

#endif // FALLINGGROUND_H
