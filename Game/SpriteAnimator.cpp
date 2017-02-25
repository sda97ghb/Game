#include "Game/ImageScaler.h"
#include "Game/SpriteAnimator.h"

SpriteAnimator::SpriteAnimator() :
    _currentGroup(""),
    _currentFrame(0),
    _animationDelay(250)
{
}

sf::Sprite& SpriteAnimator::sprite()
{
    return _sprite;
}

void SpriteAnimator::setTexture(const std::string& filename)
{
    sf::Image original;
    original.loadFromFile(filename);
    _texture.loadFromImage(ImageScaler::scale(original));

    _sprite.setTexture(_texture);
}

void SpriteAnimator::setAnimationGroup(
        const std::string& name,
        int x, int y, int frameWidth, int frameHeight,
        int numberOfFrames, bool isHorizontal)
{
    AnimationGroup group;
    group.x = x;
    group.y = y;
    group.frameWidth = frameWidth;
    group.frameHeight = frameHeight;
    group.numberOfFrames = numberOfFrames;
    group.orientation = isHorizontal ? AnimationGroup::horizontal :
                                       AnimationGroup::vertical;
    _animationGroups[name] = group;
}

void SpriteAnimator::setCurrentGroup(const std::string& groupname)
{
    if (_currentGroup == groupname)
        return;
    _currentGroup = groupname;
    _currentFrame = 0;
    nextFrame();
}

void SpriteAnimator::nextFrame()
{
    if (_animationGroups.find(_currentGroup) == _animationGroups.end())
        throw NoAnimationGroup(_currentGroup);
    AnimationGroup& group = _animationGroups[_currentGroup];
    int x = group.x;
    int y = group.y;
    if (group.orientation == AnimationGroup::horizontal)
        x += group.frameWidth * _currentFrame;
    else
        y += group.frameHeight * _currentFrame;
    _sprite.setTextureRect(sf::IntRect(x * 2, y * 2,
                                       group.frameWidth * 2,
                                       group.frameHeight * 2));
    ++ _currentFrame;
    if (_currentFrame >= group.numberOfFrames)
        _currentFrame = 0;
}

void SpriteAnimator::update()
{
    if (_clock.getElapsedTime().asMilliseconds() < _animationDelay)
        return;
    nextFrame();
    _clock.restart();
}
