#include <iostream>
#include <vector>

#include "Arena/Audio.h"
#include "Arena/MapLoader.h"
#include "Arena/MapUnloader.h"
#include "Arena/World.h"
#include "Arena/PaintingWindow.h"

#include "Arena/Entity/ArcherBuilderSpawner.h"
#include "Arena/Entity/PlayerBuilderSpawner.h"
#include "Arena/Entity/TestFinalEntityBuilderSpawner.h"

using namespace tinyxml2;

World& __world = World::instance(); // Убрать это

namespace section
{
const char* WORLD = "world";

	const char* GROUND = "ground";
		const char* BACKGROUND = "background";
		const char* MIDDLGROUND = "middlground";
		const char* PLATFORMS = "platforms";
			const char* PLATFORM = "platform";

	const char* FURNITURE = "furniture";
		const char* WATER = "water";
		const char* LAVA = "lava";
		const char* LADDER = "ladder";
		const char* CABLE = "cable";
		const char* ROPE = "rope";
		const char* SPIKES = "spikes";
		const char* FALLINGGROUND = "fallingground";
			
    const char* ACTORS = "actors";
		const char* PLAYER = "player";
		const char* ENEMY = "enemy";
			const char* ARCHER = "archer";

	const char* POSITION = "position";
	const char* SHAPE = "shape";
	const char* VERTEX = "vertex";
    const char* TEXTURE = "texture";
	const char* TEXTUREBACK = "textureback";
	const char* COORDINATES = "coordinates";
	const char* WIDTH = "width";
}

void MapLoader::safeLoadFromFile(const std::string& filename)
{
    MapUnloader().unload();

    try
    {
        loadFromFile(filename);
    }
    catch (MapLoader::XmlError& error)
    {
        std::cout << error.what() << std::endl;
        std::cout << error._lineNum << std::endl;
        exit(EXIT_FAILURE);
    }
    catch (MapLoader::MissingArgument& error)
    {
        std::cout << error.what() << std::endl;
        std::cout << error._lineNum << std::endl;
        exit(EXIT_FAILURE);
    }
    catch (MapLoader::WrongArgumentFormat& error)
    {
        std::cout << error.what() << std::endl;
        std::cout << error._lineNum << std::endl;
        exit(EXIT_FAILURE);
    }
    catch (MapLoader::NoChildElementException& error)
    {
        std::cout << error.what() << std::endl;
        std::cout << error._lineNum << std::endl;
        exit(EXIT_FAILURE);
    }

    Audio::instance().playMusic("Audio/Arena.ogg");
}

void MapLoader::loadFromFile(std::string filename)
{
	_document.LoadFile(filename.c_str());

    if (_document.Error())
	{
		_document.PrintError();
		throw XmlError(-1);
	}

    const XMLElement* worldElem = _document.RootElement();
    if (std::string(worldElem->Value()) != section::WORLD)
		throw IncorrectMapFormat(-1);

    const XMLElement* groundElem = worldElem->FirstChildElement(section::GROUND);
    if (groundElem != nullptr)
        loadGround(*groundElem);

    const XMLElement* furnitureElem = worldElem->FirstChildElement(section::FURNITURE);
    if (furnitureElem != nullptr)
        loadFurniture(*furnitureElem);

    const XMLElement* entityElem = worldElem->FirstChildElement(section::ACTORS);
    if (entityElem != nullptr)
        loadEntity(*entityElem);

    loadTestThings();
}

void MapLoader::loadGround(const tinyxml2::XMLElement& groundElem)
{
    loadBackground(childElement(section::BACKGROUND, groundElem));

    const XMLElement* platforms = groundElem.FirstChildElement(section::PLATFORMS);

	for (const XMLElement* platform = platforms->FirstChildElement(section::PLATFORM);
         platform != nullptr;
         platform = platform->NextSiblingElement(section::PLATFORM))
        loadPlatform(*platform);
}

void MapLoader::loadBackground(const tinyxml2::XMLElement& backgroundElem)
{
    const std::string picture = backgroundElem.Attribute("picture");
	PaintingWindow::instance().setBackground(picture);
}

void MapLoader::loadPlatform(const tinyxml2::XMLElement& platformElem)
{
    Platform& platform = __world.createPlatform();

	b2PolygonShape shape;

    const XMLElement& shapeElem = childElement(section::SHAPE, platformElem);

    platform.setShape(loadPolygonShape(shapeElem));

    const XMLElement& textureElem = childElement(section::TEXTURE, platformElem);
    platform.setTexture(textureElem.Attribute("picture"));
}

