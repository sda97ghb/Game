#ifndef COORDINATETRANSLATION_H
#define COORDINATETRANSLATION_H

#include "Box2D/Common/b2Math.h"
#include "SFML/System/Vector2.hpp"

namespace translate {
    static constexpr float SCREEN_PER_PHYSICAL = 30.0;

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
