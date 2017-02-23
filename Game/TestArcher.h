#ifndef TESTARCHER_H
#define TESTARCHER_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Box2D/Dynamics/b2Body.h"

class TestArcher
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

    TestArcher();
    TestArcher(const TestArcher& archer) = delete;
    void operator= (const TestArcher& archer) = delete;

    void setTexture(const std::string& filename);

    void setPosition(float x, float y);

    void setBody(b2Body* body);

    float x() const;
    float y() const;

    float cornerX() const;
    float cornerY() const;

    float width() const;
    float height() const;

    b2Body& body();
    const b2Body& body() const;

    sf::Texture& texture();
    const sf::Texture& texture() const;

    sf::Sprite& sprite();
    const sf::Sprite& sprite() const;

    b2PolygonShape& shape();
    const b2PolygonShape& shape() const;

    void stepLeft();
    void stepRight();
    void jump();

    void setOnGround(bool value);
    bool isOnGround() const;

private:
    b2Body* _body;
    sf::Texture _texture;
    sf::Sprite _sprite;

    bool _isOnGround;
};

#endif // TESTARCHER_H
