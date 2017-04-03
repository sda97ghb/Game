#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"

#include "Game/PaintingWindow.h"
#include "Game/World.h"
#include "Game/Log.h"

PaintingWindow& PaintingWindow::instance()
{
	static PaintingWindow instance(1200, 720, "Game");
	return instance;
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
    _worldView.setCenter(0.0f, 0.0f);
    // scale view to make 1 physical meter equal to 1 grapical unit
    _worldView.setSize(36.0f, -21.0f); // (36x21) == (1200x700) / 100 * 3
    _worldView.setViewport(sf::FloatRect(0.0f, 0.0f, 1.0f, 1.0f));

    _guiView.setSize(1200.0f, 700.0f);
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
    setView(_guiView);
    _background.setPosition(-600.0f, -350.0f);
    draw(_background);
}

void PaintingWindow::drawWorld()
{
    b2Vec2 playerPos = Player::instance().body().GetPosition();
    _worldView.setCenter(playerPos.x, playerPos.y + 5.0f);
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

    for (const Archer& archerC : world.archers())
    {
        Archer& archer = const_cast<Archer&>(archerC);
        sf::Sprite& sprite = constructArcher(archer);
        draw(sprite);
    }

    sf::Sprite& player = constructPlayer();
    draw(player);

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

    float health = Player::instance().health() / Player::instance().maxHealth();
    drawBar(-530.0f, -300.0f, 200.0f, 20.0f, 2.0f, health, sf::Color::Red);

    if (Player::instance().maxMana() != 0.0f)
    {
        float mana = Player::instance().mana() / Player::instance().maxMana();
        drawBar(-530.0f, -285.0f, 200.0f, 20.0f, 2.0f, mana, sf::Color::Blue);
    }

    setView(_worldView);

    World& world = World::instance();
    for (const Archer& archerC : world.archers())
    {
        Archer& archer = const_cast<Archer&>(archerC);
        b2Vec2 posB2 = archer.body().GetPosition();
        sf::Vector2f pos(posB2.x - 0.8,
                         posB2.y + archer.height() / 2.0f + 0.2f);
        float health = archer.health() / archer.maxHealth();
        drawBar(pos.x, pos.y, 1.6f, 0.2f, 0.04f, health, sf::Color::Red);
    }
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
    size *= 16.0f;
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
    size *= 16;
    shapeSF.setScale(1.0f / 16.0f, 1.0f / 16.0f);
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
	shapeSF.setScale(1.0f / 16.0f, 1.0f / 16.0f);
	shapeSF.setTextureRect(sf::IntRect(sf::Vector2i(0, 0),
						   sf::Vector2i(spikes.lenght()*16, 0.5 * 16)));

	shapeSF.setPosition(sf::Vector2f(spikes.x1(), spikes.y1()));
	shapeSF.setSize(sf::Vector2f(spikes.lenght()*16, 0.5 * 16));
	shapeSF.setRotation(180 * spikes.angle()/3.14);

    return shapeSF;
}

sf::ConvexShape& PaintingWindow::constructWater(Water& water, bool isFront)
{
    b2PolygonShape& shapeB2 = water.shapeB2();

    sf::ConvexShape& shapeSF = water.shapeSF();
    sf::Texture& texture = isFront ? water.texture() : water.textureBack();

    shapeSF.setTexture(&texture);
    b2Vec2 size = computeSize(shapeB2);
    size *= 16.0f;
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
    size *= 16.0f;
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

sf::Sprite& PaintingWindow::constructEntity(Entity& entity)
{
    SpriteAnimator& animator = entity.spriteAnimator();
    animator.update();

    if (!entity.isAlive())
    {
        entity.spriteAnimator().playGroup("dead");
        entity.spriteAnimator().nextFrame();
        entity.spriteAnimator().stop();
    }
    sf::Sprite& sprite = animator.sprite();

    sprite.setScale(1.0f / 16.0f, -1.0f / 16.0f);

    b2Vec2 pos = entity.body().GetPosition();
    sf::Vector2f posSF = sf::Vector2f(pos.x, pos.y);
    posSF.x -= sprite.getTextureRect().width / 32.0f;
    posSF.y += sprite.getTextureRect().height / 32.0f;
    sprite.setPosition(posSF);

    return sprite;
}

sf::Sprite& PaintingWindow::constructPlayer()
{
    return constructEntity(Player::instance());
}

sf::Sprite& PaintingWindow::constructArcher(Archer& archer)
{
    return constructEntity(archer);
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
