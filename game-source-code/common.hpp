/////////////////////////////////////////////////////////////////////
/// \brief   Common functions, aliases and global constants
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_COMMON_HPP
#define PROJECT_COMMON_HPP

#include <cmath>
#include <SFML/Graphics.hpp>
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
        float x; /*!< x co-ordinate */
        float y; /*!< y co-ordinate */
        float z; /*!< z co-ordinate */
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
////////////////////////////////////////////////////////////
namespace entity
{
    enum ID
    {
        Basic = 0,          /*!< A basic Enemy, Note specified as 0, to enable iteration*/
        BasicAlternate,     /*!< A basic Enemy (alternate) */
        BasicWanderer,      /*!< An Enemy (wanderer) */
        PlayerShip,         /*!< PlayerShip entity*/
        PlayerBullet,       /*!< Bullet fired by the player */
        EnemyBullet,        /*!< Bullet fired by the enemy */
        Meteoroid,          /*!< A Meteoroid */
        Satellite,          /*!< Satellite Enemy */
        Explosion,          /*!< An Explosion */
        Shield,             /*!< Invulnerability Shield for the player */
        testEnemy,          /*!< USED FOR TESTING ONLY */
        enemyID_end         /*!< Final entry, used to allow iteration on an enum */
    };
}

////////////////////////////////////////////////////////////
/// \brief A namespace to collect the ID keys for the game texture file resources
///
/// This allows easy access while writing code to assign the textures to game objects by ID
/// note that the final entry is textureID_end, a special empty entry which allows determination of
/// size and the first entry is specified as = 0, hence enabling indexing of the enum.
////////////////////////////////////////////////////////////
namespace textures
{
    enum ID
    {
        EnemyShipGrey = 0,  /*!< A basic Enemy (Note specified as 0) to enable iteration \image html enemyship_grey.png */
        EnemyShipPurple,    /*!< A basic Enemy (alternate) \image html enemyship_purple.png */
        EnemyShipYellow,    /*!< An Enemy (wanderer)  \image html enemyship_yellow.png*/
        SplashScreen,       /*!< ScreenSplash image (background) */
        SplashScreenExtra,  /*!< ScreenSplash image detail */
        GameOverLoseScreen, /*!< ScreenGameOver background image (lose) */
        GameOverWinScreen,  /*!< ScreenGameOver background image (win) */
        SplashControls,     /*!< ScreenSplash information graphic for controls */
        SplashPoints,       /*!< ScreenSplash information graphic for scoring */
        GameOverCredits,    /*!< ScreenGameOver credits image */
        PlayerShip,         /*!< PlayerShip entity  \image html player_ship_animated.png */
        BulletPlayer,       /*!< Animated Bullet texture (fired by the player) \image html bullet_player.png */
        BulletEnemy,        /*!< Animated Bullet texture (fired by the enemy) \image html bullet_enemy.png */
        Meteoroid,          /*!< Meteoroid texture \image html meteoroid.png */
        Satellite,          /*!< Satellite Enemy image \image html satellite.png */
        Explosion,          /*!< Animated Explosion texture \image html explosion.png */
        Shield,             /*!< Shield texture \image html shield.png*/
        Planet,             /*!< Animated ScreenSplash image detail \image html earth.png */
        testTexture,        /*!< USED FOR TESTING ONLY */
        textureID_end       /*!< Final entry, used to allow iteration on an enum */
    };
}
////////////////////////////////////////////////////////////
/// \brief A namespace to collect the ID keys for the game sound-fx file resources
///
/// This allows easy access while writing code to assign the sounds to game objects by ID
/// \see SoundController
////////////////////////////////////////////////////////////

namespace sounds
{
    enum ID
    {
        StartSound = 0,     /*!< Startup sound (Note specified as 0) to enable iteration */
        SpawnSound,         /*!< Played when player re-spawns */
        GameOverLoseSound,  /*!< Played in ScreenGameOver when player loses */
        GameOverWinSound,   /*!< Played in ScreenGameOver when player wins */
        PlayerMove,         /*!< Jet-engine sounds played then player moves */
        PlayerShoot,        /*!< Firing sound for player */
        EnemyShoot,         /*!< Firing sound for enemies (pitch is modified when played) */
        PlayerDeath,        /*!< Sound played when player dies */
        Explosion,          /*!< Sound of an explosion */
        testSound,          /*!< USED FOR TESTING ONLY */
        soundID_end         /*!< Final entry, used to allow iteration on an enum */
    };
}

////////////////////////////////////////////////////////////
/// \brief A namespace to collect the ID keys for the game typeface resources
///
/// This allows easy access while writing code to assign the textures to game objects by ID
/// note that the final entry is fontID_end, a special empty entry which allows determination of
/// size and the first entry is specified as = 0, hence enabling indexing of the enum.
////////////////////////////////////////////////////////////
namespace fonts
{
    enum ID
    {
        Title = 0,      /*!< Title font (danube.ttf) (Note specified as 0 to enable iteration */
        Default,        /*!< Main game font (fax_sans_beta.otf)  */
        testFont,       /*!< USED FOR TESTING ONLY */
        fontID_end      /*!< Final entry, used to allow iteration on an enum */
    };
}
////////////////////////////////////////////////////////////
/// \brief A namespace for the possible game states
////////////////////////////////////////////////////////////
namespace game
{
    enum GameState
    {
        Splash,         /*!< Show ScreenSplash */
        Playing,        /*!< Playing Game */
        GameOverLose,   /*!< Show ScreenGameOver in lose state */
        GameOverWin,    /*!< Show ScreenGameOver in win state */
        Exiting         /*!< Exit game (end programme) */
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
