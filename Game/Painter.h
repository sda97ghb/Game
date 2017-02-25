#ifndef PAINTER_H
#define PAINTER_H

#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/View.hpp"

#include "Game/Archer.h"
#include "Game/Entity.h"
#include "Game/Ladder.h"
#include "Game/Platform.h"

class Painter
{
public:
    ~Painter();
    void initialize();

    sf::RenderWindow& window();

    void drawWorld();

    sf::ConvexShape& constructPlatform(Platform& platform);

    sf::RectangleShape& constructLadder(Ladder& ladder);

    sf::Sprite& constructEntity(Entity& entity);
    sf::Sprite& constructPlayer();
    sf::Sprite& constructArcher(Archer& archer);

private:
    sf::RenderWindow* _window;
    sf::View* _view;

    sf::Texture _backgroundTexture;
    sf::Sprite _background;
};

#endif // PAINTER_H
