#ifndef ARCHER_H
#define ARCHER_H

#include "Game/Entity.h"

class Archer : public Entity
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
