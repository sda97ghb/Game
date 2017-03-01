/// \file
/// \brief Содержит класс воды.

#ifndef WATER_H
#define WATER_H

//#include "Game/Liquid.h"

#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"

class Water //: public Liquid
{
public:
    void setShape(const b2PolygonShape& shape);

    void setTextureBack(const std::string& filename);

    void setTextureFront(const std::string& filename);

    void testPlayerOnIt();

    /// \brief Физический многоугольник воды.
    b2PolygonShape& shapeB2();
    /// \brief Физический многоугольник воды.
    const b2PolygonShape& shapeB2() const;

    /// \brief Графический многоугольник воды.
    sf::ConvexShape& shapeSF();
    /// \brief Графический многоугольник воды.
    const sf::ConvexShape& shapeSF() const;

    /// \brief Текстура воды.
    sf::Texture& textureBack();
    /// \brief Текстура воды.
    const sf::Texture& textureBack() const;

    /// \brief Текстура воды.
    sf::Texture& textureFront();
    /// \brief Текстура воды.
    const sf::Texture& textureFront() const;

private:
    b2PolygonShape _shapeB2;
    sf::ConvexShape _shapeSF;
    sf::Texture _textureBack;
    sf::Texture _textureFront;
};

#endif // WATER_H
