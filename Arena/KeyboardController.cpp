#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

#include "Arena/KeyboardController.h"
#include "Arena/World.h"

#include "Arena/Entity/Player.h"

void KeyboardController::processKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        World::instance().player1()->tryToMoveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        World::instance().player1()->tryToMoveRight();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        World::instance().player1()->tryToJump();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        World::instance().player2()->tryToMoveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        World::instance().player2()->tryToMoveRight();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        World::instance().player2()->tryToJump();

//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
//    {
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
//    {
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
//    {
//    }

//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
//    {
//    }
}
