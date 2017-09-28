/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    21/9/17
/// \brief   Controller for all sound events
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#include "SoundController.hpp"

SoundController::SoundController()
{
    loadResources();
    getSounds();
}

void SoundController::playSound(sounds::ID id, float pitch, float volume)
{
    _soundList.at(id).setVolume(volume);
    _soundList.at(id).setPitch(pitch);
    _soundList.at(id).play();
}

bool SoundController::loadMusic()
{
    if(!_music.openFromFile("resources/game_music.ogg"))
        return false;
    return true;
}
void SoundController::playMusic()
{
    _music.setLoop(true);
    _music.setVolume(25);
}

void SoundController::stopMusic()
{
    if (_music.getStatus()==sf::Music::Playing)
        _music.stop();
}

void SoundController::getSounds()
{
    // Constructs the vector of sound obects by iterating through the enum
    // This relies upon the dummy enum entry soundID_end, and the first entry to
    // the enum list being assigned to 0, with the remainder in default (non specified) numerical order
    sounds::ID id;
    int end = (sounds::soundID_end-1);
    for(auto i = 0; i < end ; i++)
    {
        id = (sounds::ID)i;
        sf::Sound sound;
        _soundList.push_back(sound);
        _soundList.at(i).setBuffer(_sounds.get(id));
    }
}


void SoundController::loadResources()
{
    // Load Sounds
    _sounds.load(sounds::StartSound,"resources/startup.ogg");
    _sounds.load(sounds::SpawnSound,"resources/ship_spawn.ogg");
    _sounds.load(sounds::GameOverLoseSound,"resources/gameover.ogg");
    _sounds.load(sounds::GameOverWinSound,"resources/win.ogg");
    _sounds.load(sounds::PlayerMove,"resources/thrust.ogg");
    _sounds.load(sounds::PlayerShoot,"resources/shoot_laser.ogg");
    _sounds.load(sounds::EnemyShoot,"resources/shoot_phaser.ogg");
    _sounds.load(sounds::PlayerDeath,"resources/player_death.ogg");
    _sounds.load(sounds::Explosion,"resources/explosion.ogg");
}