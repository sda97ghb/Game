#ifndef MENU_H
#define MENU_H

#include <functional>
#include <vector>

#include "SFML/Graphics/Text.hpp"
#include "SFML/Window/Event.hpp"

class Menu
{
public:
    struct MenuItem
    {
        sf::Text itemView;
        std::function<void()> action;
    };

    static Menu& instance();

    Menu();
    ~Menu();

    void drawMenu();
    void drawOptions();
    void Optoins();
    void Exit();
    void Back();
    void MoveUp();/// @brief Вверх на один пункт меню
    void MoveDown();/// @brief Вниз на один пункт меню
    bool isShown() const;
    bool isShownOptions() const;

    void onKeyReleased(sf::Event::KeyEvent event);

    uint32_t getSelectedItemIndex() const;

    /// @brief Показать меню
    void show();
    /// @brief Скрыть меню
    void hide();

private:
    bool _isShown; // Открыто ли сейчас меню?
    bool _isShownOptions;
    uint32_t _selectedItemIndex;
    std::vector<MenuItem> _menuItems;
    uint32_t _max;
    uint32_t _min;
};

#endif // MENU_H
