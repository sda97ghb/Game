#ifndef IDDISPENSER_H
#define IDDISPENSER_H

#include <cstdint>

/// @brief Выдает новый уникальный id.
class IdDispenser
{
public:
    static uint32_t getNewId();
};

#endif // IDDISPENSER_H
