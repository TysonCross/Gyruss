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
////////////////////////////////////////////////////////////
/// \brief SoundController Class used to handle all game sounds generated through the game
///
/// Whenever a game sound is made, in any form, the SoundController is responsible for playing it.
/// The sound controler is also responsible for loading the sounds in to the game from disk
/// Its design is very similar to that of ResourceHolder, except it has the ability to play sounds
///
/// \see ResourceHolder.hpp
////////////////////////////////////////////////////////////
class SoundController
{
public:
    ////////////////////////////////////////////////////////////
    /// \brief SoundController constructor. when called, calles the loadResources to load the sounds into memory
    /// and calls getSounds to construct a vector of all the sounds from the disk resources. These sounds are now
    /// ready to be called from any game object to be played. All the game object needs to know
    /// is the ID of the sound (i.e. its name) and it can be played without having to load the sound
    /// in from disk first.
    ///
    /// \see loadResources
    /// \see getSounds
    ////////////////////////////////////////////////////////////
    SoundController();

    ////////////////////////////////////////////////////////////
    /// \brief PlaySound is used whenever a sound is needed to be played, from any contex
    ///
    /// \param id defines the sound ID that is to be played. these are unique. Using this ID,
    /// The caller of the function can define what sound they want to play
    /// \param pitch enables the caller to set the pitch of the sound
    /// \param volume enables the caller to set the volume of the sound
    /// \param loop enables or disables the looping of the played sound. i.e. when the sound ends, if looping is set
    /// to true, the sound will start playing again.
    ////////////////////////////////////////////////////////////
    void playSound(sounds::ID id, float pitch = 1.f, float volume = 100, bool loop = 0);

    ////////////////////////////////////////////////////////////
    /// \brief setPitch enables the caller to change the pitch of a particular sound by ID
    ///
    /// \param id the spesific ID of a sound to change the pitch for
    /// \param pitch the desired pitch to be set
    ////////////////////////////////////////////////////////////
    void setPitch(sounds::ID id, float pitch);

    ////////////////////////////////////////////////////////////
    /// \brief Provides a mechanism for generating "3D" sterio sound as the playership moves around the
    /// play circle
    /// \param id defines the sound to have position changed
    /// \param position defines the position to set for the associated sound
    ///
    /// \see SFML/sound
    ////////////////////////////////////////////////////////////
    void setPosition(sounds::ID id, common::position position);

    ////////////////////////////////////////////////////////////
    /// \brief Stops a sound from playing, based on an id
    ///
    /// \param id sound to stop playing
    ////////////////////////////////////////////////////////////
    void stopSound(sounds::ID id);

    ////////////////////////////////////////////////////////////
    /// \brief Loads the game music from disk into memory
    /// \return A bool to indicate success
    ////////////////////////////////////////////////////////////
    bool loadMusic();

    ////////////////////////////////////////////////////////////
    /// \brief Starts playing game music. Called main gameplay starts
    ////////////////////////////////////////////////////////////
    void playMusic();

    ////////////////////////////////////////////////////////////
    /// \brief Stops playing game music. Called when main gameplay stops
    ////////////////////////////////////////////////////////////
    void stopMusic();

private:
    ////////////////////////////////////////////////////////////
    /// \brief Music object to fasilitate the playing of music as a background for the game
    ///
    /// \see sf::Music
    ////////////////////////////////////////////////////////////
    sf::Music _music;

    ////////////////////////////////////////////////////////////
    /// \brief Private function used to load the sounds into memory from disk. called at game start
    ///
    /// \see SoundController
    ////////////////////////////////////////////////////////////
    void loadResources();

    ////////////////////////////////////////////////////////////
    /// \brief Builds a map linking the game sounds to the game unique ID's
    ///
    /// \see SoundController
    ////////////////////////////////////////////////////////////
    void getSounds();

    ////////////////////////////////////////////////////////////
    /// \brief Vector used to store all game sound objects and their associated ID's
    ///
    /// \see std::vector
    /// \see sf::sound
    ////////////////////////////////////////////////////////////
    std::vector<sf::Sound> _soundList;

    ////////////////////////////////////////////////////////////
    /// \brief Sound Holder object used to store all sound objects in memory
    ////////////////////////////////////////////////////////////
    SoundHolder _sounds;
};


#endif //PROJECT_SOUNDCONTROLLER_HPP
