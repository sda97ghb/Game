#include "Game/Painter.h"
#include "CoordinateTranslation.h"

Painter::~Painter()
{
    ;
}
#include <iostream>
void Painter::initialize()
{
//    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
//    _window = new sf::RenderWindow(videoMode, "Game", sf::Style::Fullscreen);
    sf::VideoMode videoMode = sf::VideoMode(1200, 720);
    _window = new sf::RenderWindow(videoMode, "Game");
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

    for (const Platform& cPlatform : world.platforms())
    {
        Platform& platform = const_cast<Platform&>(cPlatform);
        sf::ConvexShape& shape = constructPlatform(platform);(void)shape;
        _window->draw(shape);
    }
    for (const Ladder& ladderC : world.ladders())
    {
        Ladder& ladder = const_cast<Ladder&>(ladderC);
        sf::RectangleShape& shape = constructLadder(ladder);
        _window->draw(shape);
    }

    sf::CircleShape zeroSprite;
    zeroSprite.setPosition(0.0f, 0.0f);
    zeroSprite.setRadius(1.0f);
    zeroSprite.setFillColor(sf::Color(255, 0, 0));
    _window->draw(zeroSprite);
}

#include "Box2D.h"

b2Vec2 computeSize(b2Shape& shape)
{
    b2AABB aabb;
    b2Transform transform;
    transform.SetIdentity();
    int32 index = 0;
    shape.ComputeAABB(&aabb, transform, index);
    b2Vec2 size = aabb.upperBound;
    size -= aabb.lowerBound;
    return size;
}

sf::ConvexShape& Painter::constructPlatform(Platform& platform)
{
    b2PolygonShape& shapeB2 = platform.shapeB2();

    sf::ConvexShape& shapeSF = platform.shapeSF();
    sf::Texture& texture = platform.texture();

    shapeSF.setTexture(&texture);
    b2Vec2 size = computeSize(shapeB2);
    shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
                                       translate::SizePf2Si(size)));

    int32 vertexCount = shapeB2.GetVertexCount();
    shapeSF.setPointCount(vertexCount);
    for (int32 i = 0; i < vertexCount; ++ i)
        shapeSF.setPoint(i, translate::PosPf2Sf(shapeB2.GetVertex(i)));

    return shapeSF;
}

sf::RectangleShape& Painter::constructLadder(Ladder& ladder)
{
    b2PolygonShape& shapeB2 = ladder.shapeB2();

    sf::RectangleShape& shapeSF = ladder.shapeSF();
    sf::Texture& texture = ladder.texture();

    shapeSF.setTexture(&texture);
    b2Vec2 size = computeSize(shapeB2);
    shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
                                       translate::SizePf2Si(size)));

    b2Vec2 pos(ladder.x() - ladder.width() / 2.0f, ladder.y2());
    shapeSF.setPosition(translate::PosPf2Sf(pos));
    shapeSF.setSize(translate::SizePf2Sf(ladder.size()));

    return shapeSF;
}
