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

//namespace sf
//{
//    class Texture;
//    class Font;
//    class Shader;
//}

//USEFUL FUNCTIONS and CONSTANTS
namespace common
{
    const float pi = 3.1415;

    /// \brief A simple 2d container of 2 ints
    struct Resolution
    {
        unsigned int x;
        unsigned int y;
    };

    /// \brief Simple struct of 3 floats, a co-ordinate system (x,y,z)
    struct position
    {
        float x;
        float y;
        float z;
    };

    /// \brief Ensures that the angle is always between 0 and 360
    float degreeToRad(float degree);

    /// \brief Converts an angle from degrees to radians
    float angleFilter(float angle);

}

namespace textures
{
    enum ID
    {
        SplashScreen,
        PlayerShip,
        BulletPlayer,
        BulletEnemy,
        EnemyShipGrey,
        EnemyShipPurple,
//        EnemyShipGenerator,
//        Meteoroid,
//        Satellite,
    };
}

namespace sounds
{
    enum ID
    {
        StartSound,
        SpawnSound,
        PlayerShoot,
        EnemyShoot,
    };
}

namespace fonts
{
    enum ID
    {
        Title,
        Info,
    };
}

// Forward declaration
template <typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, textures::ID>	    TextureHolder;
typedef ResourceHolder<sf::SoundBuffer, sounds::ID>	    SoundHolder;
typedef ResourceHolder<sf::Font, fonts::ID>			    FontHolder;

#endif //PROJECT_COMMON_HPP
