#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Text.hpp"

#include "Game/CoordinateTranslation.h"
#include "Game/Painter.h"
#include "Game/World.h"
#include "Game/Log.h"

Painter::~Painter()
{
    delete _view;
    delete _window;
}

void Painter::initialize()
{
//    sf::VideoMode videoMode = sf::VideoMode::getDesktopMode();
    sf::VideoMode videoMode = sf::VideoMode(1200, 720);
//    _window = new sf::RenderWindow(videoMode, "Game", sf::Style::Fullscreen);
    _window = new sf::RenderWindow(videoMode, "Game");
    _view = new sf::View(sf::FloatRect(-(videoMode.width * 0.5f),
                                       -(videoMode.height * 0.9f),
                                        videoMode.width, videoMode.height));
    _window->setView(*_view);

    _backgroundTexture.loadFromFile("Textures/background.png");
    _background.setTexture(_backgroundTexture);
}

sf::RenderWindow& Painter::window()
{
    return *_window;
}

void Painter::drawBackground()
{
    sf::Vector2f posSF = setViewForWorld();

    _background.setPosition(posSF.x - 600.0f, posSF.y - 360.0f);
    _window->draw(_background);
}

void Painter::drawWorld()
{
    setViewForWorld();

    World& world = World::instance();

    for (const Platform& cPlatform : world.platforms())
    {
        Platform& platform = const_cast<Platform&>(cPlatform);
        sf::ConvexShape& shape = constructPlatform(platform);
        _window->draw(shape);
    }

    for (const Ladder& ladderC : world.ladders())
    {
        Ladder& ladder = const_cast<Ladder&>(ladderC);
        sf::RectangleShape& shape = constructLadder(ladder);
        _window->draw(shape);
    }

    for (const Water& waterC : world.waters())
    {
        Water& water = const_cast<Water&>(waterC);
        sf::ConvexShape& shape = constructWater(water, false);
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

    for (const Water& waterC : world.waters())
    {
        Water& water = const_cast<Water&>(waterC);
        sf::ConvexShape& shape = constructWater(water, true);
        _window->draw(shape);
    }

    sf::CircleShape zeroSprite;
    zeroSprite.setPosition(0.0f, 0.0f);
    zeroSprite.setRadius(1.0f);
    zeroSprite.setFillColor(sf::Color(255, 0, 0));
    _window->draw(zeroSprite);
}

void Painter::drawGui()
{
    setViewForGui();

    float health = Player::instance().health() / Player::instance().maxHealth();
    drawBar(-530.0f, -300.0f, 200.0f, 20.0f, 2.0f, health, sf::Color::Red);

    if (Player::instance().maxMana() != 0.0f)
    {
        float mana = Player::instance().mana() / Player::instance().maxMana();
        drawBar(-530.0f, -285.0f, 200.0f, 20.0f, 2.0f, mana, sf::Color::Blue);
    }

    //----------------//

    setViewForWorld();

    World& world = World::instance();
    for (const Archer& archerC : world.archers())
    {
        Archer& archer = const_cast<Archer&>(archerC);
        sf::Vector2f pos = translate::PosPf2Sf(archer.body().GetPosition());
        pos.x -= 50.0f;
        pos.y -= 50.0f;
        float health = archer.health() / archer.maxHealth();
        drawBar(pos.x, pos.y, 100.0f, 6.0f, 1.0f, health, sf::Color::Red);
    }
}

void Painter::drawLog()
{
    _view->setCenter(0.0f, 0.0f);
    _window->setView(*_view);

    const std::string FONTS_DIRECTORY = "Fonts";
    sf::Font font;
    font.loadFromFile(FONTS_DIRECTORY + "/open-sans/OpenSans-Light.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Black);
    text.setOutlineColor(sf::Color::White);
    text.setOutlineThickness(0.5f);
    text.setStyle(sf::Text::Bold);

    int i = 0;
    for (const std::string line : Log::instance().lines())
    {
        text.setString(line);
        text.setPosition(-530.0f, 100.0f + 20.0f * i);
        _window->draw(text);
        ++i;
    }
}

void Painter::drawBar(float x, float y, float width, float height,
                      float border, float value, sf::Color color)
{
    if (value < 0.0f)
        value = 0.0f;
    if (value > 1.0f)
        value = 1.0f;

    sf::RectangleShape barBackground;
    sf::RectangleShape barLine;

    barBackground.setPosition(x, y);
    barBackground.setSize(sf::Vector2f(width, height));
    barBackground.setFillColor(sf::Color::Black);

    barLine.setPosition(x + border, y + border);
    barLine.setSize(sf::Vector2f((width - border * 2.0f) * value,
                                 height - border * 2.0f));
    barLine.setFillColor(color);

    _window->draw(barBackground);
    _window->draw(barLine);
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

sf::ConvexShape& Painter::constructWater(Water& water, bool isFront)
{
    b2PolygonShape& shapeB2 = water.shapeB2();

    sf::ConvexShape& shapeSF = water.shapeSF();
    sf::Texture& texture = isFront ? water.texture() : water.textureBack();

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

sf::Sprite& Painter::constructEntity(Entity& entity)
{
    SpriteAnimator& animator = entity.spriteAnimator();
    animator.update();

    if (!entity.isAlive())
        entity.spriteAnimator().setCurrentGroup("dead");
    sf::Sprite& sprite = animator.sprite();

    sf::Vector2f pos = translate::PosPf2Sf(entity.body().GetPosition());
    pos.x -= sprite.getTextureRect().width / 2.0f;
    pos.y -= sprite.getTextureRect().height / 2.0f;
    sprite.setPosition(pos);

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

sf::Vector2f Painter::setViewForWorld()
{
    b2Vec2 pos = World::instance().player().body().GetPosition();
    pos.y -= 7.0f;
    if (pos.y < 0.0f)
        pos.y = 0.0f;
    sf::Vector2f posSF = translate::PosPf2Sf(pos);
    posSF.y -= 300.0f;
    _view->setCenter(posSF.x, posSF.y);
    _window->setView(*_view);

    return posSF;
}

void Painter::setViewForGui()
{
    _view->setCenter(0.0f, 0.0f);
    _window->setView(*_view);
}
