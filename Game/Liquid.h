#ifndef LIQUID_H
#define LIQUID_H

#include <list>

#include "Box2D/Common/b2Math.h"

#include "Game/Furniture.h"

class Liquid : public Furniture
{
public:
    void setShape(std::list<b2Vec2> vertexes);
private:
};

#endif // LIQUID_H
