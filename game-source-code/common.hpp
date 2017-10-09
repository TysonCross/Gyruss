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

using std::string;
using std::to_string;

//USEFUL FUNCTIONS and CONSTANTS
namespace common
{
//    const float pi = 3.1415;

    ////////////////////////////////////////////////////////////
    /// \brief Simple struct of 3 floats, a co-ordinate system (x,y,z)
    ////////////////////////////////////////////////////////////
    struct position
    {
        float x;
        float y;
        float z;
    };

    ////////////////////////////////////////////////////////////
    /// \brief Ensures that the angle is always between 0 and 360
    /// \param angle The angle to check
    /// \return The float angle from 0 to 360
    ////////////////////////////////////////////////////////////
    float angleFilter(float angle);

    ////////////////////////////////////////////////////////////
    /// \brief Converts an angle from degrees to radians
    /// \param degree The angle to convert
    /// \return The angle in radians
    ////////////////////////////////////////////////////////////
    float degreeToRad(float degree);

    ////////////////////////////////////////////////////////////
    /// \brief Converts an angle from radians to degrees
    /// \param radian The angle to convert
    /// \return The angle in degrees
    ////////////////////////////////////////////////////////////
    float radToDegree(float radian);

    ////////////////////////////////////////////////////////////
    /// \brief Converts an int to a string, with optional padding
    /// \param value The input number
    /// \param paddingLength (Optional) the length to pad to
    /// \param padChar (Optional) the char to pad with (defaults to '0' char)
    /// \return The number as a string (optionally padded)
    ////////////////////////////////////////////////////////////
    string padIntToString(unsigned int value, int paddingLength=0, char padChar='0');


}

////////////////////////////////////////////////////////////
/// \brief A namespace to collect the ID keys for the game entities
///
/// Note that the final entry is enemyID_end, a special empty entry which allows determination of
/// size and the first entry is specified as =0, hence enabling indexing of the enum.
////////////////////////////////////////////////////////////
namespace entity
{
    enum ID
    {
        Basic = 0,
        BasicAlternate,
        BasicWanderer,
        PlayerShip,
        PlayerBullet,
        EnemyBullet,
        Meteoroid,
        Satellite,
        Explosion,
        Shield,
        testEnemy,
        enemyID_end
    };
}

////////////////////////////////////////////////////////////
/// \brief A namespace to collect the ID keys for the game texture file resources
///
/// This allows easy access while writing code to assign the textures to game objects by ID
/// note that the final entry is textureID_end, a special empty entry which allows determination of
/// size and the first entry is specified as =0, hence enabling indexing of the enum.
////////////////////////////////////////////////////////////
namespace textures
{
    enum ID
    {
        EnemyShipGrey = 0,
        EnemyShipPurple,
        EnemyShipYellow,
        SplashScreen,
        SplashScreenExtra,
        GameOverLoseScreen,
        GameOverWinScreen,
        SplashControls,
        SplashPoints,
        GameOverCredits,
        PlayerShip,
        BulletPlayer,
        BulletEnemy,
        Meteoroid,
        Satellite,
        Explosion,
        Shield,
        Planet,
        testTexture,
        textureID_end
    };
}
////////////////////////////////////////////////////////////
/// \brief A namespace to collect the ID keys for the game sound-fx file resources
///
/// This allows easy access while writing code to assign the textures to game objects by ID
/// note that the final entry is soundID_end, a special empty entry which allows determination of
/// size and the first entry is specified as =0, hence enabling indexing of the enum.
////////////////////////////////////////////////////////////

namespace sounds
{
    enum ID
    {
        StartSound = 0,
        SpawnSound,
        GameOverLoseSound,
        GameOverWinSound,
        PlayerMove,
        PlayerShoot,
        EnemyShoot,
        PlayerDeath,
        Explosion,
        testSound,
        soundID_end
    };
}

////////////////////////////////////////////////////////////
/// \brief A namespace to collect the ID keys for the game typeface resources
///
/// This allows easy access while writing code to assign the textures to game objects by ID
/// note that the final entry is fontID_end, a special empty entry which allows determination of
/// size and the first entry is specified as =0, hence enabling indexing of the enum.
////////////////////////////////////////////////////////////
namespace fonts
{
    enum ID
    {
        Title = 0,
        Default,
        testFont,
        fontID_end
    };
}
////////////////////////////////////////////////////////////
/// \brief A namespace for the possible game states
////////////////////////////////////////////////////////////
namespace game
{
    enum GameState
    {
        Splash,
        Playing,
        GameOverLose,
        GameOverWin,
        Exiting
    };
}

////////////////////////////////////////////////////////////
// Forward declaration
////////////////////////////////////////////////////////////
template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, textures::ID> TextureHolder;
typedef ResourceHolder<sf::SoundBuffer, sounds::ID> SoundHolder;
typedef ResourceHolder<sf::Font, fonts::ID> FontHolder;

#endif //PROJECT_COMMON_HPP
