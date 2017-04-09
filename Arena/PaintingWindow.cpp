#include <iostream>

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Text.hpp"

#include "SFML/Window/Event.hpp"

#include "Arena/GlobalConstants.h"
#include "Arena/Log.h"
#include "Arena/PaintingWindow.h"
#include "Arena/World.h"

PaintingWindow& PaintingWindow::instance()
{
    static PaintingWindow instance(SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y, "Game");
    return instance;
}

PaintingWindow::~PaintingWindow()
{
    for (EntityView* entityView : _entityViews)
    {
        if (entityView != nullptr)
            delete entityView;
    }
}

void PaintingWindow::setBackground(const std::string& background)
{
	_backgroundTexture.loadFromFile(background);
	_background.setTexture(_backgroundTexture);
}

PaintingWindow::PaintingWindow(uint32_t width, uint32_t height,
                               const std::string& title) :
    sf::RenderWindow(sf::VideoMode(width, height), title)
{
    _backgroundView.setCenter(SCREEN_RESOLUTION_X / PIXELART_SCALE_FACTOR / 2.0f,
                              SCREEN_RESOLUTION_Y / PIXELART_SCALE_FACTOR / 2.0f);
    _backgroundView.setSize(SCREEN_RESOLUTION_X / PIXELART_SCALE_FACTOR,
                            SCREEN_RESOLUTION_Y / PIXELART_SCALE_FACTOR);
    _backgroundView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

    _worldView.setCenter(0.0f, 0.0f);
    // scale view to make 1 physical meter equal to 1 grapical unit
    // (256x144) / 5 == (51.2x28.8)
    _worldView.setSize(  SCREEN_RESOLUTION_X / PIXELART_SCALE_FACTOR / PIXELS_PER_METER,
                       -(SCREEN_RESOLUTION_Y / PIXELART_SCALE_FACTOR / PIXELS_PER_METER));
    _worldView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

    _guiView.setSize(SCREEN_RESOLUTION_X, SCREEN_RESOLUTION_Y);
    _guiView.setCenter(0.0f, 0.0f);
    _guiView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

    setView(_worldView);

	const std::string FONTS_DIRECTORY = "Fonts";
	font.loadFromFile(FONTS_DIRECTORY + "/open-sans/OpenSans-Light.ttf");
}

void PaintingWindow::paint()
{
    clear();

    drawBackground();
    drawWorld();
    drawGui();
    drawLog();

    display();
}

void PaintingWindow::drawBackground()
{
    setView(_backgroundView);
    draw(_background);
}

void PaintingWindow::drawWorld()
{
//    b2Vec2 playerPos = Player::instance().body().GetPosition();
//    _worldView.setCenter(playerPos.x, playerPos.y + 5.0f);
    _worldView.setCenter(0.0f, SCREEN_RESOLUTION_Y / PIXELART_SCALE_FACTOR / PIXELS_PER_METER / 2.0f -
                         6.0f / PIXELS_PER_METER);
    setView(_worldView);

    World& world = World::instance();

    for (const Platform& cPlatform : world.platforms())
    {
        Platform& platform = const_cast<Platform&>(cPlatform);
        sf::ConvexShape& shape = constructPlatform(platform);
        draw(shape);
    }

    for (const Water& waterC : world.waters())
    {
        Water& water = const_cast<Water&>(waterC);
        sf::ConvexShape& shape = constructWater(water, false);
        draw(shape);
    }

    for (const Ladder& ladderC : world.ladders())
    {
        Ladder& ladder = const_cast<Ladder&>(ladderC);
        sf::RectangleShape& shape = constructLadder(ladder);
        draw(shape);
    }

	for (const Spikes& spikesC : world.spikes())
	{
		Spikes& spikes = const_cast<Spikes&>(spikesC);
		sf::RectangleShape& shape = constructSpikes(spikes);
		draw(shape);
	}

    for (EntityView* view : _entityViews)
        draw(view->getSprite());

    for (const Lava& lavaC : world.lavas())
    {
        Lava& lava = const_cast<Lava&>(lavaC);
        sf::ConvexShape& shape = constructLava(lava, true);
        draw(shape);
    }

    for (const Water& waterC : world.waters())
    {
        Water& water = const_cast<Water&>(waterC);
        sf::ConvexShape& shape = constructWater(water, true);
        draw(shape);
    }

    sf::CircleShape zeroSprite;
    zeroSprite.setPosition(0.0f, 0.0f);
    zeroSprite.setRadius(0.1f);
    zeroSprite.setFillColor(sf::Color(255, 0, 0));
    draw(zeroSprite);
}

void PaintingWindow::drawGui()
{
    setView(_guiView);

//    float health = Player::instance().health() / Player::instance().maxHealth();
//    drawBar(-530.0f, -300.0f, 200.0f, 20.0f, 2.0f, health, sf::Color::Red);

//    if (Player::instance().maxMana() != 0.0f)
//    {
//        float mana = Player::instance().mana() / Player::instance().maxMana();
//        drawBar(-530.0f, -285.0f, 200.0f, 20.0f, 2.0f, mana, sf::Color::Blue);
//    }

    setView(_worldView);

//    World& world = World::instance();
//    for (const Archer& archerC : world.archers())
//    {
//        Archer& archer = const_cast<Archer&>(archerC);
//        b2Vec2 posB2 = archer.body().GetPosition();
//        sf::Vector2f pos(posB2.x - 0.8,
//                         posB2.y + archer.height() / 2.0f + 0.2f);
//        float health = archer.health() / archer.maxHealth();
//        drawBar(pos.x, pos.y, 1.6f, 0.2f, 0.04f, health, sf::Color::Red);
//    }
}

