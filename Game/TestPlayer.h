#ifndef TESTPLAYER_H
#define TESTPLAYER_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Box2D/Dynamics/b2Body.h"

class TestPlayer
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

    static TestPlayer& instance();

    void setTexture(const std::string& filename);

    void setPosition(float x, float y);

    void setOnGround(bool value);

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

    void stepLeft();
    void stepRight();
    void jump();

    bool isOnGround() const;

private:
    TestPlayer();

    TestPlayer(const TestPlayer&) = delete;
    void operator= (const TestPlayer&) = delete;

    friend class World;
    void setBody(b2Body* body);

    b2PolygonShape& shape();
    const b2PolygonShape& shape() const;

    b2Body* _body;
    sf::Texture _texture;
    sf::Sprite _sprite;

    bool _isOnGround;
};

#endif // TESTPLAYER_H
