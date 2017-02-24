#include "Game/Painter.h"

#include "Box2D/Collision/b2Collision.h"
#include "Box2D/Collision/Shapes/b2Shape.h"
#include "Box2D/Common/b2Math.h"

#include "CoordinateTranslation.h"

Painter::~Painter()
{
    delete _view;
    delete _window;
}

void Painter::initialize()
{
//    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
//    _window = new sf::RenderWindow(videoMode, "Game", sf::Style::Fullscreen);
    sf::VideoMode videoMode = sf::VideoMode(1200, 720);
    _window = new sf::RenderWindow(videoMode, "Game");
    _view = new sf::View(sf::FloatRect(-(videoMode.width * 0.5f), -(videoMode.height * 0.9f),
                                        videoMode.width, videoMode.height));
    _window->setView(*_view);

    _backgroundTexture.loadFromFile("C:/Projects/Game/Textures/background.png");
    _background.setTexture(_backgroundTexture);
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
    _view->setCenter(posSF.x + 0.0f, posSF.y - 300.0f);
    _window->setView(*_view);

    _background.setPosition(posSF.x - 600.0f, posSF.y - 660.0f);
    _window->draw(_background);

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

    for (const Archer& archerC : world.archers())
    {
        Archer& archer = const_cast<Archer&>(archerC);
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

sf::Sprite& Painter::constructEntity(Entity& entity)
{
    SpriteAnimator& animator = entity.spriteAnimator();
    animator.update();

    sf::Sprite& sprite = animator.sprite();

    b2Vec2 pos = entity.body().GetPosition();
    pos.x -= entity.width() / 2.0f;
    pos.y += entity.height() / 2.0f;
    sprite.setPosition(translate::PosPf2Sf(pos));

    return sprite;
}

sf::Sprite& Painter::constructPlayer()
{
    return constructEntity(Player::instance());
}

sf::Sprite& Painter::constructArcher(Archer& archer)
{
    return constructEntity(archer);
}
