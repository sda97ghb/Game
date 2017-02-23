#ifndef PAINTER_H
#define PAINTER_H

#include "SFML/Graphics.hpp"
#include "Game/World.h"

class Painter
{
public:
    ~Painter();
    void initialize();

    sf::RenderWindow& window();

    void drawWorld();

    sf::RectangleShape& constructLadder(Ladder& ladder);
    sf::ConvexShape& constructPlatform(Platform& platform);
    sf::Sprite& constructPlayer();
    sf::Sprite& constructArcher(TestArcher& archer);

private:
    sf::RenderWindow* _window;
    sf::View* _view;

    sf::Texture _backgroundTexture;
    sf::Sprite _background;
};

#endif // PAINTER_H
