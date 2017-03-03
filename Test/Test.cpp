#include <iostream>
#include "Test/Test.h"

#include "SFML/Window/Event.hpp"

#include "Game/KeyboardController.h"
#include "Game/MouseController.h"
#include "Game/PaintingWindow.h"
#include "Game/World.h"

#include "Test/TestWorldLoader.h"

void test::main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    //    width   height  ratio
    //
    //    1920    1080    1,7
    //    1600    900     1,7
    //    1366    768     1,7
    //
    //    1200    720     1,6
    //    320     200     1,6
    //
    //    1024    768     1,3
    //    320     240     1,3

//    sf::VideoMode::getDesktopMode()
    PaintingWindow window(1200, 720, "Game");

    TestWorldLoader loader;
    loader.load();

    while (window.isOpen())
    {
        window.processEvents();
        window.paint();

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

        static sf::Clock mouseProcessingTimer;
        if (mouseProcessingTimer.getElapsedTime().asMilliseconds() >= 10)
        {
            MouseController::processMouse();
            mouseProcessingTimer.restart();
        }
    }
}
