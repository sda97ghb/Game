/// \file
/// \brief Содержит класс воды.

#ifndef WATER_H
#define WATER_H

#include "Arena/Furniture/Liquid.h"

class b2Body;

/// \brief Класс водоема.
class Water : public Liquid
{
public:
    /// \brief Плавание игрока в воде
    void testPlayerOnIt();

private:
    bool testBody(b2Body& body);
};

#endif // WATER_H
