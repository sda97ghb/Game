#include "SFML/Window/Keyboard.hpp"

#include "Arena/KeyboardController.h"
#include "Arena/World.h"

#include "Arena/Entity/ArrowBuilderSpawner.h"

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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        static int counter = 0;
        if (counter++ <= 10)
            return;
        counter = 0;

        ArrowBuilderSpawner()
                .setPosition(World::instance().player().body()->GetPosition())
//                .setDirection(10.0f / 180.0f * 3.14f)
                .setTarget(0.0f, 10.0f)
                .setSpeed(100.0f)
                .spawn();
    }
}
