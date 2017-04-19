#include "Arena/GlobalConstants.h"

#include "Arena/Entity/ArrowView.h"

ArrowView::ArrowView(const Arrow& arrow) :
    _arrow(arrow)
{
    _texture.loadFromFile("Textures/arrow.png");
    _sprite.setTexture(_texture);
    _sprite.setTextureRect(sf::IntRect(0, 0, 3, 1));
}

const sf::Sprite& ArrowView::getSprite()
{
    _sprite.setOrigin(0.6f / 2.0f, 0.1f / 2.0f);

    _sprite.setScale(1.0f / PIXELS_PER_METER, 1.0f / PIXELS_PER_METER);

    float angle = _arrow.body()->GetAngle();
    angle *= 180.0 / 3.1415;
    _sprite.setRotation(angle);

    b2Vec2 position = _arrow.body()->GetPosition();
    _sprite.setPosition(sf::Vector2f(position.x, position.y));

    return _sprite;
}

const Entity* ArrowView::entity() const
{
    return &_arrow;
}
