#include <iostream>
#include <conio.h>
#include "Test/Test.h"

#include "SFML/Window/Event.hpp"

#include "Game/KeyboardController.h"
#include "Game/MouseController.h"
#include "Game/Painter.h"
#include "Game/World.h"

#include "Test/TestWorldLoader.h"

#include "Game/MapLoader.h"

void test::main(int argc, char** argv)
{
    (void)argc;
    (void)argv;
	Painter painter;
    painter.initialize();
    sf::RenderWindow& window = painter.window();

    /*TestWorldLoader loader;
    loader.load();*/

	MapLoader loader;
	try
	{
		loader.loadMap("C:/Users/Alexander/Desktop/Project/Game.git/Game.git/MapLevels/LEVEL_ONE.xml");
	}
	catch (MapLoader::XmlError& error)
	{
		std::cout << error.what() << std::endl;
		std::cout << error._lineNum << std::endl;
	}
	catch (MapLoader::MissingArgument& error)
	{
		std::cout << error.what() << std::endl;
		std::cout << error._lineNum << std::endl;
	}
	catch (MapLoader::WrongArgumentFormat& error)
	{
		std::cout << error.what() << std::endl;
		std::cout << error._lineNum << std::endl;
	}
	catch (MapLoader::NotExistChildElement& error)
	{
		std::cout << error.what() << std::endl;
		std::cout << error._lineNum << std::endl;
	}

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
        painter.drawGui();
        painter.drawLog();

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

        static sf::Clock mouseProcessingTimer;
        if (mouseProcessingTimer.getElapsedTime().asMilliseconds() >= 10)
        {
            MouseController::processMouse();
            mouseProcessingTimer.restart();
        }
    }
}
