#include "SFML/Window/Mouse.hpp"

#include "Game/MouseController.h"
#include "Game/Player.h"

void MouseController::processMouse()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        Player::instance().punch();
}
