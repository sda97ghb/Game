/// \file
/// \brief Содержит класс, ответсвенный за загрузку мира.
#ifndef MAPLOADER_H
#define MAPLOADER_H

#include "TinyXml2\tinyxml2.h"
#include "Box2D\Box2D.h"
#include <string>
#include <stdexcept>
class SpriteAnimator;

#define DEFINE_ERROR(error_name, error_message) \
    struct error_name : public std::logic_error {\
        error_name(int lineNum) : logic_error(error_message), _lineNum(lineNum) {}\
        int _lineNum;\
	    };
#define DEFINE_ERROR_USER_MSG(error_name, error_message) \
    struct error_name : public std::logic_error {\
        error_name(int lineNum) : logic_error(error_message), _lineNum(lineNum) {}\
		error_name(char elementName): logic_error(error_message), _elementName(elementName) {}\
        int _lineNum;\
		char _elementName;\
	    };



class MapLoader
{
public:
	DEFINE_ERROR(XmlError, "Probably you trying to load incorrect xml file.")
	DEFINE_ERROR(IncorrectMapFormat, "Incorrect map format")
	DEFINE_ERROR(MissingArgument, "must be x and y")
	DEFINE_ERROR(WrongArgumentFormat, "must be float")
	DEFINE_ERROR(NotEnoughVertexes, "polygon must contain at least 3 vertexes")

	struct NotExistChildElement : public std::logic_error {
		NotExistChildElement(int lineNum, std::string parentElement, std::string childElement) :
			logic_error(parentElement + " doesn't have child " + childElement), _lineNum(lineNum) {}

		int _lineNum;
		char _elementName;
	};

	MapLoader();

	void loadMap(std::string filename);
	/// \brief Функция загрузки Земли
	void loadGround(const tinyxml2::XMLElement& ground);
	void loadBackground(const tinyxml2::XMLElement& background);
	void loadPlatform(const tinyxml2::XMLElement& platform);

	/// \brief Функция загрузки Фурнитуры
	void loadFurniture(const tinyxml2::XMLElement& furniture);
	void loadLadder(const tinyxml2::XMLElement& ladder);
	void loadCable(const tinyxml2::XMLElement& cable);
	void loadRope(const tinyxml2::XMLElement& rope);
	void loadSpikes(const tinyxml2::XMLElement& spikes);
	void loadFallingGround(const tinyxml2::XMLElement& fallingground);
	void loadWater(const tinyxml2::XMLElement& water);
	void loadLava(const tinyxml2::XMLElement& lava);

	/// \brief Функция загрузки Сущности
	void loadEntity(const tinyxml2::XMLElement& entity);
	void loadPlayer(const tinyxml2::XMLElement& player);
	void loadAnimatorGroup(SpriteAnimator& animator);

	const tinyxml2::XMLElement& childElement(const std::string elementName, const tinyxml2::XMLElement& element);
	void loadCoordinates(const tinyxml2::XMLElement& element, b2Vec2& coordinates);
	void loadCoordinates(const tinyxml2::XMLElement& element, float& x, float& y1, float& y2);
	void loadCoordinates(const tinyxml2::XMLElement& element, float& x1, float& x2, float& y1, float& y2);

private:
	
	tinyxml2::XMLDocument _document;
	
	
	
};

#endif // MAPLOADER_H
