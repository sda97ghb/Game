#ifndef COORDINATETRANSLATION_H
#define COORDINATETRANSLATION_H

#include "Box2D/Common/b2Math.h"
#include "SFML/System/Vector2.hpp"

static constexpr float SCREEN_PER_PHYSICAL = 30.0;

sf::Vector2f physicalToScreen(const b2Vec2& pos);
b2Vec2 screenToPhysical(const sf::Vector2f& pos);

float physicalToScreen(float size);
float screenToPhysical(float size);

#endif // COORDINATETRANSLATION_H
