#ifndef TESTPLAYER_H
#define TESTPLAYER_H

#include "Game/TestEntity.h"

class TestPlayer : public TestEntity
{
public:
    static TestPlayer& instance();

    float width() const;
    float height() const;

private:
    TestPlayer();
    TestPlayer(const TestPlayer&) = delete;
    void operator= (const TestPlayer&) = delete;
};

#endif // TESTPLAYER_H
