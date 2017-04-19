#include "SFML/Window/Mouse.hpp"

#include "Arena/Log.h"
#include "Arena/MouseController.h"
#include "Arena/PaintingWindow.h"
#include "Arena/World.h"

#include "Arena/Entity/ArrowBuilderSpawner.h"
#include "Arena/Entity/Player.h"

void MouseController::processMouse()
{
}

void MouseController::processMousePressed(const sf::Event::MouseButtonEvent& event)
{
    if (event.button == sf::Mouse::Left)
    {
        PaintingWindow& window = PaintingWindow::instance();
        b2Vec2 targetPos = window.cursorCoordinatesToPhysical(event.x, event.y);

        Player& player = *(World::instance().player());
        b2Vec2 playerPos = player.body()->GetPosition();

        b2Vec2 d = targetPos - playerPos;
        d.Normalize();
        d *= 1.5f;

        playerPos += d;

        ArrowBuilderSpawner().setPosition(playerPos).setTarget(targetPos).spawn();
    }
}
