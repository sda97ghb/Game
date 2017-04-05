#include "Arena/Furniture.h"

Furniture::Furniture()
{
}

void Furniture::setTexture(const std::string& filename)
{
	sf::Image image;
	image.loadFromFile(filename);
	image.flipVertically();
	_texture.loadFromImage(image);
    _texture.setRepeated(true);
}

sf::Texture& Furniture::texture()
{
    return _texture;
}
