#include <iostream>

#include "SFML/Window/Event.hpp"

#include "Arena/Menu.h"
#include "Arena/MapLoader.h"
#include "Arena/MapUnloader.h"
#include "Arena/GlobalConstants.h"
#include "Arena/PaintingWindow.h"

Menu& Menu::instance()
{
    static Menu instance;
    return instance;
}

Menu::Menu() : _isShown(true),_isShownOptions(false),
               _selectedItemIndex(0)
{
    auto& font = PaintingWindow::instance().font();

    auto nextTop = [](uint8_t index)
    {
        const uint32_t itemHeight = 40; // 40px
        return itemHeight * index;
    };

    auto setItem = [&](uint8_t index, sf::Color color, std::string text, std::function<void()> action)
    {
        _menuItems.emplace_back();
        _menuItems.back().action = action;
        sf::Text& itemView = _menuItems.back().itemView;
        itemView.setFont(font);
        itemView.setFillColor(color);
        itemView.setString(text);
        itemView.setPosition(sf::Vector2f(SCREEN_RESOLUTION_X / 2 - 25,
                                               30 + nextTop(index)));
    };

    // Главное меню
    setItem(0, sf::Color::Red,   "Arena",    [&]()
    {
        MapLoader().safeLoadFromFile("MapLevels/ARENA.xml");
        PaintingWindow::instance().setYFloorOffset(4.5f);
        hide();
    });
    setItem(1, sf::Color::White, "Options", [&](){Optoins();});
    setItem(2, sf::Color::White, "Exit",    [&](){Exit();});

    // Меню с уровнями
    setItem(0, sf::Color::Red,   "Level 1", [&]()
    {
        MapLoader().safeLoadFromFile("MapLevels/LEVEL_ONE.xml");
        PaintingWindow::instance().setYFloorOffset(8.8f);
        hide();
    });
    setItem(1, sf::Color::White, "Level 2", [&]()
    {
        MapLoader().safeLoadFromFile("MapLevels/LEVEL_TWO.xml");
        PaintingWindow::instance().setYFloorOffset(8.8f);
        _menuItems[3].itemView.setFillColor(sf::Color::Red);
        _menuItems[4].itemView.setFillColor(sf::Color::White);
        hide();
    });
    setItem(2, sf::Color::White, "Back", [&](){Back();});
}

Menu::~Menu()
{

}

void Menu::drawMenu()
{
    auto& window = PaintingWindow::instance();
    window.prepareForGui();

    for(int i = 0; i < 3; i++)
    {
        window.draw(_menuItems[i].itemView);
    }
}

void Menu::drawOptions()
{
    auto& window = PaintingWindow::instance();
    window.prepareForGui();

    for(int i = 3; i < 6; i++)
    {
        window.draw(_menuItems[i].itemView);
    }
}

void Menu::Optoins()
{
    _isShown = false;
    _isShownOptions = true;
    _selectedItemIndex = 3;
    _menuItems[0].itemView.setFillColor(sf::Color::Red);
    _menuItems[1].itemView.setFillColor(sf::Color::White);
}

void Menu::Exit()
{
    PaintingWindow::instance().close();
    MapUnloader().unload();
}

void Menu::Back()
{
    _isShown = true;
    _isShownOptions = false;
    _selectedItemIndex = 0;
    _menuItems[3].itemView.setFillColor(sf::Color::Red);
    _menuItems[5].itemView.setFillColor(sf::Color::White);
}

void Menu::MoveUp()
{
    if(_isShown)
        _min = 0;
    if(_isShownOptions)
        _min = _menuItems.size() - _selectedItemIndex;

    if(_selectedItemIndex > _min)
    {
        _menuItems[_selectedItemIndex].itemView.setFillColor(sf::Color::White);
        _selectedItemIndex--;
        _menuItems[_selectedItemIndex].itemView.setFillColor(sf::Color::Red);
        std::cout << "Up" << std::endl;
    }
}

void Menu::MoveDown()
{
    if(_isShown)
        _max = 3;
    if(_isShownOptions)
        _max = _menuItems.size();

    if(_selectedItemIndex + 1 < _max)
    {
        _menuItems[_selectedItemIndex].itemView.setFillColor(sf::Color::White);
        _selectedItemIndex++;
        _menuItems[_selectedItemIndex].itemView.setFillColor(sf::Color::Red);
        std::cout << "Down" << std::endl;
    }
}

bool Menu::isShown() const
{
    return _isShown;
}

bool Menu::isShownOptions() const
{
    return _isShownOptions;
}

void Menu::onKeyReleased(sf::Event::KeyEvent event)
{
    if(!isShown() && !isShownOptions())
        return;

    switch(event.code)
    {
    case sf::Keyboard::Up :
        MoveUp();
        break;
    case sf::Keyboard::Down :
        MoveDown();
        break;
    case sf::Keyboard::Return :
        _menuItems.at(_selectedItemIndex).action();
    default :
        break;
    }
}

uint32_t Menu::getSelectedItemIndex() const
{
    return _selectedItemIndex;
}

void Menu::show()
{
    if (_isShownOptions == true)
        _isShown = false;
    else
        _isShown = true;
}

void Menu::hide()
{
    _isShown = false;
    _isShownOptions = false;
    _selectedItemIndex = 0;
    _menuItems[0].itemView.setFillColor(sf::Color::Red);
    _menuItems[1].itemView.setFillColor(sf::Color::White);
    _menuItems[2].itemView.setFillColor(sf::Color::White);
}
