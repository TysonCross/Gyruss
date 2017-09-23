/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/10
/// \brief   Common functions, aliases and global constants
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_COMMON_HPP
#define PROJECT_COMMON_HPP

#include "SFML/Graphics.hpp"
#include <cmath>
#include <SFML/Audio/Sound.hpp>
#include "ResourceHolder.hpp"

//USEFUL FUNCTIONS and CONSTANTS
namespace common
{
    const float pi = 3.1415;

//    /// \brief A simple 2d container of 2 ints
//    struct Resolution
//    {
//        unsigned int x;
//        unsigned int y;
//    };

    /// \brief Simple struct of 3 floats, a co-ordinate system (x,y,z)
    struct position
    {
        float x;
        float y;
        float z;
    };

    /// \brief Ensures that the angle is always between 0 and 360
    float angleFilter(float angle);

    /// \brief Converts an angle from degrees to radians
    float degreeToRad(float degree);

    /// \brief Converts an angle from radians to degrees
    float radToDegree(float radian);

}

/// \brief A namespace to collect the ID keys for the game texture file resources
///
/// This allows easy access while writing code to assign the textures to game objects by ID
/// note that the final entry is textureID_end, a special empty entry which allows determination of
/// size and the first entry is specified as =0, hence enabling indexing of the enum.
namespace textures
{
    enum ID
    {
        EnemyShipGrey = 0,
        EnemyShipPurple,
        SplashScreen,
        SplashScreenExtra,
        GameOverScreen,
        SplashControls,
        GameOverCredits,
        PlayerShip,
        BulletPlayer,
        BulletEnemy,
        Explosion,
        testTexture,
        textureID_end,
    };
}

/// \brief A namespace to collect the ID keys for the game sound-fx file resources
///
/// This allows easy access while writing code to assign the textures to game objects by ID
/// note that the final entry is soundID_end, a special empty entry which allows determination of
/// size and the first entry is specified as =0, hence enabling indexing of the enum.

namespace sounds
{
    enum ID
    {
        StartSound = 0,
        SpawnSound,
        GameOverSound,
        PlayerMove,
        PlayerShoot,
        EnemyShoot,
        PlayerDeath,
        Explosion,
        testSound,
        soundID_end,
    };
}

/// \brief A namespace to collect the ID keys for the game typeface resources
///
/// This allows easy access while writing code to assign the textures to game objects by ID
/// note that the final entry is fontID_end, a special empty entry which allows determination of
/// size and the first entry is specified as =0, hence enabling indexing of the enum.
namespace fonts
{
    enum ID
    {
        Title = 0,
        Info,
        testFont,
        fontID_end,
    };
}

/// \brief A namespace for the possible game states
namespace game
{
    enum GameState
    {
        Splash,
        Playing,
        GameOver,
        Exiting,
    };
}

// Forward declaration
template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, textures::ID> TextureHolder;
typedef ResourceHolder<sf::SoundBuffer, sounds::ID> SoundHolder;
typedef ResourceHolder<sf::Font, fonts::ID> FontHolder;

#endif //PROJECT_COMMON_HPP
