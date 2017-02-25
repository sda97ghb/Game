#ifndef SPRITEANIMATOR_H
#define SPRITEANIMATOR_H

#include <map>

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Clock.hpp"

class SpriteAnimator
{
public:
    struct NoAnimationGroup : std::logic_error
    {
        NoAnimationGroup(const std::string& groupname) :
            std::logic_error(
                std::string("this animator have no group with name \"") + groupname + "\"")
        {}
    };

    struct AnimationGroup
    {
        int x;
        int y;
        int frameWidth;
        int frameHeight;
        int numberOfFrames;
        enum {
            vertical,
            horizontal
        } orientation;
    };

    SpriteAnimator();

    sf::Sprite& sprite();

    void setTexture(const std::string& filename);

    void setAnimationGroup(const std::string& name,
                           int x, int y, int frameWidth, int frameHeight,
                           int numberOfFrames, bool isHorizontal = true);
    void setCurrentGroup(const std::string& groupname);

    void playGroup(const std::string& groupname);
    void restoreGroup();

    void nextFrame();

    void update();

    const std::string& currentGroup() const;

private:
    sf::Texture _texture;
    sf::Sprite _sprite;

    std::map<std::string, AnimationGroup> _animationGroups;

    std::string _currentGroup;
    int _currentFrame;

    std::string _previousGroup;
    bool _playOnce;

    int _animationDelay;

    sf::Clock _clock;
};

#endif // SPRITEANIMATOR_H
