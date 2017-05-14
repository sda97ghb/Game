#include "Audio.h"
#include "iostream"
Audio &Audio::instance()
{
    static Audio instance;
    return instance;
}

Audio::Audio()
{

}

void Audio::playMusic(const std::string& filename)
{
    _music.openFromFile(filename);
    _music.play();
}

void Audio::playSound(const std::__cxx11::string& filename)
{
    if (!_buffer.loadFromFile(filename))
        std::cout << "errorSound";
    _sound.setBuffer(_buffer);
    _sound.play();
}

