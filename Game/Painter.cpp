#include "Game/Painter.h"
#include "CoordinateTranslation.h"

Painter::~Painter()
{
    ;
}

void Painter::initialize()
{
    _window = new sf::RenderWindow(sf::VideoMode(1600, 900), "Game",
                                   sf::Style::Fullscreen);
    _view = new sf::View(sf::FloatRect(-800, -450, 1600, 900));
//    _view->
//    _view->rotate(45.0f);
    _window->setView(*_view);
}

sf::RenderWindow& Painter::window()
{
    return *_window;
}

void Painter::drawWorld()
{
    World& world = World::instance();
    for (const Ladder& ladder : world.ladders())
    {
        sf::Sprite& sprite = contructSpriteLadder(const_cast<Ladder&>(ladder));
        _window->draw(sprite);
    }
}

sf::Sprite& Painter::contructSpriteLadder(Ladder& ladder)
{
    sf::Sprite& sprite = ladder.sprite();
    sf::Texture& texture = ladder.texture();
    float screenWidth = physicalToScreen(ladder.width());
    float screenHeight = physicalToScreen(ladder.height());

    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, screenWidth, screenHeight));
    sprite.setPosition(physicalToScreen(ladder.x() - ladder.width() / 2),
                       physicalToScreen(-ladder.y2()));

    sprite.setScale(3.0, 3.0);

    return sprite;
}
