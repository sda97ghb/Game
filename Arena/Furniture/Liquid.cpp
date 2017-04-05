#include "Arena/Furniture/Liquid.h"

void Liquid::setShape(const b2PolygonShape& shape)
{
    _shapeB2 = shape;
}

void Liquid::setTextureBack(const std::string& filename)
{
    _textureBack.loadFromFile(filename);
    _textureBack.setRepeated(true);
}

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
