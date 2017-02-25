#include "Game/CoordinateTranslation.h"

sf::Vector2f translate::PosPf2Sf(const b2Vec2& pos)
{
    return sf::Vector2f(  pos.x * SCREEN_PER_PHYSICAL,
                        - pos.y * SCREEN_PER_PHYSICAL);
}

sf::Vector2i translate::PosPf2Si(const b2Vec2& pos)
{
    return sf::Vector2i(  static_cast<int>(floor(pos.x * SCREEN_PER_PHYSICAL)),
                        - static_cast<int>(floor(pos.y * SCREEN_PER_PHYSICAL)));
}

sf::Vector2f translate::SizePf2Sf(const b2Vec2& pos)
{
    return sf::Vector2f(pos.x * SCREEN_PER_PHYSICAL,
                        pos.y * SCREEN_PER_PHYSICAL);
}

sf::Vector2i translate::SizePf2Si(const b2Vec2& pos)
{
    return sf::Vector2i(static_cast<int>(floor(pos.x * SCREEN_PER_PHYSICAL)),
                        static_cast<int>(floor(pos.y * SCREEN_PER_PHYSICAL)));
}

float translate::SizePf2Sf(float size)
{
    return size * SCREEN_PER_PHYSICAL;
}

int translate::SizePf2Si(float size)
{
    return static_cast<int>(round(size * SCREEN_PER_PHYSICAL));
}
