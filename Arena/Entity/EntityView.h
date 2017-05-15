#ifndef ENTITYVIEW_H
#define ENTITYVIEW_H

#include "SFML/Graphics/Sprite.hpp"

class Entity;

/// @brief Интерфейс класса-отображения существа.
class EntityView
{
public:
    EntityView();
    virtual ~EntityView();

    virtual const sf::Sprite& getSprite() = 0;

    virtual const Entity* entity() const = 0;
};

#endif // ENTITYVIEW_H
