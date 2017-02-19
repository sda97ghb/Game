#include "CoordinateTranslation.h"

sf::Vector2f physicalToScreen(const b2Vec2& pos)
{
    return sf::Vector2f(pos.x * SCREEN_PER_PHYSICAL,
                        pos.y * SCREEN_PER_PHYSICAL);
}

b2Vec2 screenToPhysical(const sf::Vector2f& pos)
{
    return b2Vec2(pos.x / SCREEN_PER_PHYSICAL,
                  pos.y / SCREEN_PER_PHYSICAL);
}

float physicalToScreen(float size)
{
    return size * SCREEN_PER_PHYSICAL;
}

float screenToPhysical(float size)
{
    return size / SCREEN_PER_PHYSICAL;
}
