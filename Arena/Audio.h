#ifndef AUDIO_H
#define AUDIO_H

#include <string>

#include "SFML/Audio.hpp"

/// @brief Класс звуков.
class Audio
{
public:
    static Audio& instance();

    Audio();

    void playMusic(const std::string& filename);
    void playSound(const std::string& filename);

    sf::Music music() const;

private:
    sf::Music _music;
    sf::SoundBuffer _buffer;
    sf::Sound _sound;
};

#endif // AUDIO_H
