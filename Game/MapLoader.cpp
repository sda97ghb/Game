#include "Game/MapLoader.h"
#include "Game/World.h"
#include "Game/PaintingWindow.h"
#include <iostream>
#include <vector>
#include <string>
using namespace tinyxml2;

World& _world = World::instance();

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
			
	const char* ENTITY = "actors";
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
	
MapLoader::MapLoader()
{

}

void MapLoader::loadMap(std::string filename)
{
	_document.LoadFile(filename.c_str());
	if (_document.Error())
	{
		_document.PrintError();
		throw XmlError(-1);
	}

	

	const XMLElement* world = _document.RootElement();
	if (std::string(world->Value()) != section::WORLD)
		throw IncorrectMapFormat(-1);

	const XMLElement* ground = world->FirstChildElement(section::GROUND);
	if (ground != nullptr)
		loadGround(*ground);

	const XMLElement* furniture = world->FirstChildElement(section::FURNITURE);
	if (furniture != nullptr)
		loadFurniture(*furniture);

	const XMLElement* entity = world->FirstChildElement(section::ENTITY);
	if (entity != nullptr)
		loadEntity(*entity);
}

void MapLoader::loadGround(const tinyxml2::XMLElement& ground)
{
	const XMLElement* background = ground.FirstChildElement(section::BACKGROUND);
	if (background)
	{
		loadBackground(*background);
	}
	const XMLElement* platforms = ground.FirstChildElement(section::PLATFORMS);

	for (const XMLElement* platform = platforms->FirstChildElement(section::PLATFORM);
		platform != nullptr; platform = platform->NextSiblingElement(section::PLATFORM))
		loadPlatform(*platform);
	
}

void MapLoader::loadBackground(const tinyxml2::XMLElement& background) 
{
	const std::string picture = background.Attribute("picture");
	PaintingWindow::instance().setBackground(picture);
}

void MapLoader::loadPlatform(const tinyxml2::XMLElement& platform)
{
	Platform& platform_ = _world.createPlatform();
	b2PolygonShape shape;

	const XMLElement& shapeElement = childElement(section::SHAPE, platform);
	std::vector<b2Vec2> _vertex;

	for (const XMLElement* vertexShape = shapeElement.FirstChildElement(section::VERTEX);
		vertexShape != nullptr; vertexShape = vertexShape->NextSiblingElement(section::VERTEX))
	{
		b2Vec2 coordinates;
		loadCoordinates(*vertexShape, coordinates);
		_vertex.push_back(coordinates);
	}

	

	shape.Set(&_vertex.front(), _vertex.size());
	platform_.setShape(shape);

	const XMLElement& textureElement = childElement(section::TEXTURE, platform);
	platform_.setTexture(textureElement.Attribute("picture"));
	

}

void MapLoader::loadFurniture(const tinyxml2::XMLElement& furniture)
{
	for (const XMLElement* ladder = furniture.FirstChildElement(section::LADDER);
		ladder != nullptr; ladder = ladder->NextSiblingElement(section::LADDER))
		loadLadder(*ladder);
	for (const XMLElement* water = furniture.FirstChildElement(section::WATER);
		water != nullptr; water = water->NextSiblingElement(section::WATER))
		loadWater(*water);
	for (const XMLElement* lava = furniture.FirstChildElement(section::LAVA);
		lava != nullptr; lava = lava->NextSiblingElement(section::LAVA))
		loadLava(*lava);
	
}

void MapLoader::loadLadder(const tinyxml2::XMLElement& ladder)
{
	Ladder& ladder_ = _world.createLadder();
	const XMLElement& coordinatesElement = childElement(section::COORDINATES, ladder);
	const XMLElement& widthElement = childElement(section::WIDTH, ladder);
	const XMLElement& textureElement = childElement(section::TEXTURE, ladder);

	float x ,y1 ,y2;
	const float width = std::atof(widthElement.GetText());

	loadCoordinates(coordinatesElement, x, y1, y2);
	ladder_.setCoordinates(x, y1, y2);
	ladder_.setWidth(width);
	ladder_.setTexture(textureElement.Attribute("picture"));
}

void MapLoader::loadWater(const tinyxml2::XMLElement& water)
{
	Water& water_ = _world.createWater();
	b2PolygonShape shape;
	const XMLElement& shapeElement = childElement(section::SHAPE, water);
	const XMLElement& textureElement = childElement(section::TEXTURE, water);
	const XMLElement& texturebackElement = childElement(section::TEXTUREBACK, water);
	std::vector<b2Vec2> _vertex;

	for (const XMLElement* vertexShape = shapeElement.FirstChildElement(section::VERTEX);
		vertexShape != nullptr; vertexShape = vertexShape->NextSiblingElement(section::VERTEX))
	{
		b2Vec2 coordinates;
		loadCoordinates(*vertexShape, coordinates);
		_vertex.push_back(coordinates);
	}

	shape.Set(&_vertex.front(), _vertex.size());
	water_.setShape(shape);
	water_.setTexture(textureElement.Attribute("picture"));
	water_.setTextureBack(texturebackElement.Attribute("picture"));
}

