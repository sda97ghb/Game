#ifndef TESTENTITY_H
#define TESTENTITY_H

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "Box2D/Dynamics/b2Body.h"

class TestEntity
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

    TestEntity();

    void setTexture(const std::string& filename);

    void setPosition(float x, float y);

    void setOnGround(bool value);
    bool isOnGround() const;

    b2Vec2 footPosition() const;

    virtual float width() const = 0;
    virtual float height() const = 0;

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

protected:
    b2Body* _body;
    sf::Texture _texture;
    sf::Sprite _sprite;

    bool _isOnGround;

private:
    friend class World;
    void setBody(b2Body* body);
};

#endif // TESTENTITY_H
