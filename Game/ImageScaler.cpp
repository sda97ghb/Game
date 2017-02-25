#include "Game/ImageScaler.h"

sf::Image ImageScaler::scale(const sf::Image& original)
{
    sf::Image scaled;
    scaled.create(original.getSize().x * 2, original.getSize().y * 2);
    for (uint32_t x = 0; x < scaled.getSize().x; ++ x)
        for (uint32_t y = 0; y < scaled.getSize().y; ++ y)
            scaled.setPixel(x, y, original.getPixel(x / 2, y / 2));
    return scaled;
}
