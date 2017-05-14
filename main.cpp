#include <iostream>
#include <conio.h>

#include "SFML/Window/Event.hpp"

#include "Arena/Audio.h"
#include "Arena/KeyboardController.h"
#include "Arena/Menu.h"
#include "Arena/MapLoader.h"
#include "Arena/MapUnloader.h"
#include "Arena/MouseController.h"
#include "Arena/ObjectCounter.h"
#include "Arena/PaintingWindow.h"
#include "Arena/World.h"

#include "Arena/Entity/EntityDestroyer.h"

#include "Test/TestWorldLoader.h"

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    //    width   height  ratio
    //
    //    16/9 ratio
    //
    //    1920    1080    1,7
    //    1600    900     1,7
    //    1366    768     1,7
    //
    //    16/10 ratio
    //
    //    1200    720     1,6
    //    320     200     1,6
    //
    //    4/3 ratio
    //
    //    1024    768     1,3
    //    320     240     1,3

    PaintingWindow& window = PaintingWindow::instance();

    while (window.isOpen())
    {
        window.processEvents();

        if (Menu::instance().isShown() || Menu::instance().isShownOptions())
        {
            window.clear(sf::Color::Black);

            if (Menu::instance().isShown())
                Menu::instance().drawMenu();
            if (Menu::instance().isShownOptions())
                Menu::instance().drawOptions();

            window.display();

            continue;
        }

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

        auto destroyers = ObjectCounter<EntityDestroyer>::objects();
        for (EntityDestroyer* destroyer : destroyers)
        {
            destroyer->destroy();
            delete destroyer;
        }
    }

    MapUnloader().unload();

    std::cout << "Done." << std::endl;

    return 0;
}