void PaintingWindow::drawLog()
{
    setView(_guiView);

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
        draw(text);
        ++i;
    }
}

void PaintingWindow::drawBar(float x, float y, float width, float height,
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

    draw(barBackground);
    draw(barLine);
}

/// @brief Compute size of a shape by its aabb.
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

sf::ConvexShape& PaintingWindow::constructPlatform(Platform& platform)
{
    b2PolygonShape& shapeB2 = platform.shapeB2();

    sf::ConvexShape& shapeSF = platform.shapeSF();
    sf::Texture& texture = platform.texture();

    shapeSF.setTexture(&texture);
    b2Vec2 size = computeSize(shapeB2);
    size *= PIXELS_PER_METER;
    shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
                                       sf::Vector2i(size.x, size.y)));

    int32 vertexCount = shapeB2.GetVertexCount();
    shapeSF.setPointCount(vertexCount);
    for (int32 i = 0; i < vertexCount; ++ i)
    {
        b2Vec2 vertex = shapeB2.GetVertex(i);
        float x = vertex.x;
        float y = vertex.y;
        shapeSF.setPoint(i, sf::Vector2f(x, y));
    }

    return shapeSF;
}

sf::RectangleShape& PaintingWindow::constructLadder(Ladder& ladder)
{
    b2PolygonShape& shapeB2 = ladder.shapeB2();

    sf::RectangleShape& shapeSF = ladder.shapeSF();
    sf::Texture& texture = ladder.texture();

    shapeSF.setTexture(&texture);
    b2Vec2 size = computeSize(shapeB2);
    size *= PIXELS_PER_METER;
    shapeSF.setScale(1.0f / PIXELS_PER_METER, 1.0f / PIXELS_PER_METER);
    shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
                                       sf::Vector2i(size.x, size.y)));

    shapeSF.setPosition(sf::Vector2f(ladder.x() - ladder.width() / 2.0f,
                                     ladder.y1()));
    shapeSF.setSize(sf::Vector2f(size.x, size.y));

    return shapeSF;
}

sf::RectangleShape& PaintingWindow::constructSpikes(Spikes& spikes)
{
//	b2PolygonShape& shapeB2 = spikes.shapeB2();

	sf::RectangleShape& shapeSF = spikes.shapeSF();
	sf::Texture& texture = spikes.texture();

	shapeSF.setTexture(&texture);
    shapeSF.setScale(1.0f / PIXELS_PER_METER, 1.0f / PIXELS_PER_METER);
	shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
                           sf::Vector2i(spikes.lenght() * PIXELS_PER_METER,
                                        0.5f * PIXELS_PER_METER)));

	shapeSF.setPosition(sf::Vector2f(spikes.x1(), spikes.y1()));
    shapeSF.setSize(sf::Vector2f(spikes.lenght() * PIXELS_PER_METER, 0.5f * PIXELS_PER_METER));
    shapeSF.setRotation(180.0f * spikes.angle() / 3.14f);

    return shapeSF;
}

sf::ConvexShape& PaintingWindow::constructWater(Water& water, bool isFront)
{
    b2PolygonShape& shapeB2 = water.shapeB2();

    sf::ConvexShape& shapeSF = water.shapeSF();
    sf::Texture& texture = isFront ? water.texture() : water.textureBack();

    shapeSF.setTexture(&texture);
    b2Vec2 size = computeSize(shapeB2);
    size *= PIXELS_PER_METER;
    shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
                                       sf::Vector2i(size.x, size.y)));

    int32 vertexCount = shapeB2.GetVertexCount();
    shapeSF.setPointCount(vertexCount);
    for (int32 i = 0; i < vertexCount; ++ i)
    {
        b2Vec2 vertex = shapeB2.GetVertex(i);
        shapeSF.setPoint(i, sf::Vector2f(vertex.x, vertex.y));
    }

    return shapeSF;
}

sf::ConvexShape&PaintingWindow::constructLava(Lava& lava, bool isFront)
{
    b2PolygonShape& shapeB2 = lava.shapeB2();

    sf::ConvexShape& shapeSF = lava.shapeSF();
    sf::Texture& texture = isFront ? lava.texture() : lava.textureBack();

    shapeSF.setTexture(&texture);
    b2Vec2 size = computeSize(shapeB2);
    size *= PIXELS_PER_METER;
    shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
                                       sf::Vector2i(size.x, size.y)));

    int32 vertexCount = shapeB2.GetVertexCount();
    shapeSF.setPointCount(vertexCount);
    for (int32 i = 0; i < vertexCount; ++ i)
    {
        b2Vec2 vertex = shapeB2.GetVertex(i);
        shapeSF.setPoint(i, sf::Vector2f(vertex.x, vertex.y));
    }

    return shapeSF;
}

void PaintingWindow::processEvents()
{
    sf::Event event;
    while (pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            close();
    }
}

void PaintingWindow::addEntityView(EntityView* entityView)
{
    _entityViews.push_back(entityView);
}
