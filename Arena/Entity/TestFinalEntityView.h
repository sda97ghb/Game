#ifndef TESTFINALENTITYVIEW_H
#define TESTFINALENTITYVIEW_H

#include "SFML/Graphics/Sprite.hpp"

#include "Arena/SpriteAnimator.h"

#include "Arena/Entity/EntityView.h"
#include "Arena/Entity/TestFinalEntity.h"

class TestFinalEntityView : public EntityView
{
public:
    TestFinalEntityView(const TestFinalEntity& entity);

    const sf::Sprite& getSprite();

private:
    const TestFinalEntity& _entity;
    SpriteAnimator _animator;
};

#endif // TESTFINALENTITYVIEW_H
