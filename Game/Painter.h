/// \file
/// \brief Содержит класс отрисовки, ответственный за создание
/// графического окна и отрисовку текущего кадра и пользовательского
/// интерфейса.

#ifndef PAINTER_H
#define PAINTER_H

#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/View.hpp"

#include "Game/Archer.h"
#include "Game/Entity.h"
#include "Game/Ladder.h"
#include "Game/Platform.h"

/// \brief Класс, отвечающий за графическую составляющую игры.
/// \details Создает графическое окно, занимается отрисовкой
/// текущего кадра и пользовательского интерфейса.
class Painter
{
public:
    ~Painter();

    /// \brief Создает графическое окно, инициализирует графику.
    void initialize();

    /// \brief Возвращает ссылку на графическое окно.
    sf::RenderWindow& window();

    /// \brief Рисует фоновое изображение.
    void drawBackground();

    /// \brief Рисует мир (background, платформы, объекты взаимодействия, существ)
    void drawWorld();

    /// \brief Рисует GUI (lifebar'ы, manabar'ы)
    void drawGui();

    /// \brief Рисует чат.
    void drawLog();

    /// \brief Рисует полоску под лайфбар или манабар.
    /// \param [in] x,y положение полоски в графических координатах
    /// \param [in] width ширина полоски
    /// \param [in] height высота полоски
    /// \param [in] border ширина черной обводки
    /// \param [in] value дробное значение на отрезке от 0 до 1,
    /// где 0 - полностью пустая полоска, 1 - полностью заполненная
    /// \param [in] color цвет, например sf::Color::red или sf::Color(10, 20, 30)
    void drawBar(float x, float y, float width, float height,
                 float border, float value, sf::Color color);

    /// \brief Подготавливает к отрисовке многоугольник для платформы
    sf::ConvexShape& constructPlatform(Platform& platform);

    /// \brief Подготавливает для отрисовки прямоугольник для лестницы.
    sf::RectangleShape& constructLadder(Ladder& ladder);

    /// \brief Подготавливает для отрисовки спрайт для существа.
    sf::Sprite& constructEntity(Entity& entity);

    /// \brief Подготавливает для отрисовки спрайт для игрока.
    sf::Sprite& constructPlayer();

    /// \brief Подготавливает для отрисовки спрайт для  лучника.
    sf::Sprite& constructArcher(Archer& archer);

private:
    /// \brief Настраивает _view для рисования мира (платформ, фурнитуры, существ).
    /// \return Коодинаты нового центра _view.
    sf::Vector2f setViewForWorld();

    /// \brief Настраивает _view для рисования gui.
    void setViewForGui();

    sf::RenderWindow* _window; ///< Графическое окно
    sf::View* _view; ///< Текущая область мира, которую нужно нарисовать.

    sf::Texture _backgroundTexture; ///< Текстура фона
    sf::Sprite _background; ///< Фон
};

#endif // PAINTER_H
