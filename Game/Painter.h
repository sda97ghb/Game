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

    sf::Sprite& contructSpriteLadder(Ladder& ladder);
private:
    sf::RenderWindow* _window;
    sf::View* _view;
};

#endif // PAINTER_H
