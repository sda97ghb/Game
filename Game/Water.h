/// \file
/// \brief Содержит класс воды.

#ifndef WATER_H
#define WATER_H

#include "Game/Liquid.h"

/// \brief Класс водоема.
class Water : public Liquid
{
public:
    /// \brief Плавание игрока в воде
    void testPlayerOnIt();
};

#endif // WATER_H
