#include <iostream>
#include "Test/Test.h"

#include "Game/Painter.h"

#include "Test/TestWorldLoader.h"

void test::main()
{
    Painter painter;
    painter.initialize();
    sf::RenderWindow& window = painter.window();

    TestWorldLoader loader;
    loader.load();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        painter.drawWorld();

        window.display();
    }
}
