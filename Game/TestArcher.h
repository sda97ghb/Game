#ifndef TESTARCHER_H
#define TESTARCHER_H

#include "Game/TestEntity.h"

class TestArcher : public TestEntity
{
public:
    TestArcher();

    float width() const;
    float height() const;

private:
    TestArcher(const TestArcher& archer) = delete;
    void operator= (const TestArcher& archer) = delete;
};

#endif // TESTARCHER_H
