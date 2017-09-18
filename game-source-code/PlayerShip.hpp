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
#include "common.hpp"
#include "ResourceHolder.hpp"
#include <experimental/optional>

class PlayerShip
{
public:

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class
    ///
    /// \param textureHolder The resourceMapper object that
    /// contains the path to the texture(s) for the sprite
    /// \param The screen resolution (to determine the radius
    /// the playerShip circles around
    /// \param distanceFromCentre The fixed radius of the circle
    /// that the ship flies around
    /// \param angle The angle in degrees around the circle of movement
    /// \param scale The scale of the sprite
    ///
    ////////////////////////////////////////////////////////////
    PlayerShip(const TextureHolder &textureHolder,
               const SoundHolder &soundHolder,
               const common::Resolution resolution,
               float distanceFromCentre,
               float angle,
               float scale);

    void setMove(float angle);
    void setShoot();
    bool isShooting();
    void reset();
    void update();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the distance from origin
    ////////////////////////////////////////////////////////////
    float getDistanceFromCentre();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the angle
    ////////////////////////////////////////////////////////////
    float getAngle();

    ////////////////////////////////////////////////////////////
    /// \brief Returns the Sprite object of the Class by ref
    ///
    /// \see sf:Sprite
    ////////////////////////////////////////////////////////////
    sf::Sprite &getSprite();

private:
    ////////////////////////////////////////////////////////////
    /// \brief Moves the player ship around a circle by this angle
    ////////////////////////////////////////////////////////////
    void move();

    ////////////////////////////////////////////////////////////
    /// \brief Shooting ma lazers
    ///
    /// Spawns a projectile
    ///
    ////////////////////////////////////////////////////////////
    void shoot();

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    sf::Sprite _sprite;
    sf::Sound _soundSpawn;
    sf::Sound _soundShoot;
    sf::Sound _soundMove;
    common::Resolution _resolution;
    float _distanceFromCentre;
    float _angle;
    float _scale;
    float _futureAngleValue;
    bool _isMoving;
    bool _isShooting;
};

#endif //PROJECT_PLAYERSHIP_HPP
