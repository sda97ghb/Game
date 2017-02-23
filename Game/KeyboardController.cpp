#include "KeyboardController.h"

#include <SFML/Window/Keyboard.hpp>

#include "Game/TestPlayer.h"
#include "Game/World.h"
KeyboardController::KeyboardController()
{
}

void KeyboardController::processKeyboard()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        TestPlayer::instance().stepLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        TestPlayer::instance().stepRight();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        TestPlayer::instance().jump();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
    {
        for (const TestArcher& archerC : World::instance().archers())
            const_cast<TestArcher&>(archerC).stepLeft();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H))
    {
        for (const TestArcher& archerC : World::instance().archers())
            const_cast<TestArcher&>(archerC).stepRight();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
    {
        for (const TestArcher& archerC : World::instance().archers())
            const_cast<TestArcher&>(archerC).jump();
    }
}
