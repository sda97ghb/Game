#ifndef IMAGESCALER_H
#define IMAGESCALER_H

#include <SFML/Graphics/Texture.hpp>

class ImageScaler
{
public:
    static sf::Image scale(const sf::Image& original);
};

#endif // IMAGESCALER_H
