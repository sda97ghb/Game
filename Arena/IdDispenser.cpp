#include "Arena/IdDispenser.h"

uint32_t IdDispenser::getNewId()
{
    static int lastId = 1;
    return lastId++;
}
