#ifndef COORDINATETRANSLATION_H
#define COORDINATETRANSLATION_H

#include "SFML/System/Vector2.hpp"

#include "Box2D/Common/b2Math.h"

namespace translate {
    const float SCREEN_PER_PHYSICAL = 32.0f;
    // texture 16px == screen 32px == physical 1m

    // Point - Pos
    // Size - Size
    // Physical - P
    // Screen - S
    // int - i
    // float - f
    // to - 2 
    // Physical float point to screen int point - PosPf2Si

    sf::Vector2f PosPf2Sf(const b2Vec2& pos);
    sf::Vector2i PosPf2Si(const b2Vec2& pos);

    sf::Vector2f SizePf2Sf(const b2Vec2& pos);
    sf::Vector2i SizePf2Si(const b2Vec2& pos);

    float SizePf2Sf(float size);
    int   SizePf2Si(float size);
}

#endif // COORDINATETRANSLATION_H
