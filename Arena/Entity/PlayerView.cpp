#include "Arena/GlobalConstants.h"

#include "Arena/Entity/PlayerView.h"

PlayerView::PlayerView(const Player& player) :
    _player(player)
{
//    _animator.setTexture("Textures/player1.png");

//    _animator.setAnimationGroup("going_left", 0, 0, 9, 9, 2, Orientation::horizontal);
//    _animator.setAnimationGroup("going_right", 0, 9, 9, 9, 2, Orientation::horizontal);
////    _animator.setAnimationGroup("climbing", 0, 0, 5, 9, 1, Orientation::vertical);
//    _animator.setAnimationGroup("punching_right", 18, 0, 10, 9);
//    _animator.setAnimationGroup("punching_left", 18, 9, 10, 9);
//    _animator.setAnimationGroup("dead", 0, 18, 5, 5);

//    _animator.setAnimationGroup("going_left", 0, 0, 7, 9, 2, Orientation::horizontal);
//    _animator.setAnimationGroup("going_right", 0, 9, 7, 9, 2, Orientation::horizontal);
////    _animator.setAnimationGroup("climbing", 0, 0, 5, 9, 1, Orientation::vertical);
//    _animator.setAnimationGroup("punching_right", 14, 0, 9, 9);
//    _animator.setAnimationGroup("punching_left", 14, 9, 9, 9);
//    _animator.setAnimationGroup("dead", 0, 18, 5, 5);

//    _animator.setCurrentGroup("going_right");
//    _animator.nextFrame();
}

const sf::Sprite& PlayerView::getSprite()
{
//    static bool f = true;
//    if (f)
//    {
//        f = false;
//        _animator.setTexture("Textures/player1.png");
//    }

    _animator.update();

    if (!_player.isAlive())
    {
        _animator.playGroup("dead");
        _animator.nextFrame();
        _animator.stop();
    }

    if (_player.lookingDirection() == Direction::left)
    {
        if (_player.isPreparingForAttack())
            _animator.setCurrentGroup("punching_left");
        else
            _animator.setCurrentGroup("going_left");
    }
    else
    {
        if (_player.isPreparingForAttack())
            _animator.setCurrentGroup("punching_right");
        else
            _animator.setCurrentGroup("going_right");
    }

    sf::Sprite& sprite = _animator.sprite();

    sprite.setScale(1.0f / PIXELS_PER_METER, -1.0f / PIXELS_PER_METER);

    b2Vec2 pos = _player.body()->GetPosition();
    sf::Vector2f posSF = sf::Vector2f(pos.x, pos.y);
    posSF.x -= sprite.getTextureRect().width / PIXELS_PER_METER / 2.0f;
    posSF.y += sprite.getTextureRect().height / PIXELS_PER_METER / 2.0f;
    sprite.setPosition(posSF);

    return sprite;
}

const Entity* PlayerView::entity() const
{
    return &_player;
}
