/// \file
/// \brief Содержит класс масштабирования sf::Image изображений.

#ifndef IMAGESCALER_H
#define IMAGESCALER_H

#include "SFML/Graphics/Image.hpp"

/// \brief Класс масштабирования изображения sf::Image.
class ImageScaler
{
public:
    /// \brief Масштабирует изображение, увеличивая в два раза.
    /// \note Не сглаживает при масштабировании.
    /// \return Увеличенную копию изображения.
    static sf::Image scale(const sf::Image& original);
};

#endif // IMAGESCALER_H
