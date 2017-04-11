#include "SFML/Window/Keyboard.hpp"

#include "Game/KeyboardController.h"
#include "Game/Player.h"
#include "Game/World.h"
#include "Game/Quests.h"

void KeyboardController::processKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        Player::instance().stepLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        Player::instance().stepRight();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        Player::instance().jump();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        Player::instance().punch();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        for (const Archer& archerC : World::instance().archers())
            const_cast<Archer&>(archerC).stepLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        for (const Archer& archerC : World::instance().archers())
            const_cast<Archer&>(archerC).stepRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
    {
        for (const Archer& archerC : World::instance().archers())
            const_cast<Archer&>(archerC).jump();
    }
}
