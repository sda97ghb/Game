#include "SFML/Window/Mouse.hpp"

#include "Arena/Log.h"
#include "Arena/MouseController.h"
#include "Arena/PaintingWindow.h"
#include "Arena/World.h"

#include "Arena/Attacks/BowAttack.h"

#include "Arena/Entity/ArrowBuilderSpawner.h"
#include "Arena/Entity/Player.h"

void MouseController::processMouse()
{
}

void MouseController::processMousePressed(const sf::Event::MouseButtonEvent& event)
{
//    Player* player1 = World::instance().player1();
    Player* player2 = World::instance().player2();

    if (event.button == sf::Mouse::Left)
    {
        PaintingWindow& window = PaintingWindow::instance();
        b2Vec2 targetPos = window.cursorCoordinatesToPhysical(event.x, event.y);

        b2Vec2 playerPos = player2->body()->GetPosition();

        b2Vec2 d = targetPos - playerPos;
        d.Normalize();
        d *= 1.5f;

        playerPos += d;

        auto attack = new BowAttack;
        (*attack)
                .setPosition(playerPos)
                .setTarget(targetPos)
                .setDamage(3.5f);
        player2->tryToAttack(attack, 300);
    }
}
