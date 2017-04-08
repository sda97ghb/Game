/// \file
/// \brief Содержит класс отрисовки, ответственный за создание
/// графического окна и отрисовку текущего кадра и пользовательского
/// интерфейса.

#ifndef PAINTER_H
#define PAINTER_H

#include <list>

#include "SFML/Graphics/ConvexShape.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/View.hpp"

#include "Arena/Entity/TestFinalEntityView.h"

#include "Arena/Furniture/Ladder.h"
#include "Arena/Furniture/Lava.h"
#include "Arena/Furniture/Spikes.h"
#include "Arena/Furniture/Water.h"

#include "Arena/Platform.h"

/// \brief Класс, отвечающий за графическую составляющую игры.
/// \details Создает графическое окно, занимается отрисовкой
/// текущего кадра и пользовательского интерфейса.
class PaintingWindow : public sf::RenderWindow
{
public:
	static PaintingWindow& instance();
	void setBackground(const std::string& background);

    /// \brief Рисует содеримое окна (мир, интерфейс пользователя).
    void paint();

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

	/// \brief Подготавливает для отрисовки прямоугольник для шипов.
	sf::RectangleShape& constructSpikes(Spikes& spikes);

    /// \brief Подготавливает для отрисовки многоугольник для воды.
    sf::ConvexShape& constructWater(Water& water, bool isFront = true);

    /// \brief Подготавливает для отрисовки многоугольник для лавы.
    sf::ConvexShape& constructLava(Lava& lava, bool isFront = true);

    /// \brief Вызывает обработчики событий.
    void processEvents();

    void addEntityView(TestFinalEntityView&& entityView);

private:
	/// \brief Создает графическое окно, инициализирует графику.
	PaintingWindow(uint32_t width, uint32_t height, const std::string& title);

	PaintingWindow(PaintingWindow const&) = delete;
	PaintingWindow& operator= (PaintingWindow const&) = delete;

    sf::RenderWindow* _window; ///< Графическое окно.
    sf::View _worldView; ///< Текущая область мира, которую нужно нарисовать.
    sf::View _guiView; ///< Вид для интерфейса.
    sf::View _backgroundView; ///< Вид для мира.

    sf::Texture _backgroundTexture; ///< Текстура фона
    sf::Sprite _background; ///< Фон
	
	sf::Font font; ///< Шрифт для лога

    std::list<TestFinalEntityView> _entityViews;
};

#endif // PAINTER_H
