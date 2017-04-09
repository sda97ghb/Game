#ifndef ARCHERBUILDERSPAWNER_H
#define ARCHERBUILDERSPAWNER_H

#include "Arena/Entity/Archer.h"

class ArcherBuilderSpawner
{
public:
    ArcherBuilderSpawner();

    ArcherBuilderSpawner& setPosition(const b2Vec2& position);
    ArcherBuilderSpawner& setPosition(float x, float y);

    void spawn();

private:
    float width() const;
    float height() const;

    b2Body* body();

    void createBody();
    void constructBody();
    void constructSensors();

    Archer* _archer;

    b2Vec2 _position;
};

#endif // ARCHERBUILDERSPAWNER_H
