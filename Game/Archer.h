#ifndef ARCHER_H
#define ARCHER_H

#include "Game/Enemy.h"

class Archer : public Enemy
{
public:
    Archer();

    float width() const;
    float height() const;

    void update();

private:
    Archer(const Archer& archer) = delete;
    void operator= (const Archer& archer) = delete;
};

#endif // ARCHER_H