void MapLoader::loadFurniture(const tinyxml2::XMLElement& furnitureElem)
{
    for (const XMLElement* ladderElem = furnitureElem.FirstChildElement(section::LADDER);
         ladderElem != nullptr;
         ladderElem = ladderElem->NextSiblingElement(section::LADDER))
        loadLadder(*ladderElem);

    for (const XMLElement* water = furnitureElem.FirstChildElement(section::WATER);
         water != nullptr;
         water = water->NextSiblingElement(section::WATER))
		loadWater(*water);

    for (const XMLElement* lava = furnitureElem.FirstChildElement(section::LAVA);
         lava != nullptr;
         lava = lava->NextSiblingElement(section::LAVA))
		loadLava(*lava);
}

void MapLoader::loadLadder(const tinyxml2::XMLElement& ladderElem)
{
    Ladder& ladder = __world.createLadder();

    const XMLElement& coordinatesElement = childElement(section::COORDINATES, ladderElem);
    const XMLElement& widthElement = childElement(section::WIDTH, ladderElem);
    const XMLElement& textureElement = childElement(section::TEXTURE, ladderElem);

    const float width = widthElement.FloatText(1.0f);
    float x, y1, y2;
    loadCoordinates(coordinatesElement, x, y1, y2);

    ladder.setCoordinates(x, y1, y2);
    ladder.setWidth(width);
    ladder.setTexture(textureElement.Attribute("picture"));
}

void MapLoader::loadWater(const tinyxml2::XMLElement& waterElem)
{
    Water& water = __world.createWater();

    water.setShape(loadPolygonShape(childElement(section::SHAPE, waterElem)));

    const XMLElement& textureElement = childElement(section::TEXTURE, waterElem);
    const XMLElement& texturebackElement = childElement(section::TEXTUREBACK, waterElem);

    water.setTexture(textureElement.Attribute("picture"));
    water.setTextureBack(texturebackElement.Attribute("picture"));
}

void MapLoader::loadLava(const tinyxml2::XMLElement& lavaElem)
{
    Lava& lava = __world.createLava();

    lava.setShape(loadPolygonShape(childElement(section::SHAPE, lavaElem)));

    const XMLElement& textureElement = childElement(section::TEXTURE, lavaElem);
    const XMLElement& texturebackElement = childElement(section::TEXTUREBACK, lavaElem);

    lava.setTexture(textureElement.Attribute("picture"));
    lava.setTextureBack(texturebackElement.Attribute("picture"));
}

void MapLoader::loadEntity(const tinyxml2::XMLElement& entityElem)
{
    const XMLElement* playerElement = entityElem.FirstChildElement(section::PLAYER);
    if (playerElement)
        loadPlayer(*playerElement);

    for(const XMLElement* archerElement = entityElem.FirstChildElement(section::ARCHER);
        archerElement != nullptr;
        archerElement = archerElement->NextSiblingElement(section::ARCHER))
        loadArcher(*archerElement);

}

void MapLoader::loadPlayer(const tinyxml2::XMLElement& playerElem)
{
//    Player& player = __world.player();

//	b2Vec2 coordinates;
//    loadCoordinates(childElement(section::POSITION, playerElem), coordinates);
//    player.setPosition(coordinates.x, coordinates.y);

//    SpriteAnimator& animator = player.spriteAnimator();

//    const XMLElement& textureElement = childElement(section::TEXTURE, playerElem);
//    animator.setTexture(textureElement.Attribute("picture"));

    //    loadPlayerAnimator(animator);
}

void MapLoader::loadArcher(const XMLElement& archerElement)
{
    b2Vec2 coordinates;
    loadCoordinates(archerElement, coordinates);
    ArcherBuilderSpawner().setPosition(coordinates).spawn();
}


b2PolygonShape MapLoader::loadPolygonShape(const XMLElement& shapeElem)
{
    b2PolygonShape shape;

    std::vector<b2Vec2> vertexes;

    for (const XMLElement* vertexElem = shapeElem.FirstChildElement(section::VERTEX);
         vertexElem != nullptr;
         vertexElem = vertexElem->NextSiblingElement(section::VERTEX))
    {
        b2Vec2 coordinates;
        loadCoordinates(*vertexElem, coordinates);
        vertexes.push_back(coordinates);
    }

    shape.Set(&vertexes.front(), vertexes.size());

    return shape;
}

const XMLElement& MapLoader::childElement(const std::string elementName,
                                          const XMLElement& parentElement)
{
    const XMLElement* childElement = parentElement.FirstChildElement(elementName.c_str());
	if (childElement == nullptr)
    {
        throw NoChildElementException(parentElement.GetLineNum(),
                                      parentElement.Name(),
                                      elementName);
    }

	return *childElement;

}

