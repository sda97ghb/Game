#include "SFML/Window/Keyboard.hpp"

#include "Arena/KeyboardController.h"
#include "Arena/Entity/Player.h"
#include "Arena/World.h"

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
        for (const Panther& pantherC : World::instance().panthers())
            const_cast<Panther&>(pantherC).stepLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        for (const Archer& archerC : World::instance().archers())
            const_cast<Archer&>(archerC).stepRight();
        for (const Panther& pantherC : World::instance().panthers())
            const_cast<Panther&>(pantherC).stepRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
    {
        for (const Archer& archerC : World::instance().archers())
            const_cast<Archer&>(archerC).jump();
        for (const Panther& pantherC : World::instance().panthers())
            const_cast<Panther&>(pantherC).jump();
    }
}
