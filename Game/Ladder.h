#ifndef LADDER_H
#define LADDER_H

#include "Game/Furniture.h"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Texture.hpp"

class Ladder : public Furniture
{
public:
    Ladder();

    void setCoordinates(float x, float y1, float y2);
    void setWidth(float width);
    void setTexture(const std::string& filename);

    void testPlayerOnIt();

    float x() const;
    float y1() const;
    float y2() const;

    float width() const;
    float height() const;

    b2Vec2 size() const;

    b2PolygonShape& shapeB2();
    const b2PolygonShape& shapeB2() const;
    sf::RectangleShape& shapeSF();
    const sf::RectangleShape& shapeSF() const;
    sf::Texture& texture();
    const sf::Texture& texture() const;

private:
    void setShape();

    float _x;
    float _y1;
    float _y2;
    float _width;

    b2PolygonShape _shapeB2;
    sf::RectangleShape _shapeSF;
    sf::Texture _texture;
};

#endif // LADDER_H