void MapLoader::loadCoordinates(const tinyxml2::XMLElement& coordinatesElem,
                                b2Vec2& coordinates)
{
    float x = 0.0f;
    float y = 0.0f;

    XMLError xLoadError = coordinatesElem.QueryFloatAttribute("x", &x);
    XMLError yLoadError = coordinatesElem.QueryFloatAttribute("y", &y);

    if (xLoadError == XMLError::XML_NO_ATTRIBUTE)
        throw MissingArgument(coordinatesElem.GetLineNum());
    if (yLoadError == XMLError::XML_NO_ATTRIBUTE)
        throw MissingArgument(coordinatesElem.GetLineNum());

    if (xLoadError == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
        throw WrongArgumentFormat(coordinatesElem.GetLineNum());
    if (yLoadError == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
        throw WrongArgumentFormat(coordinatesElem.GetLineNum());

	coordinates.Set(x, y);
}

void MapLoader::loadCoordinates(const tinyxml2::XMLElement& coordinatesElem,
                                float& x, float& y1, float& y2)
{
    XMLError xLoadError = coordinatesElem.QueryFloatAttribute("x", &x);
    XMLError y1LoadError = coordinatesElem.QueryFloatAttribute("y1", &y1);
    XMLError y2LoadError = coordinatesElem.QueryFloatAttribute("y2", &y2);

    if (xLoadError == XMLError::XML_NO_ATTRIBUTE)
        throw MissingArgument(coordinatesElem.GetLineNum());
    if (y1LoadError == XMLError::XML_NO_ATTRIBUTE)
        throw MissingArgument(coordinatesElem.GetLineNum());
    if (y2LoadError == XMLError::XML_NO_ATTRIBUTE)
        throw MissingArgument(coordinatesElem.GetLineNum());

    if (xLoadError == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
        throw WrongArgumentFormat(coordinatesElem.GetLineNum());
    if (y1LoadError == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
        throw WrongArgumentFormat(coordinatesElem.GetLineNum());
    if (y2LoadError == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
        throw WrongArgumentFormat(coordinatesElem.GetLineNum());
}

void MapLoader::loadCoordinates(const tinyxml2::XMLElement& coordinatesElem,
                                float& x1, float& x2, float& y1, float& y2)
{
    XMLError x1LoadError = coordinatesElem.QueryFloatAttribute("x1", &x1);
    XMLError y1LoadError = coordinatesElem.QueryFloatAttribute("y1", &y1);
    XMLError x2LoadError = coordinatesElem.QueryFloatAttribute("x2", &x2);
    XMLError y2LoadError = coordinatesElem.QueryFloatAttribute("y2", &y2);

    if (x1LoadError == XMLError::XML_NO_ATTRIBUTE)
        throw MissingArgument(coordinatesElem.GetLineNum());
    if (x2LoadError == XMLError::XML_NO_ATTRIBUTE)
        throw MissingArgument(coordinatesElem.GetLineNum());
    if (y1LoadError == XMLError::XML_NO_ATTRIBUTE)
        throw MissingArgument(coordinatesElem.GetLineNum());
    if (y2LoadError == XMLError::XML_NO_ATTRIBUTE)
        throw MissingArgument(coordinatesElem.GetLineNum());

    if (x1LoadError == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
        throw WrongArgumentFormat(coordinatesElem.GetLineNum());
    if (x2LoadError == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
        throw WrongArgumentFormat(coordinatesElem.GetLineNum());
    if (y1LoadError == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
        throw WrongArgumentFormat(coordinatesElem.GetLineNum());
    if (y2LoadError == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
        throw WrongArgumentFormat(coordinatesElem.GetLineNum());
}

void MapLoader::loadTestThings()
{
//    TestFinalEntityBuilderSpawner().setPosition(5.0f, 10.0f).spawn();
//    ArcherBuilderSpawner().setPosition(10.0f, 2.0f).spawn();
//    ArcherBuilderSpawner().setPosition(15.0f, 2.0f).spawn();
//    ArcherBuilderSpawner().setPosition(20.0f, 2.0f).spawn();

    Player* player1 = PlayerBuilderSpawner()
            .setPosition(-10.0f, 2.0f)
            .setPlayerNum(1)
            .spawn();
    World::instance().setPlayer1(player1);

    Player* player2 = PlayerBuilderSpawner()
            .setPosition(10.0f, 2.0f)
            .setPlayerNum(2)
            .spawn();
    World::instance().setPlayer2(player2);
}