void MapLoader::loadLava(const tinyxml2::XMLElement& lava)
{
	Lava& lava_ = _world.createLava();
	b2PolygonShape shape;
	const XMLElement& shapeElement = childElement(section::SHAPE, lava);
	const XMLElement& textureElement = childElement(section::TEXTURE, lava);
	const XMLElement& texturebackElement = childElement(section::TEXTUREBACK, lava);

	std::vector<b2Vec2> _vertex;

	for (const XMLElement* vertexShape = shapeElement.FirstChildElement(section::VERTEX);
		vertexShape != nullptr; vertexShape = vertexShape->NextSiblingElement(section::VERTEX))
	{
		b2Vec2 coordinates;
		loadCoordinates(*vertexShape, coordinates);
		_vertex.push_back(coordinates);
	}

	shape.Set(&_vertex.front(), _vertex.size());
	lava_.setShape(shape);
	lava_.setTexture(textureElement.Attribute("picture"));
	lava_.setTextureBack(texturebackElement.Attribute("picture"));
}

void MapLoader::loadEntity(const tinyxml2::XMLElement& entity)
{
	const XMLElement* playerElement = entity.FirstChildElement(section::PLAYER);
	if (playerElement) loadPlayer(*playerElement);
}

void MapLoader::loadPlayer(const tinyxml2::XMLElement& player)
{
	Player& player_ = _world.player();
	SpriteAnimator& animator = player_.spriteAnimator();
	const XMLElement* positionElement = player.FirstChildElement(section::POSITION);
	const XMLElement& textureElement = childElement(section::TEXTURE, player);

	b2Vec2 coordinates;
	loadCoordinates(*positionElement, coordinates);
	player_.setPosition(coordinates.x, coordinates.y);

	animator.setTexture(textureElement.Attribute("picture"));
	loadAnimatorGroup(animator);
}

void MapLoader::loadAnimatorGroup(SpriteAnimator& animator)
{
	animator.setAnimationGroup("going_left", 0, 0, 12, 28, 4, false);
	animator.setAnimationGroup("going_right", 12, 0, 12, 28, 4, false);
	animator.setAnimationGroup("climbing", 24, 0, 12, 28, 2, false);
	animator.setAnimationGroup("punching_right", 36, 0, 15, 28, 3, true);
	animator.setAnimationGroup("punching_left", 36, 28, 15, 28, 3, true);
	animator.setAnimationGroup("dead", 52, 56, 28, 28, 1, true);
	animator.setCurrentGroup("going_right");
}

const XMLElement& MapLoader::childElement(const std::string elementName,
	const XMLElement& element)
{
	const XMLElement* childElement = element.FirstChildElement(elementName.c_str());
	if (childElement == nullptr)
		throw NotExistChildElement(element.GetLineNum(), element.Name(), elementName.c_str());

	return *childElement;

}

void MapLoader::loadCoordinates(const tinyxml2::XMLElement& element, b2Vec2& coordinates)
{
	float x = 0.0f, y = 0.0f;
	XMLError e = element.QueryFloatAttribute("x", &x);
	XMLError e_two = element.QueryFloatAttribute("y", &y);

	if (e == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
		throw WrongArgumentFormat(element.GetLineNum());
	if (e_two == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
		throw WrongArgumentFormat(element.GetLineNum());
	if (e == XMLError::XML_NO_ATTRIBUTE)
		throw MissingArgument(element.GetLineNum());
	if (e_two == XMLError::XML_NO_ATTRIBUTE)
		throw MissingArgument(element.GetLineNum());

	coordinates.Set(x, y);
}

void MapLoader::loadCoordinates(const tinyxml2::XMLElement& element, float& x, float& y1, float& y2)
{
	XMLError e = element.QueryFloatAttribute("x", &x);
	XMLError e_two = element.QueryFloatAttribute("y1", &y1);
	XMLError e_three = element.QueryFloatAttribute("y2", &y2);

	if (e == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
		throw WrongArgumentFormat(element.GetLineNum());
	if (e_two == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
		throw WrongArgumentFormat(element.GetLineNum());
	if (e_three == XMLError::XML_WRONG_ATTRIBUTE_TYPE)
		throw WrongArgumentFormat(element.GetLineNum());
	if (e == XMLError::XML_NO_ATTRIBUTE)
		throw MissingArgument(element.GetLineNum());
	if (e_two == XMLError::XML_NO_ATTRIBUTE)
		throw MissingArgument(element.GetLineNum());
	if (e_three == XMLError::XML_NO_ATTRIBUTE)
		throw MissingArgument(element.GetLineNum());
}

void MapLoader::loadCoordinates(const tinyxml2::XMLElement& element, float& x1, float& x2, float& y1, float& y2)
{

}
