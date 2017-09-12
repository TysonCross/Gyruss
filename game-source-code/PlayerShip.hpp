/////////////////////////////////////////////////////////////////////
/// Students 1239448 & 1101946
/// \date    2017/09/09
/// \brief   Player ship
///
/// Object for the player ship model
///
/// \copyright (c) 2017 Tyson Cross and Chris Maree, Wits University
/////////////////////////////////////////////////////////////////////

#ifndef PROJECT_PLAYERSHIP_HPP
#define PROJECT_PLAYERSHIP_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include "ResourceMapper.hpp"
#include "common.hpp"

class PlayerShip
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class
    ///
    /// \param resourceMapper The resourceMapper object that
    /// contains the path to the texture(s) for the sprite
    /// \param distanceFromCentre The fixed radius of the circle
    /// that the ship flies around
    /// \param angle The angle in degrees around the circle of movement
    /// \param scale The scale of the sprite
    ///
    ////////////////////////////////////////////////////////////
    PlayerShip(const ResourceMapper &resourceMapper, float distanceFromCentre, int angle, float scale);

    ////////////////////////////////////////////////////////////
    /// \brief Moves the player ship around a circle by this angle
    ////////////////////////////////////////////////////////////
    void move(int angle);

    ////////////////////////////////////////////////////////////
    /// \brief Shooting ma lazers
    ///
    /// Spawns a projectile
    ///
    ////////////////////////////////////////////////////////////
    void shoot();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    sf::Sprite &getSprite();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the texture object of the Class by ref
    ///
    /// \see sf:Texture
    ////////////////////////////////////////////////////////////
    sf::Texture &getTexture();

private:

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Sprite _sprite;
    sf::Texture _texture;
    sf::SoundBuffer _buffer;
    sf::Sound _shootSound;
    int _width;
    int _height;
    float _distanceFromCentre;
    int _angle;
    float _scale;
};

#endif //PROJECT_PLAYERSHIP_HPP
