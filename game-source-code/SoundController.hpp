/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    21/9/17
/// \brief   Controller for all sound events
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////


#ifndef PROJECT_SOUNDCONTROLLER_HPP
#define PROJECT_SOUNDCONTROLLER_HPP

#include "SFML/Audio.hpp"
#include "ResourceHolder.hpp"

class SoundController
{
public:
    SoundController();
    void playSound(sounds::ID id, float pitch = 1.f, float volume = 100);
    bool loadMusic();
    void playMusic();
    void stopMusic();

private:
    sf::Music _music;
    void loadResources();
    void getSounds();
    std::vector<sf::Sound> _soundList;
    SoundHolder _sounds;
};


#endif //PROJECT_SOUNDCONTROLLER_HPP
