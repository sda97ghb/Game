#include "Game/Furniture.h"
#include "Game/ImageScaler.h"

Furniture::Furniture()
{
}

void Furniture::setTexture(const std::string& filename)
{
	sf::Image texture;
	texture.loadFromFile(filename);
	_texture.loadFromImage(ImageScaler::scale(texture));
    _texture.setRepeated(true);
}

sf::Texture& Furniture::texture()
{
    return _texture;
}
