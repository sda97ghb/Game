/// @file
/// @brief Содержит класс, ответсвенный за загрузку мира.

#ifndef MAPLOADER_H
#define MAPLOADER_H

#include <stdexcept>
#include <string>

#include "TinyXml2\tinyxml2.h"

#include "Box2D\Box2D.h"

class SpriteAnimator;

#define DEFINE_ERROR(error_name, error_message) \
    struct error_name : public std::logic_error {\
        error_name(int lineNum) : logic_error(error_message), _lineNum(lineNum) {}\
        int _lineNum;\
    };
#define DEFINE_ERROR_USER_MSG(error_name, error_message) \
    struct error_name : public std::logic_error {\
        error_name(int lineNum) : logic_error(error_message), _lineNum(lineNum) {}\
        int _lineNum;\
    };

/// @brief Загрузчик карты.
/// @details Загружает карту из файла.
class MapLoader
{
public:
	DEFINE_ERROR(XmlError, "Probably you trying to load incorrect xml file.")
	DEFINE_ERROR(IncorrectMapFormat, "Incorrect map format")
	DEFINE_ERROR(MissingArgument, "must be x and y")
	DEFINE_ERROR(WrongArgumentFormat, "must be float")
	DEFINE_ERROR(NotEnoughVertexes, "polygon must contain at least 3 vertexes")

    struct NoChildElementException : public std::logic_error
    {
        NoChildElementException(int lineNum,
                                std::string parent,
                                std::string child) :
            logic_error(parent + " doesn't have child element " + child),
            _lineNum(lineNum),
            parentElementName(parent),
            childElementName(child)
        {}

		int _lineNum;
        std::string parentElementName;
        std::string childElementName;
	};

    /// @brief Загружает карту из файла сохранения.
    /// @details Смотрите "Формат уровней. XML стандарт" для получения информации
    /// о формате карт.
    void loadFromFile(std::string filename);

    /// @brief Загружает фон и платформы.
    void loadGround(const tinyxml2::XMLElement& groundElem);

    /// @brief Загружает фоновое изображение.
    void loadBackground(const tinyxml2::XMLElement& backgroundElem);

    /// @brief Загружает платформу.
    void loadPlatform(const tinyxml2::XMLElement& platformElem);

    /// @brief Загружает Фурнитуру.
    void loadFurniture(const tinyxml2::XMLElement& furnitureElem);

    /// @brief Загружает лестницу.
    void loadLadder(const tinyxml2::XMLElement& ladderElem);

    /// @brief Загружает трос.
    void loadCable(const tinyxml2::XMLElement& cableElem);

    /// @brief Загружает канат.
    void loadRope(const tinyxml2::XMLElement& ropeElem);

    /// @brief Загружает шипы.
    void loadSpikes(const tinyxml2::XMLElement& spikesElem);

    /// @brief Загружает осыпающуюся землю.
    void loadFallingGround(const tinyxml2::XMLElement& fallingGroundElem);

    /// @brief Загружает водоем.
    void loadWater(const tinyxml2::XMLElement& waterElem);

    /// @brief Загружает лавоем.
    void loadLava(const tinyxml2::XMLElement& lavaElem);

    /// @brief Загружает существо.
    void loadEntity(const tinyxml2::XMLElement& entityElem);

    /// @brief Загружает игрока.
    void loadPlayer(const tinyxml2::XMLElement& playerElem);

    /// @brief Загружает группы анимации для существа.
    void loadPlayerAnimator(SpriteAnimator& animator);

    /// @brief Загружает полигон.
    b2PolygonShape loadPolygonShape(const tinyxml2::XMLElement& shapeElem);

    /// @brief Возвращает дочерний элемент, если он существует. Иначе кидает
    /// исключение.
    const tinyxml2::XMLElement& childElement(const std::string elementName,
                                     const tinyxml2::XMLElement& parentElement);

    /// @brief Загружает координаты.
    void loadCoordinates(const tinyxml2::XMLElement& coordinatesElem,
                         b2Vec2& coordinates);

    /// @brief Загружает координаты.
    void loadCoordinates(const tinyxml2::XMLElement& coordinatesElem,
                         float& x, float& y1, float& y2);

    /// @brief Загружает координаты.
    void loadCoordinates(const tinyxml2::XMLElement& coordinatesElem,
                         float& x1, float& x2, float& y1, float& y2);

private:
    /// @brief Загружает тестовые предметы НЕ ИЗ ФАЙЛА.
    /// @note Нужна исключительно для отладки.
    void loadTestThings();

    tinyxml2::XMLDocument _document; ///< Открытый файл сохранения.
};

#endif // MAPLOADER_H
