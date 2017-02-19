#include "Game/Ladder.h"

#include "Game/Player.h"
#include "SFML/Window/Keyboard.hpp"

void Ladder::setCoordinates(float x, float y1, float y2)
{
    _x = x;
    _y1 = y1;
    _y2 = y2;
}

void Ladder::setWidth(float width)
{
    _width = width;
}

void Ladder::testPlayerOnIt()
{
    Player& player = Player::instance();
    float playerX = player.body().GetPosition().x;
    float playerY = player.body().GetPosition().y;
    bool isPlayerOnIt = playerX > _x - _width / 2 && playerY > _y1 &&
                        playerX < _x + _width / 2 && playerY < _y2;
    if (!isPlayerOnIt)
        return;
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
//        player.body().ApplyLinearImpulseImpulse(b2Vec(0.0f, 1.0f),
//                                                player.body().GetWorldCenter(),
//                                                true);
}

float Ladder::x() const
{
    return _x;
}

float Ladder::y1() const
{
    return _y1;
}

float Ladder::y2() const
{
    return _y2;
}

float Ladder::width() const
{
    return _width;
}

float Ladder::height() const
{
    return _y2 - _y1;
}
