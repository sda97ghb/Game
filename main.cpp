#include <iostream>
#include <conio.h>

#include "SFML/Window/Event.hpp"

#include "Arena/KeyboardController.h"
#include "Arena/MouseController.h"
#include "Arena/PaintingWindow.h"
#include "Arena/World.h"

#include "Test/TestWorldLoader.h"

#include "Arena/MapLoader.h"

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

//    sf::VideoMode::getDesktopMode()
    PaintingWindow& window = PaintingWindow::instance();

    /*TestWorldLoader loader;
    loader.load();*/

    MapLoader loader;
    try
    {
        loader.loadFromFile("MapLevels/LEVEL_ONE.xml");
    }
    catch (MapLoader::XmlError& error)
    {
        std::cout << error.what() << std::endl;
        std::cout << error._lineNum << std::endl;
        exit(EXIT_FAILURE);
    }
    catch (MapLoader::MissingArgument& error)
    {
        std::cout << error.what() << std::endl;
        std::cout << error._lineNum << std::endl;
        exit(EXIT_FAILURE);
    }
    catch (MapLoader::WrongArgumentFormat& error)
    {
        std::cout << error.what() << std::endl;
        std::cout << error._lineNum << std::endl;
        exit(EXIT_FAILURE);
    }
    catch (MapLoader::NoChildElementException& error)
    {
        std::cout << error.what() << std::endl;
        std::cout << error._lineNum << std::endl;
        exit(EXIT_FAILURE);
    }

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

    std::cout << "Done." << std::endl;

    return 0;
}
