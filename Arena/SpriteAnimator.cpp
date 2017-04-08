#include <iostream>

#include "Arena/SpriteAnimator.h"

SpriteAnimator::SpriteAnimator() :
    _currentGroup(""),
    _currentFrame(0),
    _previousGroup(""),
    _playOnce(false),
    _animationDelay(250),
    _isStopped(false)
{
}

sf::Sprite& SpriteAnimator::sprite()
{
    return _sprite;
}

void SpriteAnimator::setTexture(const std::string& filename)
{
    std::cout << "load texture " << filename << std::endl;

    _texture.loadFromFile(filename);

    _sprite.setTexture(_texture);
}

void SpriteAnimator::setAnimationGroup(const std::string& name,
        int x, int y, int frameWidth, int frameHeight,
        int numberOfFrames, Orientation orientation)
{
    AnimationGroup group;

    group.x = x;
    group.y = y;
    group.frameWidth = frameWidth;
    group.frameHeight = frameHeight;
    group.numberOfFrames = numberOfFrames;
    group.orientation = orientation;

    _animationGroups[name] = group;
}

void SpriteAnimator::setCurrentGroup(const std::string& groupname)
{
    if (_currentGroup == groupname)
        return;
    if (_playOnce)
        return;
    _currentGroup = groupname;
    _previousGroup = "";
    _currentFrame = 0;
    _playOnce = false;
}

void SpriteAnimator::playGroup(const std::string& groupname)
{
    if (_currentGroup == groupname)
        return;
    _previousGroup = _currentGroup;
    _currentGroup = groupname;
    _currentFrame = 0;
    _playOnce = true;
}

void SpriteAnimator::restoreGroup()
{
    _currentGroup = _previousGroup;
    _previousGroup = "";
    _currentFrame = 0;
    _playOnce = false;
}

void SpriteAnimator::nextFrame()
{
    if (_animationGroups.find(_currentGroup) == _animationGroups.end())
        throw NoAnimationGroupException(_currentGroup);
    AnimationGroup& group = _animationGroups[_currentGroup];
    int x = group.x;
    int y = group.y;
    if (group.orientation == Orientation::horizontal)
        x += group.frameWidth * _currentFrame;
    else
        y += group.frameHeight * _currentFrame;
    _sprite.setTextureRect(sf::IntRect(x, y,
                                       group.frameWidth, group.frameHeight));
    ++ _currentFrame;
    if (_currentFrame >= group.numberOfFrames)
    {
        if (_playOnce)
            restoreGroup();
        else
            _currentFrame = 0;
    }
}

void SpriteAnimator::update()
{
    if (_isStopped)
        return;
    if (_clock.getElapsedTime().asMilliseconds() < _animationDelay)
        return;
    nextFrame();
    _clock.restart();
}

const std::string& SpriteAnimator::currentGroup() const
{
    return _currentGroup;
}

void SpriteAnimator::stop()
{
    _isStopped = true;
}
