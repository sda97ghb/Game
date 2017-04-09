#ifndef ARCHERVIEW_H
#define ARCHERVIEW_H

#include "Arena/SpriteAnimator.h"

#include "Arena/Entity/Archer.h"
#include "Arena/Entity/EntityView.h"

class ArcherView : public EntityView
{
public:
    ArcherView(const Archer& archer);

    const sf::Sprite& getSprite();

private:
    const Archer& _archer;
    SpriteAnimator _animator;
};

#endif // ARCHERVIEW_H
