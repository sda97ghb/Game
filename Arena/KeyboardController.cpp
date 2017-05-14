#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/Mouse.hpp"

#include "Arena/KeyboardController.h"
#include "Arena/World.h"

#include "Arena/Attacks/SwordAttack.h"

#include "Arena/Entity/Player.h"

void KeyboardController::processKeyboard()
{
    Player* player1 = World::instance().player1();
    Player* player2 = World::instance().player2();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        player1->tryToMoveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        player1->tryToMoveRight();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        player1->tryToJump();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        auto attack = new SwordAttack;
        (*attack)
                .setActor(player1)
                .setDamage(10.0f)
                .setDistance(3.0f);
        player1->tryToAttack(attack, 500, true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        player2->tryToMoveLeft();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        player2->tryToMoveRight();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        player2->tryToJump();
}
