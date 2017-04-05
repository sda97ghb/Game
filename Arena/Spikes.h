/// \file
/// \brief Содержит класс шипов.

#ifndef SPIKES_H
#define SPIKES_H

#include "SFML/Graphics/RectangleShape.hpp"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"

#include "Arena/Furniture.h"
#include "Arena/ContactSensor.h"

class Spikes : public Furniture
{
public:
    void setBegin(float x, float y);
    void setEnd(float x, float y);

    Spikes();

    void setCoordinates(float x1, float y1, float x2, float y2);
    void setHeight(float height);
    void testPlayerOnIt();

    float x1() const;
    float x2() const;
    float y1() const;
    float y2() const;

    float height() const;
    float lenght() const;
    float sign(float sign) const;
    float angle() const;

    /// \brief Физическая фигура шипов.
    b2PolygonShape& shapeB2();
    const b2PolygonShape& shapeB2() const;

    /// \brief Графическая фигура шипов.
    sf::RectangleShape& shapeSF();
    const sf::RectangleShape& shapeSF() const;

private:
    void setShape();
 
    float _x1;
    float _y1;
    float _x2;
    float _y2;
    float _height;

    b2PolygonShape _shapeB2;
    sf::RectangleShape _shapeSF;
    ContactSensor _sensor;
    b2Body* _body;
};

#endif // SPIKES_H
