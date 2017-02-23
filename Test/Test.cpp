#include <iostream>
#include "Test/Test.h"

#include "Game/KeyboardController.h"
#include "Game/Painter.h"

#include "Test/TestWorldLoader.h"

void test::main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
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

        static sf::Clock physicTimer;
        if (physicTimer.getElapsedTime().asMilliseconds() >= 16)
        {
            World::instance().update();
            physicTimer.restart();
        }

        static sf::Clock keyboardProcessingTimer;
        if (keyboardProcessingTimer.getElapsedTime().asMilliseconds() >= 10)
        {
            KeyboardController::processKeyboard();
            keyboardProcessingTimer.restart();
        }
    }
}
