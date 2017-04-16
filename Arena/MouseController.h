/// \file
/// \brief Содержит класс обработки мыши.

#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include "SFML/Window/Event.hpp"

/// \brief Класс обработки мыши.
class MouseController
{
public:
    /// \brief Обработка текущего состояния мыши.
    static void processMouse();

    static void processMousePressed(const sf::Event::MouseButtonEvent& event);
};

#endif // MOUSECONTROLLER_H
