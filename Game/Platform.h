#ifndef PLATFORM_H
#define PLATFORM_H

#include <stdexcept>

#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Box2D/Common/b2Math.h"
#include "Box2D/Dynamics/b2Body.h"
#include "Box2D/Collision/Shapes/b2PolygonShape.h"

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

    void setBody(b2Body* body);
    void setShape(const b2PolygonShape& shape);
    void setTexture(const std::string& filename);

    b2PolygonShape& shapeB2();
    const b2PolygonShape& shapeB2() const;
    b2Body& body();
    const b2Body& body() const;
    sf::ConvexShape& shapeSF();
    const sf::ConvexShape& shapeSF() const;
    sf::Texture& texture();
    const sf::Texture& texture() const;

private:
    b2Body* _body;
    sf::ConvexShape _shape;
    sf::Texture _texture;
};

#endif // PLATFORM_H
