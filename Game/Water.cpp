#include "SFML/Window/Keyboard.hpp"

#include "Box2D/Dynamics/b2Fixture.h"

#include "Game/ImageScaler.h"
#include "Game/Player.h"
#include "Game/Water.h"

void Water::setShape(const b2PolygonShape& shape)
{
    _shapeB2 = shape;
}

void Water::setTextureBack(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _textureBack.loadFromImage(ImageScaler::scale(original));
    _textureBack.setRepeated(true);
}

void Water::setTextureFront(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _textureFront.loadFromImage(ImageScaler::scale(original));
    _textureFront.setRepeated(true);
}

void Water::testPlayerOnIt()
{
    try {
        Player& player = Player::instance();
        b2Body& body = player.body();
        b2Transform transform;
        transform.SetIdentity();
        if (_shapeB2.TestPoint(transform, player.body().GetPosition()))
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
                if (body.GetLinearVelocity().y < 2.0f)
                    body.ApplyLinearImpulse(b2Vec2(0.0f, 4.0f),
                                            body.GetWorldCenter(), true);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                if (body.GetLinearVelocity().y > -2.0f)
                    body.ApplyLinearImpulse(b2Vec2(0.0f, -4.0f),
                                            body.GetWorldCenter(), true);

            b2Vec2 velocity = body.GetLinearVelocity();
            velocity.x *= 0.9;
            velocity.y *= 0.9;
            body.SetLinearVelocity(velocity);

            player.spriteAnimator().setCurrentGroup("climbing");
        }
    }
    catch (Player::NoBodyException&)
    {
    }
}

b2PolygonShape& Water::shapeB2()
{
    return _shapeB2;
}

const b2PolygonShape& Water::shapeB2() const
{
    return _shapeB2;
}

sf::ConvexShape& Water::shapeSF()
{
    return _shapeSF;
}

const sf::ConvexShape& Water::shapeSF() const
{
    return _shapeSF;
}

sf::Texture& Water::textureBack()
{
    return _textureBack;
}

const sf::Texture& Water::textureBack() const
{
    return _textureBack;
}

sf::Texture& Water::textureFront()
{
    return _textureFront;
}

const sf::Texture& Water::textureFront() const
{
    return _textureFront;
}
