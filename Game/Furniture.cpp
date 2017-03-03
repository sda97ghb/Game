#include "Game/Furniture.h"

Furniture::Furniture()
{
}

void Furniture::setTexture(const std::string& filename)
{
    _texture.loadFromFile(filename);
    _texture.setRepeated(true);
}

sf::Texture& Furniture::texture()
{
    return _texture;
}
