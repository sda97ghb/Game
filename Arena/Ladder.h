/// \file
/// \brief Содержит класс лестницы.

#ifndef LADDER_H
#define LADDER_H

#include "SFML/Graphics/RectangleShape.hpp"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"

#include "Arena/Furniture.h"

/// \brief Класс лестницы.
class Ladder : public Furniture
{
public:
    Ladder();

    /// \brief Устанавливает местоположение лестницы
    /// \param [in] x центр лестницы по оси X
    /// \param [in] y1 нижняя граница лестницы
    /// \param [in] y2 верхняя граница лестницы
    void setCoordinates(float x, float y1, float y2);

    /// \brief Устанавливает ширину лестницы.
    void setWidth(float width);

    /// \brief Проверяет взаимодействие с игроком.
    /// \details Если взаимодействует, то останавливает игрока,
    /// при зажатой кнопке вверх или вниз поднимает или опускает
    /// соответственно. Переключает анимацию на лазание.
    void testPlayerOnIt();

    /// \brief Физическая координата центра лестницы вдоль оси X.
    float x() const;

    /// \brief Физическая координата нижней границы лестницы.
    float y1() const;

    /// \brief Физическая координата верхней границы лестницы.
    float y2() const;

    /// \brief Физическая ширина лестницы.
    float width() const;

    /// \brief Физическая высота лестницы.
    float height() const;

    /// \brief Физический размер лестницы.
    b2Vec2 size() const;

    /// \brief Физическая фигура лестницы.
    b2PolygonShape& shapeB2();
    const b2PolygonShape& shapeB2() const;

    /// \brief Графическая фигура лестницы.
    sf::RectangleShape& shapeSF();
    const sf::RectangleShape& shapeSF() const;

private:
    /// \brief Рассчитывает и устанавливает физическую форму лестницы.
    void setShape();

    float _x;  ///< Координата центра лестницы по X
    float _y1; ///< Нижняя граница лестницы
    float _y2; ///< Верхняя граница лестницы
    float _width; ///< Ширина лестницы

    b2PolygonShape _shapeB2; ///< Физическая фигура лестницы.
    sf::RectangleShape _shapeSF; ///< Графическая фигура лестницы.
};

#endif // LADDER_H
