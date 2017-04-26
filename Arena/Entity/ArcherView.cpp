#include "Arena/GlobalConstants.h"

#include "Arena/Entity/ArcherView.h"

ArcherView::ArcherView(const Archer& archer) :
    _archer(archer)
{
    _animator.setTexture("Textures/archer.png");

    _animator.setAnimationGroup("going_left", 0, 0, 7, 9, 2, Orientation::horizontal);
    _animator.setAnimationGroup("going_right", 0, 9, 7, 9, 2, Orientation::horizontal);
    _animator.setAnimationGroup("climbing", 12, 0, 12, 28, 2, Orientation::vertical);
    _animator.setAnimationGroup("firing_left", 24, 0, 18, 28, 5, Orientation::horizontal);
    _animator.setAnimationGroup("firing_right", 24, 28, 18, 28, 5, Orientation::horizontal);
    _animator.setAnimationGroup("dead", 0, 0, 12, 28);

    _animator.setCurrentGroup("going_left");
    _animator.nextFrame();
}

const sf::Sprite& ArcherView::getSprite()
{
    static bool f = true;
    if (f)
    {
        f = false;
        _animator.setTexture("Textures/archer.png");
    }

    _animator.update();

    if (!_archer.isAlive())
    {
        _animator.playGroup("dead");
        _animator.nextFrame();
        _animator.stop();
    }
    if (_archer.lookingDirection() == Direction::left)
        _animator.setCurrentGroup("going_left");
    else
        _animator.setCurrentGroup("going_right");

    sf::Sprite& sprite = _animator.sprite();

    sprite.setScale(1.0f / PIXELS_PER_METER, -1.0f / PIXELS_PER_METER);

    b2Vec2 pos = _archer.body()->GetPosition();
    sf::Vector2f posSF = sf::Vector2f(pos.x, pos.y);
    posSF.x -= sprite.getTextureRect().width / PIXELS_PER_METER / 2.0f;
    posSF.y += sprite.getTextureRect().height / PIXELS_PER_METER / 2.0f;
    sprite.setPosition(posSF);

    return sprite;
}

const Entity* ArcherView::entity() const
{
    return &_archer;
}
