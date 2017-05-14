#include "Player2View.h"

Player2View::Player2View(const Player& player) :
    PlayerView(player)
{
    _animator.setTexture("Textures/player2.png");

    _animator.setAnimationGroup("going_left", 0, 0, 7, 9, 2, Orientation::horizontal);
    _animator.setAnimationGroup("going_right", 0, 9, 7, 9, 2, Orientation::horizontal);
//    _animator.setAnimationGroup("climbing", 0, 0, 5, 9, 1, Orientation::vertical);
    _animator.setAnimationGroup("punching_left", 14, 0, 9, 9);
    _animator.setAnimationGroup("punching_right", 14, 9, 9, 9);
    _animator.setAnimationGroup("dead", 0, 18, 5, 5);

    _animator.setCurrentGroup("going_right");
    _animator.nextFrame();
}

const sf::Sprite& Player2View::getSprite()
{
    static bool f = true;
    if (f)
    {
        f = false;
        _animator.setTexture("Textures/player2.png");
    }

    return PlayerView::getSprite();
}
