#include "Game/ImageScaler.h"
#include "Game/Liquid.h"

void Liquid::setShape(const b2PolygonShape& shape)
{
    _shapeB2 = shape;
}

void Liquid::setTextureBack(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _textureBack.loadFromImage(ImageScaler::scale(original));
    _textureBack.setRepeated(true);
}

//void Liquid::setTextureFront(const std::string& filename)
//{
//    sf::Image original;
//    original.loadFromFile(filename);
//    _textureFront.loadFromImage(ImageScaler::scale(original));
//    _textureFront.setRepeated(true);
//}

b2PolygonShape& Liquid::shapeB2()
{
    return _shapeB2;
}

const b2PolygonShape& Liquid::shapeB2() const
{
    return _shapeB2;
}

sf::ConvexShape& Liquid::shapeSF()
{
    return _shapeSF;
}

const sf::ConvexShape& Liquid::shapeSF() const
{
    return _shapeSF;
}

sf::Texture& Liquid::textureBack()
{
    return _textureBack;
}

const sf::Texture& Liquid::textureBack() const
{
    return _textureBack;
}

//sf::Texture& Liquid::textureFront()
//{
//    return _textureFront;
//}

//const sf::Texture& Liquid::textureFront() const
//{
//    return _textureFront;
//}
