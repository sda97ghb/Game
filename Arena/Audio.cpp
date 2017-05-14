#include "Audio.h"

Audio &Audio::instance()
{
    static Audio instance;
    return instance;
}

Audio::Audio()
{

}

void Audio::playMusic()
{
    _music.openFromFile("Audio/backmusic.ogg");
    _music.play();
}

