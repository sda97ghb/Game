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
    b2Vec2 pos = World::instance().player().body().GetPosition();
    pos.y -= 7.0f;
    if (pos.y < 0.0f)
        pos.y = 0.0f;
    sf::Vector2f posSF = translate::PosPf2Sf(pos);
//    _view->setRotation(posSF.y);
    _view->setCenter(posSF.x + 0.0f, posSF.y - 300.0f);
    _window->setView(*_view);

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

    for (const TestArcher& archerC : world.archers())
    {
        TestArcher& archer = const_cast<TestArcher&>(archerC);
        sf::Sprite& sprite = constructArcher(archer);
        _window->draw(sprite);
    }

    sf::Sprite& player = constructPlayer();
    _window->draw(player);

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

sf::Sprite& Painter::constructPlayer()
{
    TestPlayer& player = TestPlayer::instance();
    b2Body& body = player.body();
    sf::Texture& texture = player.texture();
    sf::Sprite& sprite = player.sprite();

    sprite.setTexture(texture);

    b2Vec2 pos = body.GetPosition();
    pos.x -= player.width() / 2;
    pos.y += player.height() / 2;
    sprite.setPosition(translate::PosPf2Sf(pos));

    return sprite;
}

sf::Sprite&Painter::constructArcher(TestArcher& archer)
{
    b2Body& body = archer.body();
    sf::Texture& texture = archer.texture();
    sf::Sprite& sprite = archer.sprite();

    sprite.setTexture(texture);

    b2Vec2 pos = body.GetPosition();
    pos.x -= archer.width() / 2;
    pos.y += archer.height() / 2;
    sprite.setPosition(translate::PosPf2Sf(pos));

    return sprite;
}

sf::RectangleShape& Painter::constructLadder(Ladder& ladder)
{
    b2PolygonShape& shapeB2 = ladder.shapeB2();

    sf::RectangleShape& shapeSF = ladder.shapeSF();
    sf::Texture& texture = ladder.texture();

    shapeSF.setTexture(&texture);
    b2Vec2 size = computeSize(shapeB2);
//    static int N = 0;
//    static int counter = 0;
//    ++ counter;
//    if (counter >= 400)
//    {
//        ++N;
//        if (N >= 4)
//            N = 0;
//        counter = 0;
//    }
//    shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(2 * 12, 2 * 28 * N),
//                                       translate::SizePf2Si(size)));
    shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
                                       translate::SizePf2Si(size)));

    b2Vec2 pos(ladder.x() - ladder.width() / 2.0f, ladder.y2());
    shapeSF.setPosition(translate::PosPf2Sf(pos));
    shapeSF.setSize(translate::SizePf2Sf(ladder.size()));

    return shapeSF;
}
