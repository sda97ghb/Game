#ifndef GLOBALCONSTANTS_H
#define GLOBALCONSTANTS_H

#include <cstdint>

#include "Box2D/Common/b2Math.h"

// -------- Physics constants -------- //

static const float g = 9.8f;
static const b2Vec2 GRAVITY_VECTOR = b2Vec2(0.0f, -::g);

// -------- Graphic constants -------- //

static const uint32_t SCREEN_RESOLUTION_X = 1280;
static const uint32_t SCREEN_RESOLUTION_Y = 720;

static const float PIXELART_SCALE_FACTOR = 5.0f;

static const float PIXELS_PER_METER = 5.0f;

#endif // GLOBALCONSTANTS_H
