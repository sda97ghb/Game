/// \file
/// \brief Содержит класс троса.

#ifndef CABLE_H
#define CABLE_H

#include "SFML/Graphics/ConvexShape.hpp"

#include "Box2D/Collision/Shapes/b2PolygonShape.h"

#include "Arena/Furniture.h"

/// \brief Класс троса, растянутого между двумя точками.
class Cable : public Furniture
{
public:
    Cable();

    /// \brief Устанавливает начальную точку троса.
    void setBegin(float x, float y);

    /// \brief Устанавливает конечную точку троса.
    void setEnd(float x, float y);

    /// \brief Проверяет взаимодействие с игроком.
    /// \details Если взаимодействует, то останавливает игрока,
    /// при зажатой кнопке влево или вправо поднимает или опускает
    /// соответственно. Переключает анимацию на лазание.
    void testPlayerOnIt();

    float x1() const;
    float x2() const;
    float y1() const;
    float y2() const;

private:
    /// \brief Рассчитывает и устанавливает физическую форму лестницы.
    void setShape();

    float _x1; ///< Координата начала по X.
    float _y1; ///< Координата начала по Y.
    float _x2; ///< Координата конца по X.
    float _y2; ///< Координата конца по Y.

    b2PolygonShape _shapeB2;  ///< Физическая фигура троса.
    sf::ConvexShape _shapeSF; ///< Графическая фигура троса.
};

#endif // CABLE_H
