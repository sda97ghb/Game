#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include "SFML/Graphics/Sprite.hpp"

class EntityView
{
public:
    virtual ~EntityView() = default;
    virtual const sf::Sprite& getSprite() = 0;
};

#endif // ENTITYVIEW_H
