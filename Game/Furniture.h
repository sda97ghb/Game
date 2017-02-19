#ifndef FURNITURE_H
#define FURNITURE_H

#include <SFML/Graphics.hpp>

class Furniture
{
public:
    Furniture();

    void setTexture(const std::string& filename);

    sf::Sprite& sprite();
    sf::Texture& texture();

    virtual void testPlayerOnIt() = 0;

private:
    sf::Sprite _sprite;
    sf::Texture _texture;
};

#endif // FURNITURE_H
