#include "Game/Painter.h"
#include "CoordinateTranslation.h"

Painter::~Painter()
{
    ;
}
#include <iostream>
void Painter::initialize()
{
    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    _window = new sf::RenderWindow(videoMode, "Game", sf::Style::Fullscreen);
    _view = new sf::View(sf::FloatRect(-(videoMode.width * 0.5), -(videoMode.height * 0.9),
                                        videoMode.width, videoMode.height));
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
        transformSpriteCoordinates(sprite);
        _window->draw(sprite);
    }

    sf::CircleShape zeroSprite;
    zeroSprite.setPosition(0.0f, 0.0f);
    zeroSprite.setRadius(1.0f);
    zeroSprite.setFillColor(sf::Color(255, 0, 0));
    _window->draw(zeroSprite);

}

sf::Sprite& Painter::contructSpriteLadder(Ladder& ladder)
{
    sf::Sprite& sprite = ladder.sprite();
    sf::Texture& texture = ladder.texture();

    sprite.setTexture(texture);
//    float PIXEL_ART_SCALE = 4.0;
//    sprite.setScale(PIXEL_ART_SCALE, PIXEL_ART_SCALE);
    sprite.setTextureRect(sf::IntRect(0, 0, physicalToScreen(ladder.width()),
                                            physicalToScreen(ladder.height())));
    sprite.setPosition(physicalToScreen(ladder.x()) - physicalToScreen(ladder.width()) / 2,// * PIXEL_ART_SCALE,
                       physicalToScreen(ladder.y1()));
//    sprite.setPosition(physicalToScreen(ladder.x() - ladder.width() / 2),
//                       physicalToScreen(-ladder.y2()));

    return sprite;
}

void Painter::transformSpriteCoordinates(sf::Sprite& sprite)
{
    float x = sprite.getPosition().x;
    float y = sprite.getPosition().y;

    float height = sprite.getTextureRect().height;
    float width = sprite.getTextureRect().width;

    y = -y - height;

//    x = physicalToScreen(x);
//    y = physicalToScreen(y);
//    width = physicalToScreen(width);
//    height = physicalToScreen(height);

    sprite.setPosition(x, y);
//    sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(floor(width)),
//                                            static_cast<int>(floor(height))));

//    float screenWidth = physicalToScreen(ladder.width());
//    float screenHeight = physicalToScreen(ladder.height());
}
