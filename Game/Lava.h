/// \file
/// \brief Содержит класс лавы.

#ifndef LAVA_H
#define LAVA_H

#include "Game/Liquid.h"

/// \brief Класс лавового озера.
class Lava : public Liquid
{
public:
    /// \brief Смерть игрока при контакте с лавой.
    void testPlayerOnIt();
};

#endif // LAVA_H
