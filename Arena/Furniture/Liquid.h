/// \file
/// \brief Содержит базовый класс жидкости.

#ifndef LIQUID_H
#define LIQUID_H

#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"

#include "Arena/Furniture/Furniture.h"

/// \brief Базовый класс жидкости.
class Liquid : public Furniture
{
public:
    /// \brief Устанавливает форму водоема с жидкостью.
    void setShape(const b2PolygonShape& shape);

    /// \brief Устанавливает текстуру подложки.
    void setTextureBack(const std::string& filename);

    /// \brief Устанавливает текстуру жидкости, которая рисуется над объектами.
//    void setTextureFront(const std::string& filename);

    /// \brief Метод взаимодействия с игроком, например плавание для воды.
    virtual void testPlayerOnIt() = 0;

    /// \brief Физический многоугольник жидкости.
    b2PolygonShape& shapeB2();
    /// \brief Физический многоугольник жидкости.
    const b2PolygonShape& shapeB2() const;

    /// \brief Графический многоугольник жидкости.
    sf::ConvexShape& shapeSF();
    /// \brief Графический многоугольник жидкости.
    const sf::ConvexShape& shapeSF() const;

    /// \brief Текстура подложки жидкости.
    sf::Texture& textureBack();
    /// \brief Текстура подложки жидкости.
    const sf::Texture& textureBack() const;

    /// \brief Текстура жидкости.
//    sf::Texture& textureFront();
    /// \brief Текстура жидкости.
//    const sf::Texture& textureFront() const;

protected:
    b2PolygonShape _shapeB2;   ///< Физическая форма жидкости
    sf::ConvexShape _shapeSF;  ///< Графический многоугольник жидкости
    sf::Texture _textureBack;  ///< Текстура подложки
//    sf::Texture _textureFront; ///< Текстура жидкости
};

#endif // LIQUID_H
