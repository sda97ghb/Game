#include "Test/Test.h"

#include "Game/World.h"
#include "Game/Painter.h"

void test::main()
{
    Painter painter;
    painter.initialize();

    Ladder ladder;
    ladder.setCoordinates(0.0, -10.0, 7.0);
    ladder.setWidth(0.45);
    ladder.setTexture("C:/Projects/Game/Textures/ladder2.png");

    World& world = World::instance();
    world.addLadder(std::move(ladder));

    while (painter.window().isOpen())
    {
        sf::Event event;
        while (painter.window().pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                painter.window().close();
        }

        painter.window().clear();

        painter.drawWorld();

        painter.window().display();
    }
}
