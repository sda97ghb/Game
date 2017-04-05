#include "SFML/Window/Mouse.hpp"

#include "Arena/MouseController.h"
#include "Arena/Player.h"

void MouseController::processMouse()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        Player::instance().punch();
}
