#ifndef ARROWVIEW_H
#define ARROWVIEW_H

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"

#include "Arena/Entity/Arrow.h"
#include "Arena/Entity/EntityView.h"

class ArrowView : public EntityView
{
public:
    ArrowView(const Arrow& arrow);

    const sf::Sprite& getSprite();

    const Entity* entity() const;

private:
    const Arrow& _arrow;
    sf::Sprite _sprite;
    sf::Texture _texture;
};

#endif // ARROWVIEW_H
