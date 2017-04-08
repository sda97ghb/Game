#include <iostream>

#include "Arena/GlobalConstants.h"

#include "Arena/Entity/TestFinalEntityView.h"

TestFinalEntityView::TestFinalEntityView(const TestFinalEntity& entity) :
    _entity(entity)
{
    _animator.setTexture("Textures/panther.png");

    _animator.setAnimationGroup("going_left", 32, 0, 32, 12, 2, Orientation::vertical);
    _animator.setAnimationGroup("going_right", 0, 0, 32, 12, 2, Orientation::vertical);
    _animator.setAnimationGroup("climbing", 0, 0, 5, 9, 1, Orientation::vertical);
    _animator.setAnimationGroup("punching_right", 64, 0, 32, 12, 2, Orientation::vertical);
    _animator.setAnimationGroup("punching_left", 96, 0, 32, 12, 2, Orientation::vertical);
    _animator.setAnimationGroup("dead", 0, 24, 32, 12);

    _animator.setCurrentGroup("going_right");

    _animator.nextFrame();
}

const sf::Sprite& TestFinalEntityView::getSprite()
{
    static bool f = true;
    if (f)
    {
        f = false;
        _animator.setTexture("Textures/panther.png");
    }

    _animator.update();

    if (!_entity.isAlive())
    {
        _animator.playGroup("dead");
        _animator.nextFrame();
        _animator.stop();
    }
    sf::Sprite& sprite = _animator.sprite();

    sprite.setScale(1.0f / PIXELS_PER_METER, -1.0f / PIXELS_PER_METER);

    b2Vec2 pos = _entity.position();
    sf::Vector2f posSF = sf::Vector2f(pos.x, pos.y);
    posSF.x -= sprite.getTextureRect().width / PIXELS_PER_METER / 2.0f;
    posSF.y += sprite.getTextureRect().height / PIXELS_PER_METER / 2.0f;
    sprite.setPosition(posSF);

    return sprite;
}
