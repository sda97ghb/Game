#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

#include "Arena/KeyboardController.h"
#include "Arena/World.h"

void KeyboardController::processKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        World::instance().player().tryToMoveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        World::instance().player().tryToMoveRight();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        World::instance().player().tryToJump();
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
