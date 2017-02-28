/// \file
/// \brief Содержит класс платформы.

#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdexcept>

#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"

/// \brief Класс платформы.
/// \details Многоугольник, функционирующий как земля или стена.
class Platform
{
public:
    struct NoBodyException : public std::logic_error {
        NoBodyException() : std::logic_error("there is no body for the shape") {}
    };

    struct NoFixtureException : public std::logic_error {
        NoFixtureException() : std::logic_error("there is no fixture for the platform") {}
    };

    struct NoShapeException : public std::logic_error {
        NoShapeException() : std::logic_error("there is no shape for the platform") {}
    };

    /// \brief Устанавливает физическое тело для платформы.
    /// \warning Вызывайте только один раз при создании платформы.
    void setBody(b2Body* body);

    /// \brief Устанавливает форму для платформы.
    /// \details Создает форму для указанного ранее тела.
    /// \warning Вызывайте только один раз при создании платформы.
    void setShape(const b2PolygonShape& shape);

    /// \brief Устанавливает текстуру для платформы.
    void setTexture(const std::string& filename);

    /// \brief Физический многоугольник платформы.
    b2PolygonShape& shapeB2();
    /// \brief Физический многоугольник платформы.
    const b2PolygonShape& shapeB2() const;

    /// \brief Физическое тело платформы.
    b2Body& body();
    /// \brief Физическое тело платформы.
    const b2Body& body() const;

    /// \brief Графический многоугольник платформы.
    sf::ConvexShape& shapeSF();
    /// \brief Графический многоугольник платформы.
    const sf::ConvexShape& shapeSF() const;

    /// \brief Текстура платформы.
    sf::Texture& texture();
    /// \brief Текстура платформы.
    const sf::Texture& texture() const;

private:
    b2Body* _body; ///< Физическое тело платформы
    sf::ConvexShape _shape; ///< Графический многоугольник платформы
    sf::Texture _texture; ///< Текстура платформы
};

#endif // PLATFORM_H
