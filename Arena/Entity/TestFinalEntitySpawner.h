#ifndef TESTFINALENTITYSPAWNER_H
#define TESTFINALENTITYSPAWNER_H

#include "Arena/Entity/TestFinalEntity.h"

class TestFinalEntityBuilderSpawner
{
public:
    TestFinalEntityBuilderSpawner();

    TestFinalEntityBuilderSpawner&
    setPosition(const b2Vec2& position);

    TestFinalEntityBuilderSpawner&
    setPosition(float x, float y);

    void spawn();

private:
    float width() const;
    float height() const;

    b2Body* body();

    void createBody();
    void constructBody();
    void constructSensors();

    TestFinalEntity* _entity;

    b2Vec2 _position;
};

#endif // TESTFINALENTITYSPAWNER_H
