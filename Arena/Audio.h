#ifndef AUDIO_H
#define AUDIO_H

#include "SFML/Audio.hpp"

class Audio
{
public:
    static Audio& instance();

    Audio();

    void playMusic();

    sf::Music music() const;

private:
    sf::Music _music;
    sf::SoundBuffer _sound;
};

#endif // AUDIO_H
